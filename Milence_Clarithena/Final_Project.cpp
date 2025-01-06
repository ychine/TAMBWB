/*
    ________________________________________________________________________________
     M I L E N C E   C L A R I T H E N A   S T U D I O S 

     --   Benitez, Richelle Dorothy U.
     --   Flavier, Laurence James L.
     --   Santos, Milan Franco L.
     --   Ramos, Athena Eunice C.
     --   Santos, Claire Jasmine D.


    "Theo's Aerial Misfortune: Balloon Words Blitz" 2023

    - For the purpose of our final project in Fundamentals of Programming in C++
   _________________________________________________________________________________
*/


//SFML LIBRARIES
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"

#include <iostream>
#include <windows.h>                                                                                                                                                           //window functions
#include <stdlib.h>                                                                                                                                                            //for srand
#include <algorithm>                                                                                                                                                           //used sa transform
#include <ctime>                                                                                                                                                               //used sa Game void



using namespace std;

sf::Music music; // declaration for global music variable.. (global meaning, nde exclusive sa isang part ng program)

void clearScreen() {
    system("clear");
}

// (FUNCTION) TO CENTER TEXT

void centerText(const string& text, int customYPosition, float sleepDuration) {                                                 
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int screenWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int startPosition = (screenWidth - static_cast<int>(text.length())) / 2;

    COORD cursorPosition;
    cursorPosition.X = startPosition;
    cursorPosition.Y = customYPosition;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);

    for (int ii = 0; text[ii] != '\0'; ii++) {
        cout << text[ii];
        Sleep(sleepDuration);
    }
}

//dont worry about these, dineclare lang ang functions below because these functions need nasa ibabaw ng ating important functions like "story", "start", and etc. 
void stopMusic() 
{
    music.stop();
}

void menuPage(); 
void start();

void initiateReplay() {

    start();

}

///////////////////////////////////////////////////////////         G             A            M             E         /////////////////////////////////////////////////////////////


//dito nagdeclare ng array for words na igi-guess ng user
string chooseRandomWord() {
    string words[] = { "greed", "aero", "afloat", "inflate", "hatdog", "party", "conscientious", "burst", "birthday"};
    int index = rand() % 9; //chooses random from the 9 values declared.
    return words[index];
}



 // ** (FUNCTIONS) display word forda loopz pag naguess na ang letter

void displayWord(sf::RenderWindow& window, const string& word, const string& guessedLetters, sf::Font& font, int attemptsLeft, int points) {
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);

    string displayedWord;
    for (char letter : word) {
        if (guessedLetters.find(letter) != string::npos) {
            displayedWord += letter;
        }
        else {
            displayedWord += "_ ";
        }
    }

    text.setString(displayedWord); 
    text.setPosition((window.getSize().x - text.getGlobalBounds().width) / 2.0f, 700.f);
    window.draw(text);  // this block of code ay nagcenter/set ng position for the text ng displayedWord(see line 66.)


    // TO DISPLAY ATTEMPTS LEFT
    sf::Text attemptsText;
    attemptsText.setFont(font);
    attemptsText.setCharacterSize(30);
    attemptsText.setFillColor(sf::Color::Black);
    attemptsText.setString("Attempts left: " + to_string(attemptsLeft));
    
    attemptsText.setPosition((window.getSize().x - attemptsText.getGlobalBounds().width) / 2.0f, 800.f);
    window.draw(attemptsText); // ..again, positioning for the attemptsText

    // TO DISPLAY POINTS
    sf::Text pointsText;
    pointsText.setFont(font);
    pointsText.setCharacterSize(40);
    pointsText.setFillColor(sf::Color::Blue);
    pointsText.setString("Points: " + to_string(points));
    
    pointsText.setPosition((window.getSize().x - pointsText.getGlobalBounds().width) / 1.1f, 100.f);
    window.draw(pointsText); // ..again, positioning for the pointsText
}


//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 
 // ** (FUNCTIONS) eto naman ay for the texts sa dulo ng game loop. we created several versions of these below see void displayMessage,**2,**3


void displayMessage(sf::RenderWindow& window, const string& message, sf::Font& font) {

    //  WINDOW CLEARING with COLOR
    sf::Color customColor(153, 217, 234); 
    window.clear(customColor); // clears the window with the custom color natin which is sky blue



    //  TO SET THE FONT SETTINGS OF THE TEXT
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(35);
    text.setFillColor(sf::Color::Black);
    text.setString(message);
    text.setPosition((window.getSize().x - text.getGlobalBounds().width) / 2.f, (window.getSize().y - text.getGlobalBounds().height) / 2.5f);

    window.draw(text);
    window.display();


    sf::sleep(sf::seconds(3)); // Display the message for 3 seconds
}

// Just like displayMessage, displayMessage2 has the same function, but added another text along with it.. this is mainly used sa losing/gameover screen so.. it has the deadSprite (line 156)

void displayMessage2(sf::RenderWindow& window, const string& message1, const string& message2, sf::Font& font) {

    //  WINDOW CLEARING with COLOR
    sf::Color customColor(153, 217, 234);
    window.clear(customColor); // ---- clears the window with the custom color natin which is sky blue
    //------------------------------------------------------------------------------------------------v

    // to set TEXTURE for when the user LOSES
    sf::Texture deadTexture;
    if (!deadTexture.loadFromFile("dead.png")) {
        cerr << "Failed to load image: dead.png" << endl;
        return; 
    }
    
    sf::Sprite deadSprite;
    deadSprite.setTexture(deadTexture);
    float xPosition = (window.getSize().x - deadSprite.getGlobalBounds().width) / 1.95f;
    float yPosition = (window.getSize().y - deadSprite.getGlobalBounds().height) / 11.f;
    deadSprite.setPosition(xPosition, yPosition);

    float desiredWidth = 650.f;
    float desiredHeight = 1090.f;

    float scaleX = desiredWidth / deadTexture.getSize().x;
    float scaleY = desiredHeight / deadTexture.getSize().y;

    deadSprite.setTexture(deadTexture);
    deadSprite.setScale(scaleX, scaleY);
    //-----------------------------------------------------------------------------------v

    //FOR TEXT1
    sf::Text text1;
    text1.setFont(font);
    text1.setCharacterSize(30);
    text1.setFillColor(sf::Color::Black);
    text1.setString(message1);
    text1.setPosition((window.getSize().x - text1.getGlobalBounds().width) / 2.f, (window.getSize().y - text1.getGlobalBounds().height) / 2.5f - 50.f);

    //FOR TEXT2
    sf::Text text2;
    text2.setFont(font);
    text2.setCharacterSize(30);
    text2.setFillColor(sf::Color::Red);
    text2.setString(message2);

    
    text2.setPosition((window.getSize().x - text2.getGlobalBounds().width) / 2.f, (window.getSize().y - text2.getGlobalBounds().height) / 2.5f + 50.f); // Position it below the first message

    //DRAWING THE ELEMENTS
    window.draw(text1);
    window.draw(text2);
    window.draw(deadSprite);
    window.display();

    sf::sleep(sf::seconds(4)); // Display the messages for 3 seconds
}

