#include <iostream>
#include <conio.h>
#include <windows.h>

bool gameStart, gameOver;
bool  showMenu = true;
const int width = 20;
const int height = 20;
int headX, headY, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

void Setup() {
	gameOver = false;
	dir = STOP;
	headX = width / 2;
	headY = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}

void Draw(){
	system("cls");
	for (int i = 0; i < width+2; i++) {
		std::cout << "# ";
	}
	std::cout << std::endl;

	for (int i = 0; i < height; i++) {

		for (int j = 0; j < width; j++) {

			if (j == 0) {
				std::cout << "# ";
			}
			if (i == headY && j == headX) {
				std::cout << "O ";
			}
			else if (i == fruitY && j == fruitX) {
				std::cout << "F ";
			}
			else {
				bool print = false;
				for (int k = 0; k < nTail; k++) {

					if (tailX[k] == j && tailY[k] == i) {
						std::cout << "o ";
						print = true;
					}
					
					}
				if (!print) {
					std::cout << "  ";
				}
			}
			if (j == width - 1) {
				std::cout << "# ";
			}
		}
		std::cout << std::endl;
	}

	for (int i = 0; i < width+2; i++) {
		std::cout << "# ";
	}
	std::cout << std::endl;

	std::cout << "Score: " << score << std::endl;
}

void Input() {

	if (_kbhit()) {
		switch (_getch()) {
		case 'a' :
			dir = LEFT;
			break;
		case 'w' :
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}

void Logic() {

	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = headX;
	tailY[0] = headY;
	for (int i = 1; i < nTail; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir)
	{
	case LEFT:
		headX--;
		break;
	case RIGHT:
		headX++;
		break;
	case UP:
		headY--;
		break;
	case DOWN:
		headY++;
		break;
	default:
		break;
	}

	/*if (headX > width - 1 || headX < 0 || headY > height || headY < 0) {
		gameOver = true;
	}*/

	if (headX >= width) headX = 0; else if (headX < 0) headX = width - 1;
	if (headY >= width) headY = 0; else if (headY < 0) headY = width - 1;

	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == headX && tailY[i] == headY) {
			gameOver = true;
		}
	}


	if (headX == fruitX && headY == fruitY) {
		score += 20;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}

}

void Menu() {
	std::cout << "Enter 1 to start or anything else to quit:" << std::endl;
	std::cin >> gameStart;
	if (gameStart == false) {
		showMenu == false;
	}
}

void Gameover() {
	std::cout << "Game Over! Your score was " << score << std::endl;
	nTail = 0;
}

int main() {

	while (showMenu) {
		Menu();
		if (gameStart) {
			Setup();
			while (!gameOver) {
				Draw();
				Input();
				Logic();
				Sleep(100);
			}
			Gameover();
		}
		else {
			break;
		}
		
	}

	return 0;
}
