#include<stdio.h>
#include<glut.h>
#include<math.h>

// 绘制点
void setPixel(int x, int y)
{
    glColor3f(0.0, 0.0, 1.0);
    glPointSize(2.0f);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
    glFlush(); 
}

// 绘制坐标系
void CoordinateSystem(void)
{
    glBegin(GL_LINES);
    glColor3f(0.0, 1.0, 1.0);
    glVertex2f(-150.0, 0.0);
    glVertex2f(150.0, 0.0);
    glVertex2f(0.0, -150.0);
    glVertex2f(0.0, 150.0);
    glEnd();
    glFlush();
}

// 对称绘制椭圆并调用绘制点函数和坐标系函数
void Ellipsepot(int x0, int y0, int x, int y)
{
    setPixel((x0 + x), (y0 + y));
    setPixel((x0 + x), (y0 - y));
    setPixel((x0 - x), (y0 - y));
    setPixel((x0 - x), (y0 + y));
    CoordinateSystem();
}

// 中点画椭圆算法
void MidPoint_Ellipse(int x0, int y0, int a, int b)
{
    double sqa = (double)(a) * (double)(a);
    double sqb = (double)(b) * (double)(b);

    double d = sqb + sqa * (0.25 - b);
    int x = 0;
    int y = b;
    Ellipsepot(x0, y0, x, y);
    // 1
    while (sqb * (x + 1.0) < sqa * (y - 0.5))
    {
        if (d < 0)
        {
            d += sqb * (2.0 * x + 3.0);
        }
        else
        {
            d += (sqb * (2.0 * x + 3.0) + sqa * ((-2.0) * y + 2.0));
            --y;
        }
        ++x;
        Ellipsepot(x0, y0, x, y);
    }
    d = (b * (x + 0.5)) * 2 + (a * (y - 1.0)) * 2.0 - (double)(a) * (double)(b) * 2.0;
    // 2
    while (y > 0)
    {
        if (d < 0)
        {
            d += sqb * (2.0 * x + 2.0) + sqa * ((-2.0) * y + 3.0);
            ++x;
        }
        else
        {
            d += sqa * ((-2.0) * y + 3.0);
        }
        --y;
        Ellipsepot(x0, y0, x, y);
    }
}

// 窗口设置
void WindowInit(void)
{
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowPosition(900, 100);
    glutInitWindowSize(600, 600);
    glutCreateWindow("计算19-7 1906010702 蔡佳桐——>椭圆的绘制");
}

// 设置图形渲染环境
void SetupRC(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glViewport(0, 0, 600, 600);
    gluOrtho2D(-150.0, 150.0, -150.0, 150.0);
}

// 交互窗口
void display(void)
{
    int a,b;
    int x0,y0;
    printf("\t椭圆x^2/a^2+y^2/b^2=1的绘制\n\n\n");
    printf("第一步：请输入椭圆的中心点坐标\n");
    printf("横坐标x：");
    scanf_s("%d", &x0);
    printf("纵坐标y：");
    scanf_s("%d", &y0);
    printf("\n\n第二步：请输入椭圆的a值和b值\n");
    printf("请输入a值：");
    scanf_s("%d", &a);
    printf("请输入b值：");
    scanf_s("%d", &b);
    MidPoint_Ellipse(x0, y0, a, b);
}

// 主函数
void main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    system("mode con cols=50 lines=30");
    WindowInit();
    SetupRC();
    glutDisplayFunc(display);
    glutMainLoop();
}