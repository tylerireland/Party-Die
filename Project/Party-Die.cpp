
// Tyler Ireland
// CIS 1111
// 2/25/2021


//															Party Dice Game
//  -----------------------------------------------------------------------------------------------------------------------------------------------------------------
//
//						This is a simple drinking game that only rexuires two dice. You can have any number of players.
//					You roll both dice, trying to avoid certain dice arrangements, as well as scores.
//					Rolling certain arrangements will cost you a drink, or possibly a shot.
//					You must land on 100 exact, going over will result in a bust and will cost you a shot (Score returns to original value).

//						There is a main game that has certain dice arrangements as well as a custom game mode where the user can input
//					values for the dice and can set the instruction for that arrangement. The user will also set the instructions for reaching 
//					a score of 25, 50, 75, and going over 100.

//						A custom game will have nothing to do with drinking, it is completely up to the user to decide what to do.
//				    In a custom game, the user cannot decide to change the value of the player's score if landing on a certain arrangement or score.
//					There will still be a score value of 13 that will reset your score in a custom game.

// -------------------------------------------------------------------------------------------------------------------------------------------------------------------


//	I have been looking into the OpenCV library for C++ and I was messing around with object detection (with the help of youtube and open source codes obviously).
//  I want to make this game into one that can detect the value of the two dice being rolled and input those values and it's sum into the program, instead of using a
//  seeded random output between 1-6. This will make the game much more interactive.

//  This program used a lot of if statments because this game has many different prompts and options for the game (especially for a custom game).
//  I also added some exception handling with some while and if statements. I tried to make where the game would not crash unless you win or hit no for 
//  a new game. Please mess around with the inputs for this program and let me know if you can find any bugs.




#include<iostream>
#include<string>
#include<Windows.h>   //for Sleep command
#include<time.h>
#include<vector>

using namespace std;


// all variable are global for simplicity reasons (I made a few functions and needed to use some variables between them.)
int  sum,numPlayers, dieOneArrangement, dieTwoArrangement, dieOne, dieTwo;
unsigned int x;
char wannaPlay, newArrange, customGame;
bool game, newInstruction, customGamePlay, isInvalid, wrongFirst,isDupe;
string custDiceIns,cust25Ins,cust50Ins,cust75Ins,custOV100Ins;
vector<int> scoreBoard;
vector<int> already25;
vector<int> already50;
vector<int> already75;
vector<int> custdie1vector;
vector<int> custdie2vector;
vector<string> custDiceInsVector;