// like displayMessag2 but shorter.. less functions.

void displayMessage3(sf::RenderWindow& window, const string& message, sf::Font& font) {

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(23);
    text.setFillColor(sf::Color::Black);
    text.setString(message);

    // Center the message horizontally and vertically
    text.setPosition((window.getSize().x - text.getGlobalBounds().width) / 38.f, (window.getSize().y - text.getGlobalBounds().height) / 100.f);

    window.draw(text);
    window.display();

}

// BOOL functions

// basically irereturn nya whether conditions if naguess na ung letters or not.. (guessedLetters)
bool gameWon(const string& word, const string& guessedLetters) {
    return all_of(word.begin(), word.end(), [&guessedLetters](char letter) {
        return guessedLetters.find(letter) != string::npos; // this string::npos is if the guessed letters is not found hence the "!".
        });
}

bool hasGuessedLetter(const string& guessedLetters, char guess) {
    return guessedLetters.find(guess) != string::npos;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

 // ** (MAIN FUNCTIONS) for the game..

void start() {

    srand(time(0));

    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktopMode, "Theo's Aerial Misfortune: Balloon Words Blitz", sf::Style::Fullscreen);

    // ICON of the game.
    sf::Image icon;
    icon.loadFromFile("icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    

    // MAIN GAME BG MUSIC
    sf::Music music;
    if (!music.openFromFile("gamebg.wav"))

    music.setVolume(20.f);
    music.play();
    music.setPlayingOffset(sf::seconds(0.f));

    sf::Font font;
    if (!font.loadFromFile("DePixelKlein.ttf")) {
    }
    //-------------------------------------------v

    // LOADS THE FIVE STAGES NI THEO LMAO
    sf::Texture theoTextures[5];
    for (int i = 0; i < 5; ++i) {
        string filename = "theo" + to_string(i) + ".png";
        if (!theoTextures[i].loadFromFile(filename)) {
            cerr << "Failed to load image: " << filename << endl;
        }
    }
    sf::Sprite theoSprite;

    float desiredWidth = 650.f;
    float desiredHeight = 1090.f;

    float scaleX = desiredWidth / theoTextures[0].getSize().x;
    float scaleY = desiredHeight / theoTextures[0].getSize().y;

    theoSprite.setTexture(theoTextures[0]);
    theoSprite.setScale(scaleX, scaleY);

    //-------------------------------------------------------------v

    // SOUND EFFECTS

    sf::SoundBuffer correctBuffer;
    if (!correctBuffer.loadFromFile("korek.wav")) {
        // handle loading error
    }
    sf::Sound correctSound;
    correctSound.setBuffer(correctBuffer);

    sf::SoundBuffer wrongBuffer;
    if (!wrongBuffer.loadFromFile("wrong.wav")) {
        // handle loading error
    }
    sf::Sound wrongSound;
    wrongSound.setBuffer(wrongBuffer);

    sf::SoundBuffer exitBuffer;
    if (!exitBuffer.loadFromFile("closewin.wav")) {
        // handle loading error
    }
    sf::Sound exitSound;
    exitSound.setBuffer(exitBuffer);

    sf::SoundBuffer deadBuffer;
    if (!deadBuffer.loadFromFile("titlered.wav")) {
        // handle loading error
    }
    sf::Sound deadSound;
    deadSound.setBuffer(deadBuffer);
    //----------------------------------------------

    bool playAgain = true;

    int points = 0; // initialized points here for each round. so if naulit ung program, this is the initial point ng player.

    while (playAgain) {
        while (playAgain) {
            
            string word = chooseRandomWord();
            string guessedLetters;
            int attemptsLeft = 5;
            bool wordGuessed = false;


            while (attemptsLeft > 0 && !wordGuessed) {
                sf::Color customColor(153, 217, 234); 
                window.clear(customColor);

                // Display the word
                displayWord(window, word, guessedLetters, font, attemptsLeft, points);

                theoSprite.setTexture(theoTextures[5 - attemptsLeft]);

                float xPosition = (window.getSize().x - theoSprite.getGlobalBounds().width) / 2.f;
                float yPosition = (window.getSize().y - theoSprite.getGlobalBounds().height) / 5.f;

                theoSprite.setPosition(xPosition, yPosition);

                window.draw(theoSprite);

                displayMessage3(window, "OBJECTIVE: Guess the word to save Theo.", font);

                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                    }
                    else if (event.type == sf::Event::TextEntered) {
                        char guess = static_cast<char>(event.text.unicode);

                        if (isalpha(guess)) {
                            guess = tolower(guess);

                            if (hasGuessedLetter(guessedLetters, guess)) {
        
                                continue;
                            }

                            guessedLetters += guess;

                            if (word.find(guess) == string::npos) {
                                //decrement attempts
                                attemptsLeft--;
                                wrongSound.play();
                            }
                            else {
                                // guessed correctly, increment points
                                points += 10;
                                correctSound.play();
                            }

                            // Display the word after each guess
                            displayWord(window, word, guessedLetters, font, attemptsLeft, points);

                            // Check for winning after each guess
                            if (gameWon(word, guessedLetters)) {
                                wordGuessed = true;
                            }
                        }
                    }
                }

                window.display();
            }
            if (wordGuessed) {
                displayMessage(window, "Congratulations! You guessed the word: " + word + "\n\n                    Your final score: " + to_string(points), font);
                displayMessage(window, "Do you want to keep going? (Y/N)", font);
            }
            else {
                deadSound.play();
                displayMessage2(window, "Sorry, you ran out of attempts. The correct word was: " + word, "You failed to save Theo.\n\n   Your final score: " + to_string(points), font);
                displayMessage(window, "Do you want to play again? (Y/N)", font);
                points = 0; // Reset points only when the user loses
            }

            // OPTION TO PLAY AGAIN

            sf::Event roundEvent;
            while (window.pollEvent(roundEvent)) {
                if (roundEvent.type == sf::Event::Closed) {
                    window.close();
                }
                else if (roundEvent.type == sf::Event::TextEntered) {
                    char response = static_cast<char>(roundEvent.text.unicode);
                    if (tolower(response) == 'y') {
                        displayMessage(window, "Loading..", font);
                        music.stop();
                        break;
                    }
                    else if (tolower(response) == 'n') {
                        music.stop();

                        displayMessage(window, "Returning to main menu..", font);
                        playAgain = false;

                        exitSound.play();
                        window.close();

                        menuPage();
                    }
                
                }
            }
        }

    }
}

