#pragma once
#include<iostream>
#include"User.h"
#include"Board.h"
#include"FileIO.h"
#include"StaticUser.h"
#include"GameController.h"

using namespace std;

class MainClass {
public:
	void playingGame() {
		GameController* controller = new GameController();
		Dealer* dealer = new Dealer();
		FileIO* fileIO = new FileIO();
		int playerNum = 3;
		int live[3] = { 1, 1, 1 };
		int* livePtr;
		int tempPlayerNum = 0;
		User winner;


		// 유저 생성 > 플레이어 수만큼
		for (int i = 0; i < playerNum; i++) {
			boolean flag = false;
			string tempId;
			int tempMoney = 0;

			fileIO->fileLoad();

			do {
				cout << "아이디를 입력해 주세요: ";
				cin >> tempId;
				tempMoney = fileIO->checkID(tempId);
			} while (tempMoney == -1);

			StaticUser::user[i] = *(new User(tempId, tempMoney));
			//user[i] = *(new User(tempId, tempMoney));
			cout << tempId << "객체가 생성되었습니다!" << endl;
			cout << StaticUser::user[i].getPlayerID() << " " << StaticUser::user[i].getAssets() << endl;
		}
		cout << endl;

		// 공유카드 셋팅
		dealer->Shard_card();
		controller->setOpenCard(dealer->getOpenCard());
		cout << endl;

		// 사용자 카드 셋팅
		for (int i = 0; i < playerNum; i++) {
			dealer->Shuffle();
			StaticUser::user[i].playerDeck(*dealer);
			controller->setUserCards(StaticUser::user[i].getUserCard(), i);
		}

		// 첫 번째 베팅
		livePtr = controller->Bet(live);

		tempPlayerNum = 0;
		for (int i = 0; i < 3; i++) {
			live[i] = livePtr[i];
			if (live[i] == 1) {
				tempPlayerNum++;
			}
		}

		if (tempPlayerNum == 1) {
			goto end;
		}

		// 세 개의 카드 오픈(오픈-1)
		controller->showOpenCard(1);
		cout << endl;

		// 두 번째 베팅
		livePtr = controller->Bet(live);

		tempPlayerNum = 0;
		for (int i = 0; i < 3; i++) {
			live[i] = livePtr[i];
			if (live[i] == 1) {
				tempPlayerNum++;
			}
		}

		if (tempPlayerNum == 1) {
			goto end;
		}

		// 한 개의 카드 오픈(네 번째) (오픈-2)
		controller->showOpenCard(2);
		cout << endl;

		// 세 번째 베팅
		livePtr = controller->Bet(live);

		tempPlayerNum = 0;
		for (int i = 0; i < 3; i++) {
			live[i] = livePtr[i];
			if (live[i] == 1) {
				tempPlayerNum++;
			}
		}

		if (tempPlayerNum == 1) {
			goto end;
		}

		// 마지막 카드 오픈 (오픈-3)
		controller->showOpenCard(3);
		cout << endl;

		// 마지막 베팅
		livePtr = controller->Bet(live);

		tempPlayerNum = 0;
		for (int i = 0; i < 3; i++) {
			live[i] = livePtr[i];
			if (live[i] == 1) {
				tempPlayerNum++;
			}
		}

		if (tempPlayerNum == 1) {
			goto end;
		}

		// 최종 카드 결정, 사용자 족보 판정
		for (int i = 0; i < 3; i++) {
			if (live[i] != 0) {
				controller->findCombination(controller->askCard(i));
			}
		}

	end:
		// 최종 우승자 판정
		if (tempPlayerNum == 1) {
			for (int i = 0; i < 3; i++) {
				if (live[i] == 1) {
					winner = StaticUser::user[i];
				}
			}
		}

		else {
			winner = StaticUser::user[controller->findWinner()];
		}

		cout << "Winner is " << winner.getPlayerID() << endl;

		// 사용자에게 베팅 금액 추가


		// 파일 출력


		// 종료
		return;
	}
};
