#include<iostream>
#include<fstream>
using namespace std;
//CreateGrid class is basically creating the Puzzle grid according to user's file
class CreateGrid {
	char* Input_FileName;		//Input file name from where we have to take the words for making the Grid
	char* Output_FileName;		//Output file name where Grid need to store
	unsigned short Words;		//Number of words in Input file
	unsigned short Rows;		//Number of Rows of Grid
	unsigned short Columns;		//Number of Columns of Grid
	int* wordLength;			//The Array which stores the length of each word in the Input file
	int Longest_Word_Length;	//Storing the length of the longest word in this integer
	int TotalWords;				//Total words in the Input file
	char** PuzzleGrid;			//2D Array which stores the Puzzle grid
	char** FileData;			//2D Array which stores the data extracted from the Input File
public:
	//Constructor initializing the members of CreateGrid class
	CreateGrid()
	{
		Words = 0;
		Rows = 0;
		Columns = 0;
		TotalWords = 0;
		Longest_Word_Length = 0;
		wordLength = nullptr;
		Input_FileName = nullptr;
		Output_FileName = nullptr;
		PuzzleGrid = nullptr;
		FileData = nullptr;
	}
	//StrLen function finds the length of the specific Word
	int StrLen(string _string)
	{
		int _stringLength = NULL;

		for (int index = NULL; _string[index] != '\0'; index++)
			_stringLength++;

		return _stringLength;
	}
	//It actually return a char pointer and return the array which has created on heap
	char* getstringfrombuffer(char* temp)
	{
		int Length = StrLen(temp);

		char* stringfrombuffer = new char[Length + 2];
		int counter = 0;
		for (char* i = temp; *i != '\0'; i++, counter++)
		{
			stringfrombuffer[counter] = *i;
		}
		stringfrombuffer[counter] = '\0';

		return stringfrombuffer;
	}
	//Input_Information takes the input from the user i.e, it takes the Number of words in the file, Number of Rows and Columns
	void Input_Information()
	{
		char temporary[20];
		cout << "Name of Input File: ";
		cin >> temporary;
		Input_FileName = getstringfrombuffer(temporary);

		cout << "Number of Words: ";
		cin >> Words;

		cout << "Number of Rows: ";
		cin >> Rows;

		cout << "Number of Columns: ";
		cin >> Columns;

		cout << "Name of Output File: ";
		cin >> temporary;
		Output_FileName = getstringfrombuffer(temporary);
	}
	//Extracting the data from the File
	void LoadDatafromFile()
	{
		ifstream file(Input_FileName);
		char tempbuffer[45];	//temporary char Array which size is 45 because the longest word exist in this world in the name of diseases which length is 45.
		while (!file.eof())		//Reading the file until end of file
		{
			file.getline(tempbuffer, 45);	//Reading the line and storing it in the temporary char Array
			TotalWords++;					//where Rows are for counting the words in the file
		}
		wordLength = new int[TotalWords];

		ifstream Refile(Input_FileName);	//Again Opening the file for storing the data of file on heap 
		FileData = new char* [TotalWords];		//...Allocation of Rows on heap
		int k = 0;
		while (!Refile.eof())
		{
			Refile.getline(tempbuffer, 45);

			int i = 0;
			for (; tempbuffer[i] != '\0'; i++);		//counting the length of particular word
			*(FileData + k) = new char[i + 1];		//Allocation of Columns on heap
			wordLength[k] = i;				//Storing the length of the word in the array of Wordlength
			//----------------Storing the data of file on the heap----------------
			int d = 0;
			char* j;
			for (j = *(FileData + k); tempbuffer[d] != '\0'; j++, d++)
			{
				if (tempbuffer[d] != 32)
				{
					*j = tempbuffer[d];
				}
				else
				{
					j--;
					wordLength[k]--;
				}
			}
			*j = '\0';
			k++;
		}
		//-------------Calculating the length of longest Word
		for (int h = 0; h < TotalWords; h++)
		{
			if (Longest_Word_Length < wordLength[h])
			{
				Longest_Word_Length = wordLength[h];
			}
		}
	}
	//Initializing the puzzle
	bool initPuzzle()
	{
		if (Longest_Word_Length > Rows && Longest_Word_Length > Columns)
		{
			cout << "Grid cannot be formed, ";
			system("pause");
			return false;
		}
		PuzzleGrid = new char* [Rows + 1];
		for (char i = 0; i < Rows + 1; i++)
		{
			//Allocation of max+1 Rows on heap +1 just for safety purposes
			*(PuzzleGrid + i) = new char[Columns + 1];
			for (char j = 0; j < Columns + 1; j++)
			{
				//First of all, initializaling the complete Array with * for the checking reason whether it is filled or not 
				PuzzleGrid[i][j] = '*';
			}
		}
		return true;
	}
	//Diagonal Top Left to bottom Right
	bool DiagonalL_R_D(int a, int b)
	{
		int count = 0;
		for (int i = a, j = b; i < Rows + 1; i++, j++)
		{
			if (PuzzleGrid[i][j] == '*')
			{
				count++;
			}
			if (PuzzleGrid[i][j] != '*')
			{
				return false;
			}
			int temp = 0;
			for (int h = 0; h < TotalWords; h++)
			{
				if (temp < wordLength[h])
				{
					temp = wordLength[h];
				}
			}
			for (int h = 0; h < TotalWords; h++)
			{
				if (count == wordLength[h] && wordLength[h] > 0 && count == temp)
				{
					int k = 0;
					for (int e = a, f = b; e <= i; e++, f++, k++)
					{
						PuzzleGrid[e][f] = FileData[h][k];
					}
					wordLength[h] = 0;
					return true;
				}
			}
		}
		return false;
	}
	//Diagonal bottom Left to top Right 
	bool DiagonalL_R_U(int a, int b)
	{
		int count = 0;
		for (int i = a, j = b; i >= 0 && j < Columns; i--, j++)
		{
			if (PuzzleGrid[i][j] == '*')
			{
				count++;
			}
			if (PuzzleGrid[i][j] != '*')
			{
				return false;
			}
			int temp = 0;
			for (int h = 0; h < TotalWords; h++)
			{
				if (temp < wordLength[h])
				{
					temp = wordLength[h];
				}
			}
			for (int h = 0; h < TotalWords; h++)
			{
				if (count == wordLength[h] && wordLength[h] > 0 && count == temp)
				{
					int k = 0;
					for (int e = a, f = b; e >= i && f <= j; e--, f++, k++)
					{
						PuzzleGrid[e][f] = FileData[h][k];
					}
					wordLength[h] = 0;
					return true;
				}
			}
		}
		return false;
	}
	//Diagonal Top Right to bottom Left 
	bool DiagonalR_L_D(int a, int b)
	{
		int count = 0;
		for (int i = a, j = b; i < Rows + 1 && j >= 0; i++, j--)
		{
			if (PuzzleGrid[i][j] == '*')
			{
				count++;
			}
			if (PuzzleGrid[i][j] != '*')
			{
				return false;
			}
			int temp = 0;
			for (int h = 0; h < TotalWords; h++)
			{
				if (temp < wordLength[h])
				{
					temp = wordLength[h];
				}
			}
			for (int h = 0; h < TotalWords; h++)
			{
				if (count == wordLength[h] && wordLength[h] > 0 && count == temp)
				{
					int k = 0;
					for (int e = a, f = b; e <= i && f >= j; e++, f--, k++)
					{
						PuzzleGrid[e][f] = FileData[h][k];
					}
					wordLength[h] = 0;
					return true;
				}
			}
		}
		return false;
	}
	//Diagonal bottom Right to top Left	
	bool DiagonalR_L_U(int a, int b)
	{
		int count = 0;
		for (int i = a, j = b; i >= 0 && j >= 0; i--, j--)
		{
			if (PuzzleGrid[i][j] == '*')
			{
				count++;
			}
			if (PuzzleGrid[i][j] != '*')
			{
				return false;
			}
			int temp = 0;
			for (int h = 0; h < TotalWords; h++)
			{
				if (temp < wordLength[h])
				{
					temp = wordLength[h];
				}
			}
			for (int h = 0; h < TotalWords; h++)
			{
				if (count == wordLength[h] && wordLength[h] > 0 && count == temp)
				{
					int k = 0;
					for (int e = a, f = b; e >= i && f >= j; e--, f--, k++)
					{
						PuzzleGrid[e][f] = FileData[h][k];
					}
					wordLength[h] = 0;
					return true;
				}
			}
		}
		return false;
	}
	//Vertical Up to down
	bool Vertical_D(int a, int b)
	{
		int count = 0;
		for (int i = a; i < Rows + 1; i++)
		{
			if (PuzzleGrid[i][b] == '*')
			{
				count++;
			}
			if (PuzzleGrid[i][b] != '*')
			{
				return false;
			}
			int temp = 0;
			for (int h = 0; h < TotalWords; h++)
			{
				if (temp < wordLength[h])
				{
					temp = wordLength[h];
				}
			}
			for (int h = 0; h < TotalWords; h++)
			{
				if (count == wordLength[h] && wordLength[h] > 0 && count == temp)
				{
					int k = 0;
					for (int e = a; e <= i; e++, k++)
					{
						PuzzleGrid[e][b] = FileData[h][k];
					}
					wordLength[h] = 0;
					return true;
				}
			}
		}

		return false;
	}
	//Vertical Down to Up
	bool Vertical_U(int a, int b)
	{
		int count = 0;
		for (int i = a; i >= 0; i--)
		{
			if (PuzzleGrid[i][b] == '*')
			{
				count++;
			}
			if (PuzzleGrid[i][b] != '*')
			{
				return false;
			}
			int temp = 0;
			for (int h = 0; h < TotalWords; h++)
			{
				if (temp < wordLength[h])
				{
					temp = wordLength[h];
				}
			}
			for (int h = 0; h < TotalWords; h++)
			{
				if (count == wordLength[h] && wordLength[h] > 0 && count == temp)
				{
					int k = 0;
					for (int e = a; e >= i; e--, k++)
					{
						PuzzleGrid[e][b] = FileData[h][k];
					}
					wordLength[h] = 0;
					return true;
				}
			}
		}

		return false;
	}
	//Horizontal Left to Right
	bool Horizontal_R(int a, int b)
	{
		int count = 0;
		for (int i = b; i < Rows + 1; i++)
		{
			if (PuzzleGrid[a][i] == '*')
			{
				count++;
			}
			if (PuzzleGrid[a][i] != '*')
			{
				return false;
			}
			int temp = 0;
			for (int h = 0; h < TotalWords; h++)
			{
				if (temp < wordLength[h])
				{
					temp = wordLength[h];
				}
			}
			for (int h = 0; h < TotalWords; h++)
			{
				if (count == wordLength[h] && wordLength[h] > 0 && count == temp)
				{
					int k = 0;
					for (int e = b; e <= i; e++, k++)
					{
						PuzzleGrid[a][e] = FileData[h][k];
					}
					wordLength[h] = 0;
					return true;
				}
			}
		}

		return false;
	}
	//Horizontal Right to Left
	bool Horizontal_L(int a, int b)
	{
		int count = 0;
		for (int i = b; i >= 0; i--)
		{
			if (PuzzleGrid[a][i] == '*')
			{
				count++;
			}
			if (PuzzleGrid[a][i] != '*')
			{
				return false;
			}
			int temp = 0;
			for (int h = 0; h < TotalWords; h++)
			{
				if (temp < wordLength[h])
				{
					temp = wordLength[h];
				}
			}
			for (int h = 0; h < TotalWords; h++)
			{
				if (count == wordLength[h] && wordLength[h] > 0 && count == temp)
				{
					int k = 0;
					for (int e = b; e >= i; e--, k++)
					{
						PuzzleGrid[a][e] = FileData[h][k];
					}
					wordLength[h] = 0;
					return true;
				}
			}
		}

		return false;
	}
	//Creating the puzzle
	void Creating_Puzzle()
	{
		//Iteration for all the indices of Array until the Rows
		for (int i = 0; i < Rows; i++)
		{
			for (int j = 0; j < Columns; j++)
			{
				bool check = false;
				if (PuzzleGrid[i][j] == '*')
				{
					//Generating the random number between 1 and 8
					int a = rand() % 7 + 1;
					if (i == 0)
					{
						//Firstly place Horizontally
						if (Horizontal_R(i, j) && check == false)
						{
							check = true;
						}
					}
					switch (a)
					{
						//Horizontal Left to Right
					case 1:
						if (Horizontal_R(i, j) && check == false)
						{
							check = true;
						}
						//Horizontal Right to Left
					case 2:
						if (Horizontal_L(i, j) && check == false)
						{
							check = true;
						}
						//Vertical Up to down	
					case 3:
						if (Vertical_D(i, j) && check == false)
						{
							check = true;
						}
						//Vertical Down to Up	
					case 4:
						if (Vertical_U(i, j) && check == false)
						{
							check = true;
						}
						//Diagonal Top Left to bottom Right 	
					case 5:
						if (DiagonalL_R_D(i, j) && check == false)
						{
							check = true;
						}
						//Diagonal Top Right to bottom Left 	
					case 6:
						if (DiagonalR_L_D(i, j) && check == false)
						{
							check = true;
						}
						//Diagonal bottom Left to top Right 		
					case 7:
						if (DiagonalL_R_U(i, j) && check == false)
						{
							check = true;
						}
						//Diagonal bottom Right to top Left	
					case 8:
						if (DiagonalR_L_U(i, j) && check == false)
						{
							check = true;
						}
						//For default purpose we will check all the dimensions until check == true
					default:
					{
						if (DiagonalL_R_D(i, j) && check == false)
						{
							check = true;
						}
						if (Horizontal_R(i, j) && check == false)
						{
							check = true;
						}
						if (Horizontal_L(i, j) && check == false)
						{
							check = true;
						}
						if (Vertical_D(i, j) && check == false)
						{
							check = true;
						}
						if (DiagonalR_L_D(i, j) && check == false)
						{
							check = true;
						}
						if (DiagonalL_R_U(i, j) && check == false)
						{
							check = true;
						}
						if (DiagonalR_L_U(i, j) && check == false)
						{
							check = true;
						}
						if (Vertical_U(i, j) && check == false)
						{
							check = true;
						}
					}

					}
				}
			}
		}
		for (int i = 0; i < Rows + 1; i++)
		{
			for (int j = 0; j < Columns + 1; j++)
			{
				if (PuzzleGrid[i][j] == '*')
				{
					PuzzleGrid[i][j] = rand() % 24 + 65;
				}
			}
		}
	}
	//Finally, the Outputting the grid in the file and also outputting on console
	void Output()
	{
		ofstream out(Output_FileName);
		char c;
		for (int i = 0; i < Rows + 1; i++)
		{
			for (int j = 0; j < Columns + 1; j++)
			{
				if (PuzzleGrid[i][j] >= 97)
				{
					c = PuzzleGrid[i][j] - 32;
					cout << c << " ";
					out << c << " ";
				}
				else
				{
					c = PuzzleGrid[i][j];
					cout << c << " ";
					out << c << " ";
				}
			}
			cout << endl;
			out << endl;
		}
	}
};