///////////////////////////////////////////////////////////          S        T        O        R        Y         /////////////////////////////////////////////////////////////


class Slideshow {
public:
    Slideshow(sf::RenderWindow& window) : window(window), currentImageIndex(0) {}

    void addImage(const std::string& filename, sf::Time duration) {
        sf::Texture texture;
        if (texture.loadFromFile(filename)) {
            images.push_back(std::make_pair(texture, duration));
        }
        else {
            std::cerr << "Failed to load image: " << filename << std::endl;
        }
    }

    

    void addText(const std::string& text, sf::Time duration) {
        texts.push_back(std::make_pair(text, duration));
    }

    void run() {
        while (currentImageIndex < images.size()) {
            handleEvents();
            displayCurrentImage();

            sf::sleep(images[currentImageIndex].second);
            currentImageIndex++;
        }
    }

private:

    std::size_t currentSoundIndex = 0;
    std::size_t currentTextIndex = 0;

    void handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }

    sf::Time playSound() {
        sf::Time soundDuration = sf::Time::Zero;

        if (currentSoundIndex < sounds.size()) {
            sf::Sound sound(sounds[currentSoundIndex].first);
            sound.play();

            soundDuration = sounds[currentSoundIndex].second;
            currentSoundIndex++;
        }

        return soundDuration;
    }

    void displayCurrentImage() {
        window.clear();

        // Set texture and scale for the image
        sf::Sprite sprite(images[currentImageIndex].first);
        float desiredWidth = 970.f;
        float desiredHeight = 945.f;
        float scaleX = desiredWidth / images[currentImageIndex].first.getSize().x;
        float scaleY = desiredHeight / images[currentImageIndex].first.getSize().y;
        sprite.move(15.f, 0.f);
        sprite.setScale(scaleX, scaleY);

        // Draw the image
        window.draw(sprite);

        // Play sound and get the sound duration, skip for the first image
        sf::Time soundDuration = (currentImageIndex > 0) ? playSound() : sf::Time::Zero;

        // Set up and draw the rectangle shape behind the text
        sf::RectangleShape rectangle(sf::Vector2f(desiredWidth, 40.f)); // Adjust height as needed
        rectangle.setPosition(15.f, 800);
        rectangle.setFillColor(sf::Color(0, 0, 0, 150)); // Black with some transparency

        window.draw(rectangle);

        // Set up and draw the text if there are texts available
        if (currentTextIndex < texts.size()) {
            sf::Font font;
            if (font.loadFromFile("DePixelKlein.ttf")) {
                sf::Text text(texts[currentTextIndex].first, font);
                text.setCharacterSize(20);
                text.setFillColor(sf::Color::Yellow);

                // Calculate the position to center the text within the rectangle
                float textX = (desiredWidth - text.getLocalBounds().width) / 2.0f;
                float textY = (rectangle.getSize().y - text.getLocalBounds().height) / 3.5f;

                // Set the position of the text within the rectangle
                text.setPosition(rectangle.getPosition().x + textX, rectangle.getPosition().y + textY);
                window.draw(text);
                currentTextIndex++;
            }
            else {
                std::cerr << "Failed to load font." << std::endl;
            }
        }

        window.display();

        // Wait for the specified duration, including sound duration
        sf::sleep(images[currentImageIndex].second + soundDuration);
    }

    sf::RenderWindow& window;
    std::vector<std::pair<sf::Texture, sf::Time>> images;
    std::vector<std::pair<sf::SoundBuffer, sf::Time>> sounds;
    std::vector<std::pair<std::string, sf::Time>> texts;
    std::size_t currentImageIndex;
};

void dispMessageStory(sf::RenderWindow& window, const string& message, sf::Font& font) {
    sf::Color customColor(153, 217, 234); // Custom color with RGB components
    window.clear(customColor); // Clears the window with the custom color


    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);
    text.setString(message);

    // Center the message horizontally and vertically
    text.setPosition((window.getSize().x - text.getGlobalBounds().width) / 5.f, (window.getSize().y - text.getGlobalBounds().height) / 2.5f);

    window.draw(text);
    window.display();


    sf::sleep(sf::seconds(3)); // Display the message for 3 seconds
}

void dispMessageStory2(sf::RenderWindow& window, const string& message, sf::Font& font) {
    sf::Color customColor(153, 217, 234); // Custom color with RGB components
    window.clear(customColor); // Clears the window with the custom color


    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);
    text.setString(message);

    // Center the message horizontally and vertically
    text.setPosition((window.getSize().x - text.getGlobalBounds().width) / 4.f, (window.getSize().y - text.getGlobalBounds().height) / 2.5f);

    window.draw(text);
    window.display();


    sf::sleep(sf::seconds(1)); // Display the message for 3 seconds
}

