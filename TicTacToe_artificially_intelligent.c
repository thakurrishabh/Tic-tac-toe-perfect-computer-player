#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>

int board[3][3], depth, diff = 5, p, tflag, flag, player = 1, co[2];
int temp[9][2] = { { 0,0 },{ 0,1 },{ 0,2 },{ 1,0 },{ 1,1 },{ 1,2 },{ 2,0 },{ 2,1 },{ 2,2 } };
struct node
{
	int coor[2];
	int matrix[3][3];
	int value;
	struct node *pm[9];
}*root = NULL;

void display()
{
	register int i, j, k = 1;
	printf("\n\t     Reference Matrix");
	printf("\n\n\t\t");

	for (i = 0;i < 3;i++)
	{
		for (j = 0;j < 3;j++, k++)
			printf(" %d ", k);
		printf("\n\n\t\t");
	}
	printf("Game Matrix");
	printf("\n\n\t\t");
	for (i = 0;i < 3;i++)
	{
		for (j = 0;j < 3;j++)
		{
			if (board[i][j] == 0)
				printf(" - ");
			else if (board[i][j] == 1)
				printf(" O ");
			else if (board[i][j] == 2)
				printf(" X ");
		}
		printf("\n\t\t");
	}
}

int validate()
{
	if (board[co[0]][co[1]] == 1 || board[co[0]][co[1]] == 2)
		return 1;
	else
		return 0;
}


int gameover(int board[3][3])
{
	register int i, j;
	if ((board[0][0] == 2 && board[1][1] == 2 && board[2][2] == 2) || (board[0][2] == 2 && board[1][1] == 2 && board[2][0] == 2) || (board[0][0] == 2 && board[0][1] == 2 && board[0][2] == 2) || (board[1][0] == 2 && board[1][1] == 2 && board[1][2] == 2) || (board[2][0] == 2 && board[2][1] == 2 && board[2][2] == 2) || (board[0][0] == 2 && board[1][0] == 2 && board[2][0] == 2) || (board[0][1] == 2 && board[1][1] == 2 && board[2][1] == 2) || (board[0][2] == 2 && board[1][2] == 2 && board[2][2] == 2))
		return 2;
	else if ((board[0][0] == 1 && board[1][1] == 1 && board[2][2] == 1) || (board[0][2] == 1 && board[1][1] == 1 && board[2][0] == 1) || (board[0][0] == 1 && board[0][1] == 1 && board[0][2] == 1) || (board[1][0] == 1 && board[1][1] == 1 && board[1][2] == 1) || (board[2][0] == 1 && board[2][1] == 1 && board[2][2] == 1) || (board[0][0] == 1 && board[1][0] == 1 && board[2][0] == 1) || (board[0][1] == 1 && board[1][1] == 1 && board[2][1] == 1) || (board[0][2] == 1 && board[1][2] == 1 && board[2][2] == 1))
		return 1;
	else
	{
		for (i = 0;i < 3;i++)
		{
			for (j = 0;j < 3;j++)
			{
				if (board[i][j] == 0)
					return 0;
			}

		}
		return 3;
	}
}

struct node *create(int i, int j, struct node *proot)
{
	register int k;
	register int i1, j1;
	struct node *temp = (struct node *)malloc(sizeof(struct node));
	if (proot == NULL)
	{
		memcpy(temp->matrix, board, 3 * 3 * sizeof(int));
		if (p == 1)
			temp->value = 100;
		else if (p == 2)
			temp->value = -100;
	}
	else
	{
		memcpy(temp->matrix, proot->matrix, 3 * 3 * sizeof(int));
		temp->matrix[i][j] = p;
		temp->coor[0] = i;
		temp->coor[1] = j;
		if (p == 2)
			temp->value = 100;
		else if (p == 1)
			temp->value = -100;
	}

	for (k = 0;k<9;k++)
		temp->pm[k] = NULL;
	return temp;
}

int mini(int a, int b)
{
	if (a>b)
		return b;
	else
		return a;
}

int maxi(int a, int b)
{
	if (a>b)
		return a;
	else
		return b;
}

struct node *insert(struct node *root, int i, int j, struct node *proot, int depth)
{
	int pos = -1;
	if (root == NULL)
	{
		tflag = 1;
		root = create(i, j, proot);
	}
	else
	{
		++depth;
		if (gameover(root->matrix) == 2)
			return root;
		else if (gameover(root->matrix) == 1)
			return root;
		else if (gameover(root->matrix) == 3)
			return root;

		for (i = 0;i < 3;i++)
		{
			for (j = 0;j < 3;j++)
			{
				if (root->matrix[i][j] == 0)
				{
					++pos;
					root->pm[pos] = insert(root->pm[pos], i, j, root, depth);
				}
			}
		}
	}
	return root;
}