// creates and prints out the custom list of Instructions
void customInstructions() {

	// prints instructions for having custom inputs.
	Sleep(0750);
	cout << "\nYou can choose certain values for both dice as well as a custom instruction to add some variety!";
	Sleep(0750);
	cout << "Entering 'p' will print out all of your current arrangements." << endl;
	newInstruction = true;
	wrongFirst = true;
	Sleep(1000);

	
	// allows entry of new arrangements and checks for correct inputs and duplicates
	while (newInstruction) 
	{
		Sleep(0500);
		cout << endl;    	// Prompt for new arrangement
		
		cout << "Would you like to add an arrangement? (y/n/p): ";
		cin >> newArrange;
		cin.ignore();
		isInvalid = false;
		
				// new arrangement
		if (newArrange == 'y') 
		{
			// first custom dice value   
			cout << "    Enter a value for the first die: ";
			cin >> dieOneArrangement;
			cin.ignore();
			
			if (dieOneArrangement >= 1 && dieOneArrangement <= 6) 
			{
				custdie1vector.push_back(dieOneArrangement);
			}
			
			
			// if value is not 1-6, isInvalid will reset the while loop
			else 
			{  
				Sleep(0250);
				cout << "    Invalid Input..." << endl;						
				isInvalid = true;
			}
			
			// second custom dice value
			if (isInvalid == false) 
			{					
				cout << "    Enter a value for the second die: ";
				cin >> dieTwoArrangement;
				cin.ignore();

				// checks if between 1 and 6
				if (dieTwoArrangement >= 1 && dieTwoArrangement <= 6)     
				{
					isDupe = false;				// Resets the duplicate bool

					// checks if arrangement has already been made
					if (custdie1vector.size() > 0 && custdie2vector.size() > 0)
					{
						for (x = 0; x < custdie2vector.size(); x++)			
						{

							if (dieOneArrangement == custdie1vector[x] && dieTwoArrangement == custdie2vector[x])
							{
								isDupe = true;
							}
						}

						// tells user its a duplicate 
						if(isDupe)
						{
							isInvalid = true;
							Sleep(0500);
							cout << endl << "    You already have this arrangement!" << endl;
							custdie1vector.pop_back();
							Sleep(1000);
						}


						// if not a duplicate
						else 
						{
							custdie2vector.push_back(dieTwoArrangement);
						}
					}

					// for the first entry (vectors will not have anything so it sholdn't loop through)
					else
					{
						custdie2vector.push_back(dieTwoArrangement);
					}

				}

				// if user inputs a value other than 1-6
				else 
				{
					cout << "    Invalid Input..." << endl;
					custdie1vector.pop_back();			// removes the first die value for this arrangment
					isInvalid = true;
				}	


				// custom instruction input if values are valid
				if (isInvalid == false) 
				{
					// custom instruction
					cout << "\nEnter the custom instruction for this arrangement (This can be any short statment & will be displayed during the game): ";
					cout << "    ";
					getline(cin, custDiceIns);
					custDiceInsVector.push_back(custDiceIns);
				}
			}
		}
																				
				// when user is done inputting arrangements
		else if (newArrange == 'n') 
		{
			cout << "Enter the custom instruction for reaching 25: "; 
			getline(cin, cust25Ins);
			
			cout << "Enter the custom instruction for reaching 50: ";
			getline(cin, cust50Ins);
			
			cout << "Enter the custom instruction for reaching 75: ";
			getline(cin, cust75Ins);
			
			cout << "Enter the custom instruction for going over 100: ";
			getline(cin, custOV100Ins);
			
			newInstruction = false;
			break;
		}

				// extra for printing out list of arrangements
		else if (newArrange == 'p') 
		{
			if (custdie2vector.size() == 0)
			{
				cout << "You don't have any arrangements yet!" << endl;
			}
			else {
				for (x = 0; x < custdie2vector.size(); x++)
				{
					cout << "Arrangement #" << x + 1 << ": " << custdie1vector[x] << " & ";
					cout << custdie2vector[x] << endl;
				}
			}
		}

				// if user doesn't put 'y' or 'n'
		else 
		{
			cout << "Invalid Input..." << endl;
		}
	}
	
	
	// prints custom Instruction
	cout << "\n\t\tWelcome to Party Dice!" << endl << endl;
	Sleep(1000);
	cout << "The objective is to be the first to get to 100 by only rolling two dice. " << endl;
	Sleep(2000);
	cout << "This is your custom game! The instructions for score values will be normal. (At least until I add it)" << endl << endl;
	Sleep(2000);
	cout << "Here are your custom instructions for particular dice arrangements &  scores." << endl << endl;
	Sleep(1000);
	cout << "  _____________________________________________________ " << endl;
	cout << " |    Arrangement    |         Instruction             |" << endl;
	cout << " |___________________|_________________________________|" << endl;
	for (x = 0; x < custDiceInsVector.size(); x++) {
		cout << " |      '" << custdie1vector[x] << "' & '" << custdie2vector[x] << "'    |     " << custDiceInsVector[x] << endl;
	}
	cout << " | ------------------|-------------------------------- |" << endl;
	cout << " |       Score       |         Instruction             |" << endl;
	cout << " |___________________|_________________________________|" << endl;
	cout << " |        25         |     " << cust25Ins                 << endl;
	cout << " |        50         |     " << cust50Ins                 << endl;
	cout << " |        75         |     " << cust75Ins                 << endl;
	cout << " |        100        |         You Won !"                 << endl;
	cout << " |       >100        |     " << custOV100Ins              << endl;
	cout << " |        13         |      Go back to 0"                 << endl;
	cout << " |___________________|_________________________________"  << endl << endl;
	Sleep(2000);
	cout << "\tLet's Begin!" << endl << endl << endl;
	Sleep(2000);
}


// Prints out the base game instructions
void printInstructions() {   
	cout <<"\n\t\tWelcome to Party Dice!" << endl << endl;
	Sleep(1000);
	cout <<"The objective is to be the first to get to 100 by only rolling two dice. " << endl;
	Sleep(2000);
	cout <<"Landing on certain dice arrangements and having certain scores will cost you." << endl << endl;
	Sleep(2000);
	cout <<"Here are the instructions for particular dice arrangements & scores." << endl << endl;
	Sleep(1000);
	cout <<"  _____________________________________________________ " << endl;
	cout <<" |    Arrangement    |         Instruction             |" << endl;
	cout <<" |___________________|_________________________________|" << endl;
	cout <<" |    Snake eyes     |   Pick someone to take a shot   |" << endl;
	cout <<" |     Doubles       |   Take 1 shot & 1 drink         |" << endl;
	cout <<" |    '1' & '3'      |   Take 1 shot & 3 drinks        |" << endl;
	cout <<" | ------------------|-------------------------------- |" << endl;
	cout <<" |       Score       |         Instruction             |" << endl;
	cout <<" |___________________|_________________________________|" << endl;
	cout <<" |        25         |       Take 1 drink              |" << endl;
	cout <<" |        50         |       Take 1/2 shot             |" << endl;
	cout <<" |        75         |       Take 3 drinks             |" << endl;
	cout <<" |        100        |       Celebrate                 |" << endl;
	cout <<" |       >100        |       Take 1 shot               |" << endl;
	cout <<" |        13         |      Go back to 0               |" << endl;
	cout <<" |___________________|_________________________________|" << endl << endl;
	Sleep(2000);
	cout <<"\tLet's Begin!" << endl << endl << endl;
	Sleep(2000);
}