void storyline() {

    sf::RenderWindow window;
    window.create(sf::VideoMode(1000, 950), "Theo's Aerial Misfortune: Balloon Words Blitz");
    window.setKeyRepeatEnabled(false);

    ShowWindow(window.getSystemHandle(), SW_MAXIMIZE);

    sf::Music music;
    if (!music.openFromFile("musicbg1.wav"))

    music.setVolume(20.f);
    music.play();
    music.setPlayingOffset(sf::seconds(0.f));

    Slideshow slideshow(window);
    slideshow.addImage("fram1.png", sf::seconds(3));
    slideshow.addText("<< At his Friend's House >>", sf::seconds(2));

    slideshow.addImage("fram2.png", sf::seconds(3));
    slideshow.addText("This is Theo.", sf::seconds(2));

    slideshow.addImage("fram3.png", sf::seconds(3));
    slideshow.addText("Because of his love for balloons,", sf::seconds(2));

    slideshow.addImage("fram4.png", sf::seconds(3));
    slideshow.addText("..he couldn't resist to take as many as possible during his friend's birthday party. ", sf::seconds(2));

    slideshow.addImage("fram5.png", sf::seconds(3));
    slideshow.addText("Theo happily left with five balloons.", sf::seconds(2));

    slideshow.addImage("fram6.png", sf::seconds(3));
    slideshow.addText("Walking on his way home, oblivious to the impending dangers across him..", sf::seconds(2));

    slideshow.addImage("fram7.png", sf::seconds(3));
    slideshow.addText("Uh oh.", sf::seconds(2));

    slideshow.addImage("fram8.png", sf::seconds(3));
    slideshow.addText("''Ahh!''", sf::seconds(2));

    slideshow.addImage("fram9.png", sf::seconds(3));
    
    sf::Font font;
    if (!font.loadFromFile("DePixelKlein.ttf")) {
    }

    slideshow.run();

    dispMessageStory(window, "Do you want to play now? (Y/N)", font);

    sf::Event event;
    while (window.waitEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();

        }
        else if (event.type == sf::Event::TextEntered) {
            char response = static_cast<char>(event.text.unicode);
            if (tolower(response) == 'y') {

                dispMessageStory2(window, "Loading..", font);
                music.stop();
                window.close();
                initiateReplay();

            }
            else if (tolower(response) == 'n') {
                music.stop();
                window.close();
                menuPage();
            }
        }
    }
}

///////////////////////////////////////////////////////////           I  N  S  T  R  U  C  T  I  O  N  S           /////////////////////////////////////////////////////////////


