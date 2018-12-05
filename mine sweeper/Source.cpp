#include <stdio.h>
#include <time.h>
#include <stdlib.h>
static unsigned int g_seed, row, column, mine_num;

//-----------------------------------------------------------------------------------------------------------------------------
inline void fast_srand(int seed) {
	g_seed = seed;
}
//-----------------------------------------------------------------------------------------------------------------------------
inline int fast_rand(void) {
	g_seed = (214013 * g_seed + 2531011);
	return (g_seed >> 16) & 0x7FFF;
}
//-----------------------------------------------------------------------------------------------------------------------------
int how_many_around(int x, int y, int solved[][20], int a) {
	int mines = 0;
	if (solved[x + 1][y + 1] == a && y != column - 1 && x != row - 1) {
		mines++;
	}
	if (solved[x + 1][y - 1] == a && y != 0 && x != row - 1) {
		mines++;
	}
	if (solved[x - 1][y + 1] == a && y != column - 1 && x != 0) {
		mines++;
	}
	if (solved[x - 1][y - 1] == a && y != 0 && x != 0) {
		mines++;
	}
	if (solved[x - 1][y] == a && x != 0) {
		mines++;
	}
	if (solved[x + 1][y] == a && x != row - 1) {
		mines++;
	}
	if (solved[x][y + 1] == a && y != column - 1) {
		mines++;
	}
	if (solved[x][y - 1] == a && y != 0) {
		mines++;
	}
	return mines;
}
//-----------------------------------------------------------------------------------------------------------------------------
char inttos(int a) {
	switch (a)
	{
	case (1):
		return '1';
	case (2):
		return '2';
	case (3):
		return '3';
	case (4):
		return '4';
	case (5):
		return '5';
	case (6):
		return '6';
	case (7):
		return '7';
	case (8):
		return '8';
	}
}
//-----------------------------------------------------------------------------------------------------------------------------
void open_map(char play[][20], int solved[][20], int x, int y) {
	if (how_many_around(x, y, solved, 0) == 0) {
		return;
	}
	if (x != 0) {
		if (solved[x - 1][y] == 0) {
			solved[x - 1][y] = 9;
			open_map(play, solved, x - 1, y);
		}
	}
	if (x != row - 1) {
		if (solved[x + 1][y] == 0) {
			solved[x + 1][y] = 9;
			open_map(play, solved, x + 1, y);
		}
	}
	if (y != 0) {
		if (solved[x][y - 1] == 0) {
			solved[x][y - 1] = 9;
			open_map(play, solved, x, y - 1);
		}
	}
	if (y != column - 1) {
		if (solved[x][y + 1] == 0) {
			solved[x][y + 1] = 9;
			open_map(play, solved, x, y + 1);
		}
	}
	if (x != 0 && y != column - 1) {
		if (solved[x - 1][y + 1] == 0) {
			solved[x - 1][y + 1] = 9;
			open_map(play, solved, x - 1, y + 1);
		}
	}
	if (x != row - 1 && y != 0) {
		if (solved[x + 1][y - 1] == 0) {
			solved[x + 1][y - 1] = 9;
			open_map(play, solved, x + 1, y - 1);
		}
	}
	if (x != 0 && y != 0) {
		if (solved[x - 1][y - 1] == 0) {
			solved[x - 1][y - 1] = 9;
			open_map(play, solved, x - 1, y - 1);
		}
	}
	if (x != row - 1 && y != column - 1) {
		if (solved[x + 1][y + 1] == 0) {
			solved[x + 1][y + 1] = 9;
			open_map(play, solved, x + 1, y + 1);
		}
	}
}
//-----------------------------------------------------------------------------------------------------------------------------
void shift_mines(int mines[][2], int start, int n) {
	if (start == n - 1) {
		return;
	}
	for (int i = start; i < n - 1; i++) {
		mines[i][0] = mines[i + 1][0];
		mines[i][1] = mines[i + 1][1];
	}
}
//-----------------------------------------------------------------------------------------------------------------------------
int remove_mine(int mines[][2], int x, int y, int n) {
	for (int i = 0; i < n; i++) {
		if (mines[i][0] == x && mines[i][1] == y) {
			shift_mines(mines, i, n);
			n--;
		}
	}
	return n;
}
//-----------------------------------------------------------------------------------------------------------------------------
int main() {
	int solved[20][20] = {}, x = 0, y = 0, mines = 0, mines_around = 0, flag = 0, pluses = 0, mine_x_y[100][2], flags;
	char play_ground[20][20] , operation;
	while (1) {
		printf("how many rows do you want your palyground to have?\nThe row number should be less than or equal to 20\n");
		scanf("%d", &row);
		while (row > 20) {
			system("cls");
			printf("The row number should be less than or equal to 20\n");
			scanf("%d", &row);
		}
		printf("how many column do you want your palyground to have?\nThe column number should be less than or equal to 20\n");
		scanf("%d", &column);
		while (column > 20) {
			system("cls");
			printf("The column number should be less than or equal to 20\n");
			scanf("%d", &column);
		}
		printf("how many mines do you want your palyground to have?\nThe mine number should be less than or equal to 100\n");
		scanf("%d", &mine_num);
		while (mine_num > 100) {
			system("cls");
			printf("The mine number should be less than or equal to 100\n");
			scanf("%d", &mine_num);
		}
		printf("Please wait while initializing the playground!!  ^___^\n\n");
		mines = 0;
		flag = 0;
		x = 0;
		y = 0;
		flags = 0;
		mines_around = 0;
		for (int a = 0; a < row; a++) {
			for (int b = 0; b < column; b++) {
				play_ground[a][b] = '+';
			}
		}
		for (int a = 0; a < row; a++) {
			for (int b = 0; b < column; b++) {
				solved[a][b] = 0;
			}
		}
		fast_srand(time(NULL));
		while (mines < mine_num) {
			x = fast_rand() % row;
			y = fast_rand() % column;
			if (solved[x][y] == 10) {
				continue;
			}
			mine_x_y[mines][0] = x;
			mine_x_y[mines][1] = y;
			solved[x][y] = 10;
			mines++;
		}
		for (int a = 0; a < row; a++) {
			for (int b = 0; b < column; b++) {
				if (solved[a][b] == 10) {
					continue;
				}
				mines_around = how_many_around(a, b, solved, 10);
				solved[a][b] = mines_around;
			}
		}
		printf("    ");
		for (int a = 1; a <= column; a++) {
			printf("%d ", a);
		}
		printf("\n");
		printf("    ");
		for (int a = 1; a <= column; a++) {
			printf("_ ");
		}
		printf("\n");
		for (int a = 0; a < row; a++) {
			printf("%d | ", a + 1);
			for (int b = 0; b < column; b++) {
				if (play_ground[a][b] == '+') {
					pluses++;
				}
				printf("%c ", play_ground[a][b]);
			}
			printf("|\n");
		}
		printf("    ");
		for (int a = 1; a <= column; a++) {
			printf("_ ");
		}
		printf("\n");
		while (1) {
			if (pluses == mines || mines == 0) {
				printf("CONGRATS, YOU WON  ^____^\n");
				break;
			}
			scanf("%d %d %c", &x, &y, &operation);
			y--;
			x--;
			if (solved[x][y] == 10 && operation == 'o') {
				printf("YOU LOST\n");
				break;
			}
			else if (solved[x][y] == 0 && operation == 'o') {
				solved[x][y] = 9;
				open_map(play_ground, solved, x, y);
				for (int a = 0; a < row; a++) {
					for (int b = 0; b < column; b++) {
						if (solved[a][b] == 9) {
							play_ground[a][b] = ' ';
						}
					}
				}
				for (int a = 0; a < row; a++) {
					for (int b = 0; b < column; b++) {
						if (play_ground[a][b] == ' ') {
							if (a != 0) {
								if (play_ground[a - 1][b] == '+') {
									play_ground[a - 1][b] = inttos(solved[a - 1][b]);
								}
							}
							if (a != row - 1) {
								if (play_ground[a + 1][b] == '+') {
									play_ground[a + 1][b] = inttos(solved[a + 1][b]);
								}
							}
							if (b != 0) {
								if (play_ground[a][b - 1] == '+') {
									play_ground[a][b - 1] = inttos(solved[a][b - 1]);
								}
							}
							if (b != column - 1) {
								if (play_ground[a][b + 1] == '+') {
									play_ground[a][b + 1] = inttos(solved[a][b + 1]);
								}
							}
							if (a != 0 && b != column - 1) {
								if (play_ground[a - 1][b + 1] == '+') {
									play_ground[a - 1][b + 1] = inttos(solved[a - 1][b + 1]);
								}
							}
							if (a != row - 1 && b != 0) {
								if (play_ground[a + 1][b - 1] == '+') {
									play_ground[a + 1][b - 1] = inttos(solved[a + 1][b - 1]);
								}
							}
							if (a != 0 && b != 0) {
								if (play_ground[a - 1][b - 1] == '+') {
									play_ground[a - 1][b - 1] = inttos(solved[a - 1][b - 1]);
								}
							}
							if (a != row - 1 && b != column - 1) {
								if (play_ground[a + 1][b + 1] == '+') {
									play_ground[a + 1][b + 1] = inttos(solved[a + 1][b + 1]);
								}
							}
						}
					}
				}
			}
			else if (operation == 'o') {
				if (play_ground[x][y] == '+' || play_ground[x][y] == 'f') {
					play_ground[x][y] = inttos(solved[x][y]);
				}
				else {
					printf("ok");
					flag = 1;
				}
			}
			else if (operation == 'f') {
				if (play_ground[x][y] == '+') {
					if (flags < mine_num) {
						play_ground[x][y] = 'f';
						mines = remove_mine(mine_x_y, x, y, mines);
						flags++;
					}
					else {
						flag = 3;
					}
				}
				else {
					flag = 1;
				}
			}
			else {
				flag = 2;
			}
			system("cls");
			printf("    ");
			for (int a = 1; a <= column; a++) {
				printf("%d ", a);
			}
			printf("\n");
			printf("    ");
			for (int a = 1; a <= column; a++) {
				printf("_ ");
			}
			printf("\n");
			pluses = 0;
			for (int a = 0; a < row; a++) {
				printf("%d | ", a + 1);
				for (int b = 0; b < column; b++) {
					if (play_ground[a][b] == '+') {
						pluses++;
					}
					printf("%c ", play_ground[a][b]);
				}
				printf("|\n");
			}
			printf("    ");
			for (int a = 1; a <= column; a++) {
				printf("_ ");
			}
			printf("\n");
			if (flag == 1) {
				printf("THIS CELL IS ALREADY OPENED!\n");
				flag = 0;
			}
			else if (flag == 2) {
				flag = 0;
				printf("INVALID COMMAND\n");
			}
			else if (flag == 3) {
				flag = 0;
				printf("NO MORE FLAGS ARE ALLOWED!!\n");
			}
		}
		printf("Do you want to play again?\n y for yes, n for no\n");
		scanf("\n%c", &operation);
		if (operation == 'N' || operation == 'n') {
			break;
		}
	}
	return 0;
}