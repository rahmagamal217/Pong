#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>

int main()
{
    //First paddle position
    int x1=50;
    int y1=200;

    //Second paddle position
    int x2=750;
    int y2=200;

    //Ball position
    int bx=380;
    int by=300;

    //collision values
    int xvel=3;
    int yvel=3;

    //First player movement
    bool up1=false;
    bool down1=false;

    //Second player movement
    bool up2=false;
    bool down2=false;

    bool startGame=false;

    int score1=0;
    int score2=0;

    bool flag=false;

    bool playWithComputer=false;

    bool playing=false;


    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Ping Pong");
    window.setFramerateLimit(80);

    //First paddle
    sf::RectangleShape line1;
    line1.setSize(sf::Vector2f(150,10));
    line1.rotate(90);
    line1.setFillColor(sf::Color::White);

    //Second paddle
    sf::RectangleShape line2;
    line2.setSize(sf::Vector2f(150,10));
    line2.rotate(90);
    line2.setFillColor(sf::Color::White);

    //Ball
    sf::CircleShape ball;
    ball.setRadius(15);
    ball.setFillColor(sf::Color::White);

    //background image
    sf::Texture img ;
    img.loadFromFile("Sources/bg.jpeg");
    sf::Sprite image(img);

    //scores
    sf::Text info1;
    sf::Text info2;
    sf::Font font;
    font.loadFromFile("Sources/arial.ttf");
    info1.setFont(font);
    info2.setFont(font);
    info1.setFillColor(sf::Color::White);
    info2.setFillColor(sf::Color::White);
    info1.setPosition(200,20);
    info2.setPosition(550,20);
    info1.setCharacterSize(30);
    info2.setCharacterSize(30);

    sf::Text pauseMessage;
    pauseMessage.setFont(font);
    pauseMessage.setCharacterSize(30);
    pauseMessage.setPosition(200.f, 150.f);
    pauseMessage.setFillColor(sf::Color::White);
    pauseMessage.setString("1-Play with computer: please enter 1 \n 2-Two players: please enter 2");

    // Load the sounds used in the game
    sf::SoundBuffer ballSoundBuffer;
    if (!ballSoundBuffer.loadFromFile("Sources/ball.wav"))
        return EXIT_FAILURE;
    sf::Sound ballSound;
    ballSound.setBuffer(ballSoundBuffer);


    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                window.close();

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();

                //Start Game
            if(event.type==sf::Event::MouseButtonPressed){
                startGame=true;
                playing=true;
            }

            //Player One
            if(event.type==sf::Event::KeyPressed&&(event.key.code==sf::Keyboard::W)){
                up1=true;
            }
            if(event.type==sf::Event::KeyPressed&&(event.key.code==sf::Keyboard::S)){
                down1=true;
            }

            //Player Two
            if(event.type==sf::Event::KeyPressed&&(event.key.code==sf::Keyboard::Up)){
                up2=true;
            }
            if(event.type==sf::Event::KeyPressed&&(event.key.code==sf::Keyboard::Down)){
                down2=true;
            }

            //Playing with computer
            if(event.type==sf::Event::KeyPressed&&(event.key.code==sf::Keyboard::Num1)){
                playWithComputer=true;
                playing=true;
            }

            //Playing with two players
            if(event.type==sf::Event::KeyPressed&&(event.key.code==sf::Keyboard::Num2)){
                playing=true;
            }
        }
        //Playing with computer logic
        if(playWithComputer==true){
            up2=false;
            down2=false;
            if(y2>=100&&y2<400&&flag==false){
                y2+=5;
            }
            else{
                 flag=true;
                 y2-=5;
                 if(y2<=100){
                    flag=false;
                 }
            }
            line2.setPosition(x2,y2);
        }

        //Play game logic
        if(startGame==true){
           if(bx<0){
              startGame=false;
              playing=false;
              score2++;
              pauseMessage.setString("Player Two won\nLeft click mouse to restart or\nescape to exit");
              bx=380;
              by=300;
           }
           if(bx>750){
            startGame=false;
            playing=false;
            score1++;
            pauseMessage.setString("Player one won\nLeft click mouse to restart or\nescape to exit");
            bx=380;
            by=300;
           }
           //Moving paddles
           if(up1==true&&y1>50){
            y1-=30;
            up1=false;
           }
           if(down1==true&&y1<550){
            y1+=30;
            down1=false;
           }
           if(up2==true&&y1>50){
            y2-=30;
            up2=false;
           }
           if(down2==true&&y1<550){
            y2+=30;
            down2=false;
           }
           //if the ball hit the paddles, the ball move back to another side (x axis)
           if(line1.getGlobalBounds().intersects(ball.getGlobalBounds())==true||line2.getGlobalBounds().intersects(ball.getGlobalBounds())==true){
              ballSound.play();
              xvel*=-1;
           }
           //if the ball touch the top or the bottom The ball move back to another side (y axis)
           if(by<0 || by>550){
              ballSound.play();
              yvel*=-1;
           }
           bx+=xvel;
           by+=yvel;
        }
        ball.setPosition(bx,by);
        line1.setPosition(x1,y1);
        line2.setPosition(x2,y2);

        // turn string and integer values into text
        std::stringstream ss1;
        std::stringstream ss2;
        ss1<<score1<<" points";
        ss2<<score2<<" points";
        info1.setString(ss1.str());
        info2.setString(ss2.str());
        //back ground color for pause massage
        //clear screen
        window.clear(sf::Color(10,47,105));
        if(playing==true){
           window.draw(image);
           window.draw(line1);
           window.draw(line2);
           window.draw(ball);
           window.draw(info1);
           window.draw(info2);
        }
        else{
            window.draw(pauseMessage);
        }


        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