int verify(struct node *root)
{
	int flag = 0;

	register int i, j;
	for (i = 0;i<3;i++)
	{
		for (j = 0;j<3;j++)
		{

			if (root->matrix[i][j] == 2)
				++flag;
		}
	}
	if (flag > 0)
		return 0;
	else
		return 1;
}

void seek(struct node *root, int *row, int *column)
{
	int pos = -1, num;
	struct node *temp1;
	register int i, j;

	if (verify(root))
	{
	re: {
		srand((int)time(NULL));
		num = (rand() % 9) + 1;
		if (num % 2 == 0)
			num = num + 1;
		if (root->matrix[temp[2][0]][temp[2][1]] != 0 || root->matrix[temp[0][0]][temp[0][1]] != 0 || root->matrix[temp[6][0]][temp[6][1]] != 0 || root->matrix[temp[8][0]][temp[8][1]] != 0)
			num = 5;
		if (root->matrix[temp[1][0]][temp[1][1]] != 0)
			num = 1;
		if (root->matrix[temp[7][0]][temp[7][1]] != 0)
			num = 9;
		if (root->matrix[temp[3][0]][temp[3][1]] != 0)
			num = 7;
		if (root->matrix[temp[5][0]][temp[5][1]] != 0)
			num = 3;
			if (root->matrix[temp[num-1][0]][temp[num-1][1]] != 0)
			goto re;
		*row = temp[num-1][0];
		*column = temp[num-1][1];
	}
	}
	else
	{
		for (i = 0;i < 3;i++)
		{
			for (j = 0;j < 3;j++)
			{

				if (root->matrix[i][j] == 0)
				{
					++pos;
					temp1 = root->pm[pos];
					if (temp1->value == root->value)
					{
						*row = i;
						*column = j;
					}
				}
			}
		}
	}
}



void ai()
{
	if (tflag == 0)
		return;
	else
		tflag = 0;

	root = insert(root, 0, 0, root, -1);

	if (p == 2)
		p = 1;
	else
		p = 2;
	++depth;
	ai();
}
void init()
{
	root = insert(NULL, 0, 0, NULL, -1);
}

struct node *minimax(struct node *root, int depth)
{
	int pos = -1;
	register int i, j;
	struct node *temp;
	++depth;
	if (gameover(root->matrix) == 2)
	{
		root->value = 11 - depth;

		flag = 1;
	}
	else if (gameover(root->matrix) == 1)
	{
		root->value = -11 + depth;
		flag = 1;
	}
	else if (gameover(root->matrix) == 3)
	{
		root->value = 1 - depth;
		flag = 1;
	}

	if (flag == 1)
	{
		flag = 0;
		return root;
	}

	for (i = 0;i < 3;i++)
	{
		for (j = 0;j < 3;j++)
		{
			if (root->matrix[i][j] == 0)
			{
				++pos;
				root->pm[pos] = minimax(root->pm[pos], depth);
				temp = root->pm[pos];
				if (depth % 2 == 0)
					root->value = maxi(temp->value, root->value);

				else if (depth % 2 != 0)
					root->value = mini(temp->value, root->value);

			}
		}
	}
	return root;
}


void gameplay()
{
rep: {
	int in;
	display();

	if (player == 1)
	{
		printf("\n\nplayer %d's turn", player);
		printf("\n\nenter the position number: ");
		scanf("%d", &in);
		if (in < 1 || in>9)
		{
			printf("\n\ninvalid input,try again");
			Sleep(2000);
			system("CLS");
			goto rep;
		}
		co[0] = temp[in - 1][0];
		co[1] = temp[in - 1][1];
	}
	else
	{
		depth = 0;
		p = player;
		init();
		ai();
		minimax(root, -1);
		seek(root, &co[0], &co[1]);
	}
	if (validate(2) || co[0]>2 || co[1]>2)
	{
		printf("\n\ninvalid input,try again");
		Sleep(2000);
		system("CLS");
		goto rep;
	}
	board[co[0]][co[1]] = player;
	display();
}
}


void main()
{
retry: {
	int end;
	char ch;
	SetConsoleTitle("TIC TAC TOE");
	printf("Who's gonna play first 1.You 2.Computer : ");
	ch = getchar();
	if (ch != '1' && ch != '2')
	{
		printf("\ninvalid input,try again");
		Sleep(2000);
		system("CLS");
		goto retry;
	}
	if (ch == '1')
		player = 1;
	else
		player = 2;
	system("CLS");
	while (1)
	{
		gameplay();
		system("CLS");
		end = gameover(board);
		if (end == 1 || end == 2)
		{
			display();
			if (player == 1)
				printf("\n\nYou win! , Impossible!!!!!!");
			else if (player == 2)
				printf("\n\nComputer Wins :P");
			_getch();
			exit(0);
		}
		else if (end == 3)
		{
			display();
			printf("\n\nIt's a draw...");
			_getch();
			exit(0);
		}
		if (player == 1)
			player = 2;
		else
			player = 1;
	}
}
}