//WordSearch class takes a grid from the file and takes words from from the file and tells the indices of words in the grid
class WordSearch {

	char* Words_Input_FileName;		//Words Input file Name where the words exist
	char* Grid_Input_FileName;		//Name of file where is the grid
	char* Output_FileName;			//Output file name where indices need to store
	unsigned short Rows;			//Number of Rows of grid
	unsigned short Columns;			//Number of Columns of grid
	int* wordLength;				//Storing the length of each word
	int TotalWords;					//Total words in the file
	unsigned short TotalLines;		//Total lines/Rows of Grid
	char** PuzzleGrid;				//2D Array of Grid
	char** FileData;				//2D Array for storing the data of words
	unsigned short testcases;		//Number of words for which we have find indices
	int** index;					//Index Array for storing the indices of all words

public:
	//Constructor initializing the members of WordSearch class
	WordSearch()
	{
		TotalLines = 0;
		testcases = 0;
		Rows = 0;
		Columns = 0;
		TotalWords = 0;
		wordLength = nullptr;
		Output_FileName = nullptr;
		PuzzleGrid = nullptr;
		FileData = nullptr;
		Words_Input_FileName = nullptr;
		Grid_Input_FileName = nullptr;
		index = nullptr;
	}
	//StrLen function finds the length of the specific Word
	int StrLen(string _string)
	{
		int _stringLength = NULL;

		for (int index = NULL; _string[index] != '\0'; index++)
			_stringLength++;

		return _stringLength;
	}
	//It actually return a char pointer and return the array which has created on heap
	char* getstringfrombuffer(char* temp)
	{
		int Length = StrLen(temp);

		char* stringfrombuffer = new char[Length + 2];
		int counter = 0;
		for (char* i = temp; *i != '\0'; i++, counter++)
		{
			stringfrombuffer[counter] = *i;
		}
		stringfrombuffer[counter] = '\0';

		return stringfrombuffer;
	}
	//Input_Information takes the input from the user i.e, File Name of Grid, File Name of Words and File Name of Output
	void Input_Information()
	{
		char temporary[20];
		cout << "Name of Input File which has a grid: ";
		cin >> temporary;
		Grid_Input_FileName = getstringfrombuffer(temporary);

		cout << "Name of File which has the Words to be Searched: ";
		cin >> temporary;
		Words_Input_FileName = getstringfrombuffer(temporary);

		cout << "Name of Output File: ";
		cin >> temporary;
		Output_FileName = getstringfrombuffer(temporary);
	}
	//Extracting the data from both Input Files
	void LoadDatafromFiles()
	{
		ifstream Gridfile(Grid_Input_FileName);
		char tempbuffer[100];	//temporary char Array which size is 45 because the longest word exist in this world in the name of diseases which length is 45.
		while (!Gridfile.eof())		//Reading the file until end of file
		{
			Gridfile.getline(tempbuffer, 100);	//Reading the line and storing it in the temporary char Array
			TotalLines++;					//where Rows are for counting the words in the file
		}
		Gridfile.close();
		ifstream ReGridfile(Grid_Input_FileName);	//Again Opening the file for storing the data of file on heap 
		PuzzleGrid = new char* [TotalLines];		//...Allocation of Rows on heap
		int k = 0;
		while (!ReGridfile.eof())
		{
			ReGridfile.getline(tempbuffer, 100);

			int i = 0;
			for (; tempbuffer[i] != '\0'; i++);		//counting the length of particular word
			*(PuzzleGrid + k) = new char[i + 1];		//Allocation of Columns on heap
										//Storing the length of the word in the array of Wordlength
			//----------------Storing the data of file on the heap----------------
			int d = 0;
			char* j;
			for (j = *(PuzzleGrid + k); tempbuffer[d] != '\0'; j++, d++)
			{
				if (tempbuffer[d] != 32)
				{
					*j = tempbuffer[d];
				}
				else
				{
					j--;
				}
			}
			*j = '\0';
			k++;
		}
		ReGridfile.close();

		ifstream Wordsfile(Words_Input_FileName);

		Wordsfile >> Rows >> Columns;
		Wordsfile >> testcases;
		Wordsfile.ignore(256, '\n');						//temporary char Array which size is 45 because the longest word exist in this world in the name of diseases which length is 45.
		while (!Wordsfile.eof())		//Reading the file until end of file
		{
			Wordsfile.getline(tempbuffer, 45);	//Reading the line and storing it in the temporary char Array
			TotalWords++;					//where Rows are for counting the words in the file
		}
		Wordsfile.close();
		wordLength = new int[TotalWords];

		ifstream ReWordsfile(Words_Input_FileName);	//Again Opening the file for storing the data of file on heap 
		FileData = new char* [TotalWords];		//...Allocation of Rows on heap
		k = 0;
		ReWordsfile >> Rows >> Columns;
		ReWordsfile >> testcases;
		testcases++;
		Wordsfile.ignore(256, '\n');

		while (!ReWordsfile.eof())
		{
			ReWordsfile.getline(tempbuffer, 45);

			int i = 0;
			for (; tempbuffer[i] != '\0'; i++);		//counting the length of particular word
			*(FileData + k) = new char[i + 1];		//Allocation of Columns on heap
			wordLength[k] = i;				//Storing the length of the word in the array of Wordlength
			//----------------Storing the data of file on the heap----------------
			int d = 0;
			char* j;
			for (j = *(FileData + k); tempbuffer[d] != '\0'; j++, d++)
			{
				if (tempbuffer[d] != 32)
				{
					*j = tempbuffer[d];
				}
				else
				{
					j--;
					wordLength[k]--;
				}
			}
			*j = '\0';
			//cout << "file: " << *(FileData + k) << endl;
			k++;
		}
		
		ReWordsfile.close();

	}
	//It actually Stores the indices of a particular word in Index Array
	void Inputting(int** index, int a, int i, int j, int Ni, int Nj)
	{
		index[a][0] = i;
		index[a][1] = j;
		index[a][2] = Ni;
		index[a][3] = Nj;
	}
	//Horizontal Left to Right
	bool Horizontal_R(int a, int b, int x)
	{
		int count = 0;
		int v = 0;
		for (int i = b, y = 0; v < wordLength[x]; i++, y++, v++)
		{
			if (FileData[x][y] == PuzzleGrid[a][i])
			{
				count++;
				if (count == wordLength[x])
				{
					return true;
				}
			}
			if (FileData[x][y] != PuzzleGrid[a][i])
			{
				return false;
			}

		}
		return false;
	}
	//Horizontal Right to Left
	bool Horizontal_L(int a, int b, int x)
	{
		int count = 0;
		for (int i = b, y = 0; i >= 0; i--, y++)
		{
			if (FileData[x][y] == PuzzleGrid[a][i])
			{
				count++;
				if (count == wordLength[x])
				{
					return true;
				}
			}
			if (FileData[x][y] != PuzzleGrid[a][i])
			{
				return false;
			}

		}
		return false;
	}
	//Vertical Up to down
	bool Vertical_D(int a, int b, int x)
	{
		int count = 0;
		for (int i = a, y = 0; i < Rows; i++, y++)
		{
			if (FileData[x][y] == PuzzleGrid[i][b])
			{
				count++;
				if (count == wordLength[x])
				{
					return true;
				}
			}
			if (FileData[x][y] != PuzzleGrid[i][b])
			{
				return false;
			}

		}
		return false;
	}
	//Vertical Down to Up
	bool Vertical_U(int a, int b, int x)
	{
		int count = 0;
		for (int i = a, y = 0; i >= 0; i--, y++)
		{
			if (FileData[x][y] == PuzzleGrid[i][b])
			{
				count++;
				if (count == wordLength[x])
				{
					return true;
				}
			}
			if (FileData[x][y] != PuzzleGrid[i][b])
			{
				return false;
			}

		}
		return false;
	}
	//Diagonal Top Left to bottom Right
	bool DiagonalL_R_D(int a, int b, int x)
	{
		int count = 0;
		for (int i = a, j = b, y = 0; i < Rows; i++, j++, y++)
		{
			if (FileData[x][y] == PuzzleGrid[i][j])
			{
				count++;
				if (count == wordLength[x])
				{
					return true;
				}
			}
			if (FileData[x][y] != PuzzleGrid[i][j])
			{
				return false;
			}

		}
		return false;
	}
	//Diagonal bottom Left to top Right 
	bool DiagonalL_R_U(int a, int b, int x, int c)
	{
		int count = 0;
		for (int i = a, j = b, y = 0; i >= 0 && j < c; i--, j++, y++)
		{
			if (FileData[x][y] == PuzzleGrid[i][j])
			{
				count++;
				if (count == wordLength[x])
				{
					return true;
				}
			}
			if (FileData[x][y] != PuzzleGrid[i][j])
			{
				return false;
			}

		}
		return false;
	}
	//Diagonal Top Right to bottom Left 
	bool DiagonalR_L_D(int a, int b, int x)
	{
		int count = 0;
		for (int i = a, j = b, y = 0; i < Rows && j >= 0; i++, j--, y++)
		{
			if (FileData[x][y] == PuzzleGrid[i][j])
			{
				count++;
				if (count == wordLength[x])
				{
					return true;
				}
			}
			if (FileData[x][y] != PuzzleGrid[i][j])
			{
				return false;
			}

		}
		return false;
	}
	//Diagonal bottom Right to top Left	
	bool DiagonalR_L_U(int a, int b, int x)
	{
		int count = 0;
		for (int i = a, j = b, y = 0; i >= 0 && j >= 0; i--, j--, y++)
		{
			if (FileData[x][y] == PuzzleGrid[i][j])
			{
				count++;
				if (count == wordLength[x])
				{
					return true;
				}
			}
			if (FileData[x][y] != PuzzleGrid[i][j])
			{
				return false;
			}

		}
		return false;
	}
	//Searching the Indices of words
	void searchindex()
	{
		//------Creating Array on heap for storing the indices
		index = new int* [testcases];
		for (int i = 0; i < testcases; i++)
		{
			//Creating 4 cols because of 4 indices
			index[i] = new int[4];
		}

		for (char a = 0; a < testcases; a++)
		{
			//Iteration for all the indices of Array until the Rows
			bool check = false;
			for (char i = 0; i < Rows; i++)
			{
				for (char j = 0; j < Columns; j++)
				{
					//Matching the first Index
					if (FileData[a][0] == PuzzleGrid[i][j])
					{
						//Horizontal Left to Right
						if (Horizontal_R(i, j, a) && check == false)
						{

							Inputting(index, a, i, j, i, j + (wordLength[a] - 1));

							check = true;
						}
						//Horizontal Right to Left
						if (Horizontal_L(i, j, a) && check == false)
						{

							Inputting(index, a, i, j, i, j - (wordLength[a] - 1));

							check = true;
						}
						//Vertical Up to down	
						if (Vertical_D(i, j, a) && check == false)
						{
							Inputting(index, a, i, j, i + (wordLength[a] - 1), j);

							check = true;
						}
						//Vertical Down to Up	
						if (Vertical_U(i, j, a) && check == false)
						{

							Inputting(index, a, i, j, i - (wordLength[a] - 1), j);

							check = true;
						}
						//Diagonal Top Left to bottom Right 	
						if (DiagonalL_R_D(i, j, a) && check == false)
						{

							Inputting(index, a, i, j, i + (wordLength[a] - 1), j + (wordLength[a] - 1));

							check = true;
						}
						//Diagonal bottom Left to top Right 
						if (DiagonalL_R_U(i, j, a, Columns) && check == false)
						{

							Inputting(index, a, i, j, i - (wordLength[a] - 1), j + (wordLength[a] - 1));

							check = true;
						}
						//Diagonal Top Right to bottom Left 	
						if (DiagonalR_L_D(i, j, a) && check == false)
						{

							Inputting(index, a, i, j, i + (wordLength[a] - 1), j - (wordLength[a] - 1));

							check = true;
						}
						//Diagonal Right bottom to Left Top
						if (DiagonalR_L_U(i, j, a) && check == false)
						{

							Inputting(index, a, i, j, i - (wordLength[a] - 1), j - (wordLength[a] - 1));

							check = true;
						}
					}
				}
			}
			if (check == false)
			{
				index[a][0] = -1;
				index[a][1] = -1;
				index[a][2] = -1;
				index[a][3] = -1;
			}
		}
	}
	//Outputting the Indices of Words in file as well as on console
	void Indices()
	{
		ofstream Out(Output_FileName);

		//---------Outputing the Indices in file as well as outputting on console
		for (int i = 1; i < testcases; i++)
		{
			for (int j = 0; j < 4; j++)		// j < 4 because of 4 indices 
			{
				if (index[i][j] == -1 && index[i][j] == -1 && index[i][j] == -1 && index[i][j] == -1)
				{
					Out << "Not Found";
					cout << "Not Found";
					break;
				}
				else
				{
					if (j == 0 || j == 2)
					{
						Out << '{';
						cout << '{';
					}

					Out << index[i][j];
					cout << index[i][j];

					if (j == 1 || j == 3)
					{
						Out << "}";
						cout << "}";
					}
					if (j == 0 || j == 2)
					{
						Out << ",";
						cout << ",";
					}
				}
			}
			Out << endl;
			cout << endl;
		}


	}

};