void instructions() {

    string insChoice;

    string htplay1 = "                                                                         ___ ___                             ";
    string htplay2 = "                                                                        |   Y   .-----.--.--.--.   ";
    string htplay3 = "                                                                        |.  1   |  _  |  |  |  |   ";
    string htplay4 = "                                                                        |.  _   |_____|________|   ";
    string htplay5 = "                                                                        |:  |   |                  ";
    string htplay6 = "                                                                        |::.|:. |                  ";
    string htplay7 = "                                                                        `--- ---'                  ";


    string htplayy1 = "                                                                         ___ ___                    __           ";
    string htplayy2 = "                                                                        |   Y   .-----.--.--.--.   |  |_.-----.  ";
    string htplayy3 = "                                                                        |.  1   |  _  |  |  |  |   |   _|  _  |  ";
    string htplayy4 = "                                                                        |.  _   |_____|________|   |____|_____|  ";
    string htplayy5 = "                                                                        |:  |   |                                ";
    string htplayy6 = "                                                                        |::.|:. |                                ";
    string htplayy7 = "                                                                        `--- ---'                                ";

    string htplayyy1 = "                                                                         ___ ___                    __             _______ __             ";
    string htplayyy2 = "                                                                        |   Y   .-----.--.--.--.   |  |_.-----.   |   _   |  .---.-.--.--.";
    string htplayyy3 = "                                                                        |.  1   |  _  |  |  |  |   |   _|  _  |   |.  1   |  |  _  |  |  |";
    string htplayyy4 = "                                                                        |.  _   |_____|________|   |____|_____|   |.  ____|__|___._|___  |";
    string htplayyy5 = "                                                                        |:  |   |                                 |:  |            |_____|";
    string htplayyy6 = "                                                                        |::.|:. |                                 |::.|                   ";
    string htplayyy7 = "                                                                        `--- ---'                                 `---'                   ";

    string balloon1 = "                                          AAA                                             ";
    string balloon2 = "                                      AAAAA AAAAA                                         ";
    string balloon3 = "                                   AAAAAAAA    AAAAAAAAAAAAA                              ";
    string balloon4 = "                                 AA       AAAAA    AAA     AA                             ";
    string balloon5 = "                              AAAA        AA         AA     AA                            ";
    string balloon6 = "                            AAA AA        A           A      A                            ";
    string balloon7 = "                            A    AA       A           A     AA                            ";
    string balloon8 = "                            A     AA      AA         AA     A                             ";
    string balloon9 = "                            AA     AAAAAAAAAAA      AA    AA                              ";
    string balloon10 = "                             AAA     AAA AAAAAAAAAAAAAAAAA                                ";
    string balloon11 = "                               AAAAAAAA   A A   A  AA                                     ";
    string balloon12 = "                                      A   A A   A  A                                      ";
    string balloon13 = "                                      AA  AAA  AA AA                                      ";
    string balloon14 = "                                       AA AAA  AA A                                       ";
    string balloon15 = "                                        AA AA AAAA                                        ";
    string balloon16 = "                                         A AA AAA                                         ";
    string balloon17 = "                                         A AAAAAA                                         ";
    string balloon18 = "                                         AAAAAAAA                                         ";
    string balloon19 = "                                         AAAAA A                                          ";
    string balloon20 = "                                         AAAAA A                                          ";
    string balloon21 = "                                          AAAAAA                                          ";

    string paragra1 = "                                         __| |____________________________________________| |__                 __| |____________________________________________| |__";
    string paragra2 = "                                        (__   ____________________________________________   __)               (__   ____________________________________________   __)";
    string paragra3 = "                                           | |           >>  DESCRIPTION  <<              | |                     | |           >>  ABOUT THE GAME  <<           | |";
    string paragra4 = "                                           | |       Theo's Aerial Misfortune : BWB       | |                     | | Look deep within in our jumbled selection  | |";
    string paragra5 = "                                           | | is a console c++ word game that improves   | |                     | |     of words linked by Theo's trip.        | |";
    string paragra6 = "                                           | | your chances of guessing different types   | |                     | |  An interesting gameplay experience that   | |";
    string paragra7 = "                                           | | of words. An engaging game that puts your  | |                     | |  you can immerse yourself in. Take extra   | |";
    string paragra8 = "                                           | |    wordplay agenda and problem-solving     | |                     | |   care with your balloons!  Be cautious    | |";
    string paragra9 = "                                           | | abilities to the test. This game revolves  | |                     | |   of in error assumptions, since each one  | |";
    string paragra10 = "                                           | | on Theo's tale, which depends on you!      | |                     | | leads you closer to theo's tragic events!  | |";
    string paragra11 = "                                         __| |____________________________________________| |__                 __| |____________________________________________| |__";
    string paragra12 = "                                       (___  ____________________________________________   __)                (___  ____________________________________________   __)";
    string paragra13 = "                                          | |                                            | |                      | |                                            | |";


    string paragrap1 = "                                         __| |____________________________________________| |__                 __| |____________________________________________| |__";
    string paragrap2 = "                                        (__   ____________________________________________   __)               (__   ____________________________________________   __)";
    string paragrap3 = "                                           | |        >>  GAMEPLAY MECHANICS 1 <<         | |                     | |        >>  GAMEPLAY MECHANICS 2 <<         | |";
    string paragrap4 = "                                           | |   >> The goal of Theo's Wordplay is for    | |                     | | >> The game has two difficulties: simple   | |";
    string paragrap5 = "                                           | | players to guess the secret word hidden    | |                     | |   and challenging. The easy difficulty     | |";
    string paragrap6 = "                                           | | to suspend the balloons. Players can also  | |                     | | contains five sets of words with less than | |";
    string paragrap7 = "                                           | |  take turns choosing letters to narrow     | |                     | | five letters and just five balloons/lives. | |";
    string paragrap8 = "                                           | |  down the secret word that needs to guess. | |                     | | The insanity game difficulty features long | |";
    string paragrap9 = "                                           | | >> There's a word that shows in the game,  | |                     | |    phrases with just three balloon life.   | |";
    string paragrap10 = "                                           | |   choose random letter to accomplish it.   | |                     | | >> Watch out! and be alert on Theo's Life! | |";
    string paragrap11 = "                                         __| |____________________________________________| |__                 __| |____________________________________________| |__";
    string paragrap12 = "                                       (___  ____________________________________________   __)                (___  ____________________________________________   __)";
    string paragrap13 = "                                          | |                                            | |                      | |                                            | |";


    string allstrings4 = balloon1 + "\n" + balloon2 + "\n" + balloon3 + "\n" + balloon4 + "\n" + balloon5 + "\n" + balloon6 + "\n" + balloon7 + "\n" + balloon8 + "\n" + balloon9 + "\n" + balloon10 + "\n" + balloon11 + "\n" + balloon12 + "\n" + balloon13 + "\n" + balloon14 + "\n" + balloon15 + "\n" + balloon16 + "\n" + balloon17 + "\n" + balloon18 + "\n" + balloon19 + "\n" + balloon20 + "\n" + balloon21 + "\n";

    string allStrings1 = htplay1 + "\n" + htplay2 + "\n" + htplay3 + "\n" + htplay4 + "\n" + htplay5 + "\n" + htplay6 + "\n" + htplay7 + "\n";
    string allStrings2 = htplayy1 + "\n" + htplayy2 + "\n" + htplayy3 + "\n" + htplayy4 + "\n" + htplayy5 + "\n" + htplayy6 + "\n" + htplayy7 + "\n";
    string allStrings3 = htplayyy1 + "\n" + htplayyy2 + "\n" + htplayyy3 + "\n" + htplayyy4 + "\n" + htplayyy5 + "\n" + htplayyy6 + "\n" + htplayyy7 + "\n";


    string allstrings5 = paragra1 + "\n" + paragra2 + "\n" + paragra3 + "\n" + paragra4 + "\n" + paragra5 + "\n" + paragra6 + "\n" + paragra7 + "\n" + paragra8 + "\n" + paragra9 + "\n" + paragra10 + "\n" + paragra11 + "\n" + paragra12 + "\n" + paragra13 + "\n";
    string allstrings6 = paragrap1 + "\n" + paragrap2 + "\n" + paragrap3 + "\n" + paragrap4 + "\n" + paragrap5 + "\n" + paragrap6 + "\n" + paragrap7 + "\n" + paragrap8 + "\n" + paragrap9 + "\n" + paragrap10 + "\n" + paragrap11 + "\n" + paragrap12 + "\n" + paragrap13 + "\n";

    //cout << allstrings4 << endl;
    cout << "\n\n" << endl;
    cout << "\n\n" << endl;
    cout << "\n\n" << endl;
    cout << "\n\n" << endl;
    cout << "\n\n" << endl;
    cout << "\n\n" << endl;
    cout << "\n\n" << endl;
    PlaySound(TEXT("Explosionsound.wav"), NULL, SND_ASYNC);
    cout << allStrings1 << endl;
    system("Color 01");
    Sleep(900);
    system("cls");
    cout << "\n\n" << endl;
    cout << "\n\n" << endl;
    cout << "\n\n" << endl;
    cout << "\n\n" << endl;
    cout << "\n\n" << endl;
    cout << "\n\n" << endl;
    cout << "\n\n" << endl;
    PlaySound(TEXT("Explosionsound.wav"), NULL, SND_ASYNC);
    cout << allStrings2 << endl;
    Sleep(900);
    system("cls");
    cout << "\n\n" << endl;
    cout << "\n\n" << endl;
    cout << "\n\n" << endl;
    cout << "\n\n" << endl;
    cout << "\n\n" << endl;
    cout << "\n\n" << endl;
    cout << "\n\n" << endl;
    PlaySound(TEXT("Explosionsound.wav"), NULL, SND_ASYNC);
    cout << allStrings3 << endl;
    Sleep(900);
    system("cls");
    cout << "\n\n" << endl;
    PlaySound(TEXT("sahtpfinal.wav"), NULL, SND_ASYNC);
    cout << allStrings3 << endl;
    Sleep(900);
    PlaySound(TEXT("lineee.wav"), NULL, SND_ASYNC);
    cout << "===================================================================================================================================================================================================================\n" << endl;
    system("Color 09");
    Sleep(900);
    PlaySound(TEXT("desc.wav"), NULL, SND_ASYNC);
    cout << allstrings5 << endl;
    Sleep(1000);
    PlaySound(TEXT("desc.wav"), NULL, SND_ASYNC);
    cout << allstrings6 << endl;
    Sleep(1000);
    PlaySound(TEXT("lineee.wav"), NULL, SND_ASYNC);
    cout << "===================================================================================================================================================================================================================" << endl;
    Sleep(1000);
    cout << "\n\n" << endl;
    centerText("RETURN or PLAY GAME? (return/play:         )", 44, 0);
    cout << "\n\n" << endl;
    PlaySound(TEXT("lineee.wav"), NULL, SND_ASYNC);
    cout << "===================================================================================================================================================================================================================" << endl;
    COORD cursorPosition;
    cursorPosition.X = 118;
    cursorPosition.Y = 44;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);


    while (true) {
        cin >> insChoice;
        cin.ignore();

        transform(insChoice.begin(), insChoice.end(), insChoice.begin(), ::tolower);
        if (insChoice == "return") {
            system("cls");
            menuPage();
            break;
        }
        else if (insChoice == "play") {
            system("cls");
            start();
            break;
        }
        else {
            cout << "Please choose return or play." << endl;
            COORD cursorPosition;
            cursorPosition.X = 118;
            cursorPosition.Y = 44;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);

        }
    }
}

