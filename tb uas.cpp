#include <GL/glut.h>
#include <math.h>

// Variabel untuk rotasi, scaling, dan kontrol gerakan
float rotationX = 0.0f;
float rotationY = 0.0f;
float scale = 1.0f;
bool isMoving = true;
float translationX = 0.0f, translationY = 0.0f, translationZ = 0.0f;

void setupLighting() {
    GLfloat light_position[] = { 1.0f, 1.0f, 1.0f, 0.0f };
    GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat light_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

void drawCartesianAxes() {
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);

    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-5.0f, 0.0f, 0.0f);
    glVertex3f(5.0f, 0.0f, 0.0f);

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -5.0f, 0.0f);
    glVertex3f(0.0f, 5.0f, 0.0f);

    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -5.0f);
    glVertex3f(0.0f, 0.0f, 5.0f);

    glEnd();
    glEnable(GL_LIGHTING);
}

void drawSauce() {
    GLUquadric* quadric = gluNewQuadric();
    glColor3f(2.0f, 0.1f, 0.0f);

    float radius = 0.55f;      
    float length = 3.0f;      
    float turns = 5.0f;     
    float step = 0.01f;       

    for (float t = 0.0f; t <= turns * 2 * M_PI; t += step) {
        float x = radius * cos(t);       
        float y = radius * sin(t);       
        float z = (t / (turns * 2 * M_PI)) * length - (length / 2); 

        glPushMatrix();
        glTranslatef(x, y, z);           
        gluSphere(quadric, 0.08, 20, 20); 
        glPopMatrix();
    }

    gluDeleteQuadric(quadric);
}

void drawStick() { 
    GLUquadric* quadric = gluNewQuadric();
    glColor3f(0.8f, 0.5f, 0.3f); 

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -5.0f);
    glRotatef(0.0f, 0.0f, 1.0f, 0.0f); 
    gluCylinder(quadric, 0.05f, 0.05f, 4.0f, 30, 30); 
    glPopMatrix();

    gluDeleteQuadric(quadric);
}

void drawSauceWithMayonnaise() {
    GLUquadric* quadric = gluNewQuadric();
    
    float radius = 0.55f;     
    float length = 3.0f;      
    float turns = 5.0f;       
    float step = 0.01f; 

    glColor3f(1.0f, 0.3f, 0.0f); 
    for (float t = 0.0f; t <= turns * 2 * M_PI; t += step) {
        float x = radius * cos(t);
        float y = radius * sin(t);
        float z = (t / (turns * 2 * M_PI)) * length - (length / 2);

        glPushMatrix();
        glTranslatef(y, x, z); 
        gluSphere(quadric, 0.08, 20, 20);
        glPopMatrix();
    }

    glColor3f(1.0f, 1.0f, 1.0f); 
    for (float t = 0.0f; t <= turns * 2 * M_PI; t += step) {
        float x = (radius + 0.1f) * cos(t); 
        float y = (radius + 0.1f) * sin(t);
        float z = (t / (turns * 2 * M_PI)) * length - (length / 2);

        glPushMatrix();
        glTranslatef(x, y, z); 
        gluSphere(quadric, 0.05, 20, 20);
        glPopMatrix();
    }

    gluDeleteQuadric(quadric);
}

void drawPlate() {
    GLUquadric* quadric = gluNewQuadric();
    glColor3f(1.0f, 1.0f, 1.0f); 

    float radiusOuter = 2.0f;  
    float radiusInner = 1.8f;  
    float height = 0.2f;       

    glPushMatrix();
    glTranslatef(0.0f, -0.3f, 0.0f); 
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); 
    gluDisk(quadric, 0.0f, radiusOuter, 50, 1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, -0.3f, 0.0f); 
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(quadric, radiusOuter, radiusOuter, height, 50, 1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, -0.4f + height, 0.0f); 
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); 
    gluDisk(quadric, 0.0f, radiusInner, 50, 1); 
    glPopMatrix();

    gluDeleteQuadric(quadric);
}

void drawSausage() {
    GLUquadric* quadric = gluNewQuadric();

    glPushMatrix();
    glColor3f(1.0f, 0.5f, 0.2f); 
    glTranslatef(0.0f, 0.0f, 0.0f);
    glScalef(1.0f, 1.0f, 3.0f); 
    gluSphere(quadric, 0.6, 30, 30);
    glPopMatrix();

	glPushMatrix();
    glColor3f(1.0f, 0.5f, 0.2f); 
    glTranslatef(0.0f, 0.0f, 1.5f); 
    gluSphere(quadric, 0.5, 30, 30); 
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0f, 0.5f, 0.2f); 
    glTranslatef(0.0f, 0.0f, -1.5f); 
    gluSphere(quadric, 0.5, 30, 30); 
    glPopMatrix();
    
    gluDeleteQuadric(quadric);
    
    drawSauce();
	drawSauceWithMayonnaise();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(0.0, 2.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glTranslatef(translationX, translationY, translationZ);
    glScalef(scale, scale, scale);
    glRotatef(rotationX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotationY, 0.0f, 1.0f, 0.0f);

    drawCartesianAxes();

    drawSausage();
    drawPlate();
	drawStick();
    glutSwapBuffers();
}

void update(int value) {
    if (isMoving) {
        rotationY += 2.0f;
        if (rotationY > 360.0f) {
            rotationY -= 360.0f;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(16, update, 0); 
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    	case 'i':
			translationZ -= 0.1f;
			break;
		case 'k': 
    		translationZ += 0.1f;
   		 	break;
		case 'j':
    		translationX -= 0.1f;
    		break;
		case 'l': 
    		translationX += 0.1f;
 	    	break;
		case 'u':
   	 		translationY += 0.1f;
 		    break;
		case 'o': 
    		translationY -= 0.1f;
 	    	break;
        case 'w':
            rotationX -= 5.0f;
            break;
        case 's':
            rotationX += 5.0f;
            break;
        case 'a':
            rotationY -= 5.0f;
            break;
        case 'd':
            rotationY += 5.0f;
            break;
        case '+':
            scale += 0.1f;
            break;
        case '-':
            scale -= 0.1f;
            break;
        case 27: 
            exit(0);
            break;
    }
    glutPostRedisplay();
}

void menu(int option) {
    switch (option) {
        case 1:
            isMoving = false;
            break;
        case 2:
            isMoving = true;
            break;
        case 3:
            exit(0);
            break;
    }
}

void reshape(int width, int height) {
    if (height == 0) height = 1;
    float aspect = (float)width / (float)height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, aspect, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Sosis 3D");

    glEnable(GL_DEPTH_TEST);
    setupLighting();

    glutCreateMenu(menu);
    glutAddMenuEntry("Objek Berhenti", 1);
    glutAddMenuEntry("Objek Bergerak Lagi", 2);
    glutAddMenuEntry("Keluar", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(16, update, 0); 

    glutMainLoop();
    return 0;
}