//rolls two dice and returns the sum
int diceRoll() {  

	cout <<" Press 'Enter' to roll the dice.";
	cin.get();	// waits for user to hit "enter"

	// two random values between 1-6 set for dice one and two
	dieOne = (rand() % 6) + 1;
	dieTwo = (rand() % 6) + 1;

	// print out dice one on screen
	Sleep(0750);
	cout <<"\t  .";
	Sleep(0750);
	cout <<".";
	Sleep(0750);
	cout <<". ";
	Sleep(0750);
	cout << dieOne << endl;

	// print out dice two on screen
	Sleep(0750);
	cout <<"\t  .";
	Sleep(0750);
	cout <<".";
	Sleep(0750);
	cout <<". ";
	Sleep(0750);
	cout << dieTwo << endl;
	 // prints out the sum
	Sleep(1000);
	cout <<"        You got " << (dieOne + dieTwo) << "!" << endl << endl;

	// custom game dice checker
	if (customGamePlay == true) 
	{
		// loop checks if dice match each custom arrangement
		for (unsigned int x = 0; x < custDiceInsVector.size(); x++) 
		{
			if (dieOne == custdie1vector[x] && dieTwo == custdie2vector[x]) 
			{
				Sleep(1000);
				cout << " That matches one of your custom arrangements!" << endl;
				Sleep(0500);
				cout << " Here is the instruction: " << custDiceInsVector[x] << endl;
			}
		}
		return dieOne + dieTwo;
	}

	// normal game dice checker
	else if(customGamePlay == false) 
	{
		if (dieOne == 1 && dieTwo == 1) 
		{
			Sleep(1000);
			cout << " Those look like snake eyes to me. \n   Pick someone to take a drink!" << endl << endl;
		}
		else if (dieOne == dieTwo) 
		{
			Sleep(1000);
			cout << "     Those are doubles! \n That calls for one shot and one drink." << endl << endl;
		}
		else if (dieOne == 1 && dieTwo == 3 || dieOne == 3 && dieTwo == 1) 
		{
			Sleep(1000);
			cout << " A one and a three? Sounds unlucky to me. \n    Take a shot and three drinks!" << endl << endl;
		}
		return dieOne + dieTwo;
	}
	
	// should never happen
	return dieOne + dieTwo;
}


// creates vectors for numPlayers and for reaching certain scores
void createScoreBoard() {   
	
	// if user has no friends to play with
	if (numPlayers < 2 && numPlayers >= 0) 
	{
		cout <<" Find some friends, loser..." << endl;
		Sleep(2000);
		exit(1);
	}
	
	// if user inputs a valid number of players
	else if (numPlayers >= 2) 
	{
		for (int i = 0;i <= numPlayers;i++) 
		{
			scoreBoard.push_back(0);
			already25.push_back(0);
			already50.push_back(0);
			already75.push_back(0);
		}
	}
	
	// if user inputs something other than a positive integer
	else {
		Sleep(1000);
		cout <<" What a joker..." << endl;
		exit(1);
	}
}