///////////////////////////////////////////////////////////         C     R     E     D     I     T     S          /////////////////////////////////////////////////////////////


void credits() {

        sf::RenderWindow window(sf::VideoMode(1930, 1080), "Credits....");

        sf::Font font;
        if (!font.loadFromFile("depixelklein.ttf"))
        {
            std::cerr << "Error loading font!" << std::endl;

        }



        sf::Text creditsText("                                                                                      << CREDITS >> \n\n\n\n\n\n\n\n                                                                         MILENCE CLARITHENA STUDIOS\n\n\n\n\n                                                                         BENITEZ, RICHELLE DOROTHY U.\n\n                                                                           FLAVIER,LAURENCE JAMES L. \n\n                                                                            SANTOS, MILAN FRANCO L.\n\n                                                                            RAMOS, ATHENA EUNICE C.\n\n                                                                           SANTOS, CLAIRE JAZMINE D.\n\n\n\n\n\n\n\n         BENITEZ, RICHELLE DOROTHY U. ................................................................................................................................................................... LEAD PROGRAMMER\n\n\n         FLAVIER,LAURENCE JAMES L.  .....................................................................................................................................................................  ASST. PROGRAMMER\n\n\n\n\n         BENITEZ, RICHELLE DOROTHY U. ................................................................................................................................................................... GRAPHIC DESIGNER\n\n\n         FLAVIER,LAURENCE JAMES L.     ................................................................................................................................................................... GRAPHIC DESIGNER\n\n\n\n\n         BENITEZ, RICHELLE DOROTHY U. ................................................................................................................................................................... SOUND EFFECTS\n\n\n         FLAVIER,LAURENCE JAMES L.     ................................................................................................................................................................... SOUND EFFECTS\n\n\n\n\n         BENITEZ, RICHELLE DOROTHY U. ................................................................................................................................................................... SCRIPT WRITER1\n\n\n         FLAVIER,LAURENCE JAMES L.     ................................................................................................................................................................... SCRIPT WRITER2\n\n\n\n\n         SANTOS, MILAN FRANCO L.      ..................................................................................................................................................................... STORYMAKER\n\n\n\n\n         FLAVIER,LAURENCE JAMES L.     ................................................................................................................................................................... PLAYTESTER\n\n\n         SANTOS, MILAN FRANCO L.      .................................................................................................................................................................... PLAYTESTER\n\n\n         BENITEZ, RICHELLE DOROTHY U. .................................................................................................................................................................. PLAYTESTER\n\n\n         RAMOS, ATHENA EUNICE C.   ....................................................................................................................................................................... PLAYTESTER\n\n\n         SANTOS, CLAIRE JAZMINE D.   ....................................................................................................................................................................... PLAYTESTER        \n\n", font, 23);
        creditsText.setFillColor(sf::Color::White);



        sf::FloatRect textRect = creditsText.getLocalBounds();
        creditsText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        creditsText.setPosition(window.getSize().x / 2.0f, window.getSize().y + textRect.height);

        float scrollSpeed = -130.0f;

        sf::Clock clock;
        sf::Music music;

        if (!music.openFromFile("endcred.mp3")) {
            std::cerr << "Error: Failed to load music file 'endcred.wav'" << std::endl;
        }

        music.setVolume(20.f);
        music.play();
        music.setPlayingOffset(sf::seconds(0.f));

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            float deltaTime = clock.restart().asSeconds();

            creditsText.move(0.0f, scrollSpeed * deltaTime);

            window.clear();
            window.draw(creditsText);
            window.display();

            if (music.getStatus() == sf::Music::Stopped) {
                window.close();

                menuPage();
            }
        }
}



///////////////////////////////////////////////////////////         E           X           I            T          /////////////////////////////////////////////////////////////



void exitGame() {
    cout << "Press ENTER to close the console.\n\n\n" << endl;
    ExitProcess(0);
}

///////////////////////////////////////////////////////////        M    A    I    N        M    E    N    U         /////////////////////////////////////////////////////////////


