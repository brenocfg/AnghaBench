#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_13__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_23__ {int /*<<< orphan*/  (* fBtcSetRfReg ) (TYPE_1__*,int /*<<< orphan*/ ,int,int,int) ;int /*<<< orphan*/  (* fBtcSet ) (TYPE_1__*,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  (* fBtcGet ) (TYPE_1__*,int /*<<< orphan*/ ,int*) ;} ;
struct TYPE_22__ {scalar_t__ btStatus; } ;
typedef  TYPE_1__* PBTC_COEXIST ;

/* Variables and functions */
 int /*<<< orphan*/  ALGO_TRACE ; 
 int /*<<< orphan*/  BTC_GET_BL_HS_OPERATION ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_BUSY ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_CONNECTED ; 
 int /*<<< orphan*/  BTC_MSG_ALGORITHM ; 
 int /*<<< orphan*/  BTC_PRINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  BTC_RF_A ; 
 scalar_t__ BTC_RSSI_HIGH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTC_RSSI_STATE_HIGH ; 
 int /*<<< orphan*/  BTC_SET_ACT_DISABLE_LOW_POWER ; 
 scalar_t__ BT_8723B_2ANT_BT_STATUS_CONNECTED_IDLE ; 
 scalar_t__ BT_8723B_2ANT_BT_STATUS_NON_CONNECTED_IDLE ; 
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int /*<<< orphan*/  halbtc8723b2ant_BtRssiState (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  halbtc8723b2ant_CoexTableWithType (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8723b2ant_DecBtPwr (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8723b2ant_FwDacSwingLvl (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8723b2ant_LimitedRx (TYPE_1__*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  halbtc8723b2ant_PsTdma (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  halbtc8723b2ant_SwMechanism1 (TYPE_1__*,int,int,int,int) ; 
 int /*<<< orphan*/  halbtc8723b2ant_SwMechanism2 (TYPE_1__*,int,int,int,int) ; 
 TYPE_13__* pCoexDm ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub10 (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub11 (TYPE_1__*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub4 (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub5 (TYPE_1__*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  stub6 (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub7 (TYPE_1__*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  stub8 (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub9 (TYPE_1__*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static bool halbtc8723b2ant_IsCommonAction(PBTC_COEXIST pBtCoexist)
{
	u8 btRssiState = BTC_RSSI_STATE_HIGH;
	bool bCommon = false, bWifiConnected = false, bWifiBusy = false;
	bool bBtHsOn = false, bLowPwrDisable = false;

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_HS_OPERATION, &bBtHsOn);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_CONNECTED, &bWifiConnected);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_BUSY, &bWifiBusy);

	if (!bWifiConnected) {
		bLowPwrDisable = false;
		pBtCoexist->fBtcSet(pBtCoexist, BTC_SET_ACT_DISABLE_LOW_POWER, &bLowPwrDisable);
		halbtc8723b2ant_LimitedRx(pBtCoexist, NORMAL_EXEC, false, false, 0x8);

		BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], Wifi non-connected idle!!\n"));

		pBtCoexist->fBtcSetRfReg(pBtCoexist, BTC_RF_A, 0x1, 0xfffff, 0x0);
		halbtc8723b2ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 0);
		halbtc8723b2ant_PsTdma(pBtCoexist, NORMAL_EXEC, false, 1);
		halbtc8723b2ant_FwDacSwingLvl(pBtCoexist, NORMAL_EXEC, 6);
		halbtc8723b2ant_DecBtPwr(pBtCoexist, NORMAL_EXEC, 0);

		halbtc8723b2ant_SwMechanism1(pBtCoexist, false, false, false, false);
		halbtc8723b2ant_SwMechanism2(pBtCoexist, false, false, false, 0x18);

		bCommon = true;
	} else {
		if (BT_8723B_2ANT_BT_STATUS_NON_CONNECTED_IDLE == pCoexDm->btStatus) {
			bLowPwrDisable = false;
			pBtCoexist->fBtcSet(pBtCoexist, BTC_SET_ACT_DISABLE_LOW_POWER, &bLowPwrDisable);
			halbtc8723b2ant_LimitedRx(pBtCoexist, NORMAL_EXEC, false, false, 0x8);

			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], Wifi connected + BT non connected-idle!!\n"));

			pBtCoexist->fBtcSetRfReg(pBtCoexist, BTC_RF_A, 0x1, 0xfffff, 0x0);
			halbtc8723b2ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 0);
			halbtc8723b2ant_PsTdma(pBtCoexist, NORMAL_EXEC, false, 1);
			halbtc8723b2ant_FwDacSwingLvl(pBtCoexist, NORMAL_EXEC, 0xb);
			halbtc8723b2ant_DecBtPwr(pBtCoexist, NORMAL_EXEC, 0);

			halbtc8723b2ant_SwMechanism1(pBtCoexist, false, false, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, false, false, false, 0x18);

			bCommon = true;
		} else if (BT_8723B_2ANT_BT_STATUS_CONNECTED_IDLE == pCoexDm->btStatus) {
			bLowPwrDisable = true;
			pBtCoexist->fBtcSet(pBtCoexist, BTC_SET_ACT_DISABLE_LOW_POWER, &bLowPwrDisable);

			if (bBtHsOn)
				return false;

			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], Wifi connected + BT connected-idle!!\n"));
			halbtc8723b2ant_LimitedRx(pBtCoexist, NORMAL_EXEC, false, false, 0x8);

			pBtCoexist->fBtcSetRfReg(pBtCoexist, BTC_RF_A, 0x1, 0xfffff, 0x0);
			halbtc8723b2ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 0);
			halbtc8723b2ant_PsTdma(pBtCoexist, NORMAL_EXEC, false, 1);
			halbtc8723b2ant_FwDacSwingLvl(pBtCoexist, NORMAL_EXEC, 0xb);
			halbtc8723b2ant_DecBtPwr(pBtCoexist, NORMAL_EXEC, 0);

			halbtc8723b2ant_SwMechanism1(pBtCoexist, true, false, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, false, false, false, 0x18);

			bCommon = true;
		} else {
			bLowPwrDisable = true;
			pBtCoexist->fBtcSet(pBtCoexist, BTC_SET_ACT_DISABLE_LOW_POWER, &bLowPwrDisable);

			if (bWifiBusy) {
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], Wifi Connected-Busy + BT Busy!!\n"));
				bCommon = false;
			} else {
				if (bBtHsOn)
					return false;

				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], Wifi Connected-Idle + BT Busy!!\n"));
				btRssiState = halbtc8723b2ant_BtRssiState(2, 29, 0);
				halbtc8723b2ant_LimitedRx(pBtCoexist, NORMAL_EXEC, false, false, 0x8);

				pBtCoexist->fBtcSetRfReg(pBtCoexist, BTC_RF_A, 0x1, 0xfffff, 0x0);
				halbtc8723b2ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 7);
				halbtc8723b2ant_PsTdma(pBtCoexist, NORMAL_EXEC, true, 21);
				halbtc8723b2ant_FwDacSwingLvl(pBtCoexist, NORMAL_EXEC, 0xb);

				if (BTC_RSSI_HIGH(btRssiState))
					halbtc8723b2ant_DecBtPwr(pBtCoexist, NORMAL_EXEC, 2);
				else
					halbtc8723b2ant_DecBtPwr(pBtCoexist, NORMAL_EXEC, 0);

				halbtc8723b2ant_SwMechanism1(pBtCoexist, false, false, false, false);
				halbtc8723b2ant_SwMechanism2(pBtCoexist, false, false, false, 0x18);
				bCommon = true;
			}
		}
	}

	return bCommon;
}