// this function will check the player's score for checkpoints or value exuivalencies
void testScore(int sum) { 

	// tests score for custom arrangements
	if (customGamePlay == true)
	{
		// cust25Ins,cust50Ins,cust75Ins
		if (scoreBoard[x] == 13)
		{
			cout << "Oof. You landed on unlucky number 13. You better restart..." << endl;
			scoreBoard[x] = 0;
			Sleep(2000);
		}
		else if (scoreBoard[x] == 99)
		{
			scoreBoard[x] = 98;
		}
		else if (scoreBoard[x] > 100)
		{
			cout << "    Oh no! You went over 100." << endl;
			cout << "    Instruction : " << custOV100Ins << endl;
			Sleep(0500);
			scoreBoard[x] -= sum;
		}
		else if (scoreBoard[x] == 100)
		{
			cout << "    You made it to 100!! You won!" << endl;
			game = 0;
			Sleep(7000);
			exit(1);
		}
		else if (scoreBoard[x] >= 75 && scoreBoard[x] < 100 && already75[x] == 0)
		{
			cout << "    You're at 75! So close..." << endl;
			cout << "    Instruction : " << cust75Ins << endl;
			already75[x] = 1;
		}
		else if (scoreBoard[x] >= 50 && scoreBoard[x] < 75 && already50[x] == 0)
		{
			cout << "    You're at 50! Halfways done, boss!" << endl;
			cout << "    Instruction : " << cust50Ins << endl;
			already50[x] = 1;
		}
		else if (scoreBoard[x] >= 25 && scoreBoard[x] < 50 && already25[x] == 0)
		{
			cout << "    25! Just getting warmed up!" << endl;
			cout << "    Instruction : " << cust25Ins << endl;
			already25[x] = 1;
		}
		else if (scoreBoard[x] == 69)
		{
			cout << " Nice." << endl;
		}
	}

	// tests score for normal game
	else if (customGamePlay == false)
	{
		if (scoreBoard[x] == 13) 
		{
			cout << "Oof. You landed on unlucky number 13. You better restart..." << endl;
			scoreBoard[x] = 0;
			Sleep(2000);
		}
		else if (scoreBoard[x] == 99) 
		{
			scoreBoard[x] = 98;
		}
		else if (scoreBoard[x] > 100) 
		{
			cout << "    Bust! Take a shot..." << endl;
			Sleep(0500);
			scoreBoard[x] -= sum;
		}
		else if (scoreBoard[x] == 100) 
		{
			cout << "    You made it to 100!! You won!" << endl;
			game = 0;
			Sleep(7000);
			exit(1);
		}
		else if (scoreBoard[x] >= 75 && scoreBoard[x] < 100 && already75[x] == 0) 
		{
			cout << " You're almost there! 3 more final drinks!" << endl;
			already75[x] = 1;
		}
		else if (scoreBoard[x] >= 50 && scoreBoard[x] < 75 && already50[x] == 0) 
		{
			cout << " Halfway! That means a half shot!" << endl;
			already50[x] = 1;
		}
		else if (scoreBoard[x] >= 25 && scoreBoard[x] < 50 && already25[x] == 0) 
		{
			cout << " Just getting warmed up! Take a swig!" << endl;
			already25[x] = 1;
		}
		else if (scoreBoard[x] == 69) 
		{
			cout << " Nice." << endl;
		}
	}
}


// where the game begins
int main() {	
	//seed for dice rolling
	srand(time(0));

	
	// Prompt for game start
	cout <<" Are you ready to play? (y/n): ";
	cin >> wannaPlay;
	cin.ignore(); // removes '\n' in keyboard buffer


	// if user does not want to play
	if (wannaPlay == 'n') 
	{
		Sleep(0500);
		cout <<" Goodbye!" << endl;
		Sleep(2000);
		game = 0;
		exit(1);
	}


	// if user wants to play
	else if (wannaPlay == 'y') 
	{
		game = true;

		// asks for number of players
		cout << endl << " Enter the number of players: ";
		cin >> numPlayers;
		cin.ignore();
		createScoreBoard();

		// asks if user would like to have custom arrangements
		cout << " \nWould you like to have custom arrangements and instructions? (y/n): ";
		cin >> customGame;
		cin.ignore();

		// prints custom instructions if custom game
		if (customGame == 'y') 
		{
			customGamePlay = true;
			customInstructions();
		}
		// prints regular instructions if normal game
		else if (customGame == 'n') 
		{
			printInstructions();
		}
		else
		{
			cout << "Invalid Input..." << endl << endl;
			Sleep(1500);
			cout << "Continuing to normal game..." << endl;
			Sleep(2000);
			printInstructions();
		}

		// game loop
		while (game) 
		{
			// loop for each player's turn
			for (x = 0; x < numPlayers; x++) 
			{
				Sleep(1000);
				cout <<"     Your turn, Player " << (x+1) << endl;
				Sleep(1000);
				// diceRoll returns the sum of the two dice rolled
				sum = diceRoll();
				// adds the sum to the player's score
				scoreBoard[x] += sum;
				Sleep(2000);
				
				// tests score for checkpoints and custom values
				testScore(sum);
				
				cout <<"    Your new score is: ";
				Sleep(0650);
				cout << scoreBoard[x] << endl << endl;
				Sleep(1500);
				cout <<"     ...Next Player..." << endl << endl;
				Sleep(1000);
				
			}
		}
	}


	// if user doesn't put 'y' or 'n'
	else 
	{
		Sleep(1500);
		cout <<" I said to put 'y' or 'n' ";
		Sleep(0750);
		cout <<". ";
		Sleep(0750);
		cout <<". ";
		Sleep(0750);
		cout <<". ";
		Sleep(0750);
		cout <<"not " << wannaPlay << "." << endl;
		Sleep(1000);
		exit(1);
	}




	system("pause");
	return 0;
}