void menuPage() {

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    string titleChoice;


    cout << "\n" << endl;
    system("Color 07");

    system("cls");
    system("cls");
    system("cls");
    system("cls");
    system("cls");
    system("cls");

    cout << "\n" << endl;
    cout << "\n" << endl;
    cout << "\n" << endl;
    cout << "\n" << endl;
    cout << "\n" << endl;
    cout << "\n" << endl;
    cout << "\n" << endl;
    cout << "\n" << endl;
    cout << "\n" << endl;
    cout << "\n" << endl;
    cout << "\n" << endl;



    system("cls");

    string title1 = "     _______  __   __  _______  _______  __   _______   ";
    string title2 = "    |       ||  | |  ||       ||       ||  | |       |  ";
    string title3 = "    |_     _||  |_|  ||    ___||   _   ||__| |  _____|  ";
    string title4 = "      |   |  |       ||   |___ |  | |  |     | |_____   ";
    string title5 = "      |   |  |       ||    ___||  |_|  |     |_____  |  ";
    string title6 = "      |   |  |   _   ||   |___ |       |      _____| |  ";
    string title7 = "      |___|  |__| |__||_______||_______|     |_______|  ";



    string title8 = "     _______  __   __  _______  _______  __   _______    _______  _______  ______    ___   _______  ___       ";
    string title9 = "    |       ||  | |  ||       ||       ||  | |       |  |   _   ||       ||    _ |  |   | |   _   ||   |      ";
    string title10 = "    |_     _||  |_|  ||    ___||   _   ||__| |  _____|  |  |_|  ||    ___||   | ||  |   | |  |_|  ||   |      ";
    string title11 = "      |   |  |       ||   |___ |  | |  |     | |_____   |       ||   |___ |   |_||_ |   | |       ||   |      ";
    string title12 = "      |   |  |       ||    ___||  |_|  |     |_____  |  |       ||    ___||    __  ||   | |       ||   |___   ";
    string title13 = "      |   |  |   _   ||   |___ |       |      _____| |  |   _   ||   |___ |   |  | ||   | |   _   ||       |  ";
    string title14 = "      |___|  |__| |__||_______||_______|     |_______|  |__| |__||_______||___|  |_||___| |__| |__||_______|  ";


    string title15 = "     _______  __   __  _______  _______  __   _______    _______  _______  ______    ___   _______  ___        __   __  ___   _______  _______  _______  ______    _______  __   __  __    _  _______     ";
    string title16 = "    |       ||  | |  ||       ||       ||  | |       |  |   _   ||       ||    _ |  |   | |   _   ||   |      |  |_|  ||   | |       ||       ||       ||    _ |  |       ||  | |  ||  |  | ||       |  ___ ";
    string title17 = "    |_     _||  |_|  ||    ___||   _   ||__| |  _____|  |  |_|  ||    ___||   | ||  |   | |  |_|  ||   |      |       ||   | |  _____||    ___||   _   ||   | ||  |_     _||  | |  ||   |_| ||    ___| |   |";
    string title18 = "      |   |  |       ||   |___ |  | |  |     | |_____   |       ||   |___ |   |_||_ |   | |       ||   |      |       ||   | | |_____ |   |___ |  | |  ||   |_||_   |   |  |  |_|  ||       ||   |__   |___|";
    string title19 = "      |   |  |       ||    ___||  |_|  |     |_____  |  |       ||    ___||    __  ||   | |       ||   |___   |       ||   | |_____  ||    ___||  |_|  ||    __  |  |   |  |       ||  _    ||    ___|  ___ ";
    string title20 = "      |   |  |   _   ||   |___ |       |      _____| |  |   _   ||   |___ |   |  | ||   | |   _   ||       |  | ||_|| ||   |  _____| ||   |    |       ||   |  | |  |   |  |       || | |   ||   |___  |   | ";
    string title21 = "      |___|  |__| |__||_______||_______|     |_______|  |__| |__||_______||___|  |_||___| |__| |__||_______|  |_|   |_||___| |_______||___|    |_______||___|  |_|  |___|  |_______||_|  |__||_______| |___|";

    //SUBTITLE


    string subTitle1 = "                                                           ____        ____                    _       __               __         ____  ___ __        __";
    string subTitle2 = "===============================:::::::::::------          / __ )____ _/ / /___  ____  ____    | |     / /___  _________/ /____    / __ )/ (_) /_____  / /             ------:::::::::::============================";
    string subTitle3 = "==========::::::::::--------- - -                        / __  / __ `/ / / __  / __  / __     | | /| / / __  / ___/ __  / ___/   / __  / / / __/_  / / /                          - - ---------::::::::::==========";
    string subTitle4 = "=======::::::-- - -                                     / /_/ / /_/ / / / /_/ / /_/ / / / /   | |/ |/ / /_/ / /  / /_/ (__  )   / /_/ / / / /_  / /_/_/                                         - - --::::::=======";
    string subTitle5 = "                                                       /_____/ __,_/_/_/ ____/ ____/_/ /_/    |__/|__/ ____/_/    __,_/____/   /_____/_/_/ __/ /___(_)   ";


    //options
    string start1 = "                                                            >>=======================================<<     >>=======================================<<       ";
    string start2 = "                                                            ||_______ _______ _______  ______ _______||     ||_______ _______  _____   ______ __   __||    ";
    string start3 = "                                                            |||______    |    |_____| |_____/    |   ||     |||______    |    |     | |_____/   |_|  ||    ";
    string start4 = "                                                            ||______|    |    |     | |    |_    |   ||     ||______|    |    |_____| |    |_    |   ||    ";
    string start5 = "                                                            >>=======================================<<     >>=======================================<<   ";


    string instr1 = "                                                           >>=========================================================================================<<  ";
    string instr2 = "                                                           ||_____ __   _ _______ _______  ______ _     _ _______ _______ _____  _____  __   _ _______||  ";
    string instr3 = "                                                           ||  |   | |  | |______    |    |_____/ |     | |          |      |   |     | | |  | |______||  ";
    string instr4 = "                                                           ||__|__ |  |_| ______|    |    |    |_ |_____| |_____     |    __|__ |_____| |  |_| ______|||  ";
    string instr5 = "                                                           >>=========================================================================================<<  ";

    string creds1 = "                                                                             >>=====================================================<<                 ";
    string creds2 = "                                                                             ||_______  ______ _______ ______  _____ _______ _______||                 ";
    string creds3 = "                                                                             |||       |_____/ |______ |     |   |      |    |______||                 ";
    string creds4 = "                                                                             |||_____  |    |_ |______ |_____/ __|__  __|_   ______|||                 ";
    string creds5 = "                                                                             >>=====================================================<<                 ";

    string exits1 = "                                                                                         >>=============================<<                             ";
    string exits2 = "                                                                                         ||_______ _     _ _____ _______||                             ";
    string exits3 = "                                                                                         |||______  |___|    |      |   ||                             ";
    string exits4 = "                                                                                         |||______ _|   |_ __|__    |   ||                             ";
    string exits5 = "                                                                                         >>=============================<<                             ";


    string allStrings1 = title1 + "\n" + title2 + "\n" + title3 + "\n" + title4 + "\n" + title5 + "\n" + title6 + "\n" + title7 + "\n";

    string allStrings11 = title8 + "\n" + title9 + "\n" + title10 + "\n" + title11 + "\n" + title12 + "\n" + title13 + "\n" + title14 + "\n";

    string allStrings111 = title15 + "\n" + title16 + "\n" + title17 + "\n" + title18 + "\n" + title19 + "\n" + title20 + "\n" + title21 + "\n";


    ///sub
    string allStrings2 = subTitle1 + "\n" + subTitle2 + "\n" + subTitle3 + "\n" + subTitle4 + "\n" + subTitle5 + "\n";


    ///options
    string allStrings3 = start1 + "\n" + start2 + "\n" + start3 + "\n" + start4 + "\n" + start5 + "\n";

    string allStrings4 = instr1 + "\n" + instr2 + "\n" + instr3 + "\n" + instr4 + "\n" + instr5 + "\n";

    string allStrings5 = creds1 + "\n" + creds2 + "\n" + creds3 + "\n" + creds4 + "\n" + creds5 + "\n";

    string allStrings6 = exits1 + "\n" + exits2 + "\n" + exits3 + "\n" + exits4 + "\n" + exits5 + "\n";

    music.stop();

    PlaySound(TEXT("Explosionsound.wav"), NULL, SND_ASYNC);
    cout << allStrings1 << endl;
    Sleep(900);
    system("cls");

    cout << allStrings11 << endl;
    PlaySound(TEXT("Explosionsound.wav"), NULL, SND_ASYNC);
    Sleep(900);
    system("cls");

    SetConsoleTextAttribute(h, 4);
    cout << allStrings111 << endl;
    PlaySound(TEXT("titlered.wav"), NULL, SND_ASYNC);
    Sleep(1500);

    SetConsoleTextAttribute(h, 3);
    PlaySound(TEXT("bwbfx.wav"), NULL, SND_ASYNC);
    cout << allStrings2 << endl;
    Sleep(1500);

    SetConsoleTextAttribute(h, 8);
    PlaySound(TEXT("mcfx.wav"), NULL, SND_ASYNC);
    centerText("-------==============:::::::::::==========================:::::::::::==============-------", 14, 1.07f);
    SetConsoleTextAttribute(h, 3);
    centerText("     by Milence Clarithena Studios     ", 14, 1.10f);

    SetConsoleTextAttribute(h, 14);
    cout << "\n\n\n\n" << endl;
    Sleep(1000);

    //MENU
    cout << allStrings3 << endl;
    PlaySound(TEXT("pop.wav"), NULL, SND_ASYNC);
    Sleep(900);
    cout << allStrings4 << endl;
    PlaySound(TEXT("pop.wav"), NULL, SND_ASYNC);
    Sleep(900);
    cout << allStrings5 << endl;
    PlaySound(TEXT("pop.wav"), NULL, SND_ASYNC);
    Sleep(900);
    cout << allStrings6 << endl;
    PlaySound(TEXT("pop.wav"), NULL, SND_ASYNC);
    Sleep(900);

    if (!music.openFromFile("menumusic2.wav")) {
       
    } // error 
    music.play();
    music.setPlayingOffset(sf::seconds(0.f));

    SetConsoleTextAttribute(h, 3);
    centerText("Where do you want to go ? :", 45, 2); cout << endl;

    SetConsoleTextAttribute(h, 8);
   
   
    while (true) {
        centerText("---------------", 47, 0);
        COORD cursorPosition;
        cursorPosition.X = 99;
        cursorPosition.Y = 46;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);

        cin >> titleChoice;
        cin.ignore();

        transform(titleChoice.begin(), titleChoice.end(), titleChoice.begin(), ::tolower);

        if (titleChoice == "start") {
            
            stopMusic();
            system("cls");
            start();
            break;
        }
        else if (titleChoice == "story") {

            stopMusic();
            system("cls");
            storyline();
            break;
        }
        else if (titleChoice == "instructions") {

            stopMusic();
            system("cls");
            instructions();
            break;
        }
        else if (titleChoice == "credits") {

            stopMusic();
            system("cls");
            credits();
            break;
        }
        else if (titleChoice == "exit") {

            stopMusic();
            system("cls");
            exitGame();
            break;
        }
        else {
            COORD cursorPosition;
            cursorPosition.X = 88;
            cursorPosition.Y = 48;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
            cout << "Please choose between the options." << endl;
        }
    }
}



int main()

{
    // to maximize the window
    HWND console = GetConsoleWindow();
    ShowWindow(console, SW_MAXIMIZE);
    
    if (!music.openFromFile("menumusic.wav")) {
        return -1;
    } // error 

    music.play();
    music.setPlayingOffset(sf::seconds(0.f));

    centerText("Turn your SOUND ON for the best experience!", 5, 40);
    cout << endl << endl;
    centerText("PRESS ENTER to continue", 10, 30);
    cin.get();
    system("cls");
    centerText(" MILENCE CLARITHENA STUDIOS presents", 20, 100);
    Sleep(900);

    menuPage();


    return 0;
}