void main()
{
	cout << "---------------------CREATING THE PUZZLE AND FINDING THE INDEX-----------------" << endl << endl;
	//while User not press Q
	while (true)
	{
		cout << "----------------------Home Screen-------------------------" << endl;
		cout << "1.Create Grid" << endl << "2.Search Words from Grid" << endl << "3.Quit" << endl;
		cout << "Enter the Character: ";
		char character;	//Inputting the character for action according to it
		cin >> character;
		//If user press C then Create class will create the Grid
		if (character == 'C' || character == 'c')	
		{
			CreateGrid Grid;
			Grid.Input_Information();
			Grid.LoadDatafromFile();
			if (Grid.initPuzzle())
			{
				Grid.Creating_Puzzle();
				Grid.Output();
				cout << "For Returnig to HOME SCREEN, ";
				system("pause");
			}
		}//If user press S then SearchWords class will search the indices
		else if (character == 'S' || character == 's')	
		{
			WordSearch Search;
			Search.Input_Information();
			Search.LoadDatafromFiles();
			Search.searchindex();
			Search.Indices();
			cout << "For Returnig to HOME SCREEN, ";
			system("pause");

		}//If user press Q then program will quit
		else if (character == 'Q' || character == 'q') 
		{
			cout << endl << "-------------------HAVE A NICE DAY--------------------" << endl;
			return;
		}
	}
	
}