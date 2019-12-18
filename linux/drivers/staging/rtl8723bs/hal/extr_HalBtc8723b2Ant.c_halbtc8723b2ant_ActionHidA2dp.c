#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_14__ {int /*<<< orphan*/  (* fBtcGet ) (TYPE_1__*,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  (* fBtcSetRfReg ) (TYPE_1__*,int /*<<< orphan*/ ,int,int,int) ;} ;
typedef  TYPE_1__* PBTC_COEXIST ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_GET_U1_AP_NUM ; 
 int /*<<< orphan*/  BTC_GET_U4_WIFI_BW ; 
 int /*<<< orphan*/  BTC_RF_A ; 
 scalar_t__ BTC_RSSI_HIGH (int) ; 
 scalar_t__ BTC_RSSI_MEDIUM (int) ; 
 int BTC_RSSI_STATE_HIGH ; 
 int BTC_RSSI_STATE_STAY_HIGH ; 
 scalar_t__ BTC_WIFI_BW_HT40 ; 
 scalar_t__ BTC_WIFI_BW_LEGACY ; 
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int halbtc8723b2ant_BtRssiState (int,int,int) ; 
 int /*<<< orphan*/  halbtc8723b2ant_CoexTableWithType (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8723b2ant_DecBtPwr (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8723b2ant_FwDacSwingLvl (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8723b2ant_LimitedRx (TYPE_1__*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  halbtc8723b2ant_SwMechanism1 (TYPE_1__*,int,int,int,int) ; 
 int /*<<< orphan*/  halbtc8723b2ant_SwMechanism2 (TYPE_1__*,int,int,int,int) ; 
 int /*<<< orphan*/  halbtc8723b2ant_TdmaDurationAdjust (TYPE_1__*,int,int,int) ; 
 int halbtc8723b2ant_WifiRssiState (TYPE_1__*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void halbtc8723b2ant_ActionHidA2dp(PBTC_COEXIST pBtCoexist)
{
	u8 wifiRssiState, btRssiState;
	u32 wifiBw;
	u8 apNum = 0;

	wifiRssiState = halbtc8723b2ant_WifiRssiState(pBtCoexist, 0, 2, 15, 0);
	/* btRssiState = halbtc8723b2ant_BtRssiState(2, 29, 0); */
	btRssiState = halbtc8723b2ant_BtRssiState(3, 29, 37);

	pBtCoexist->fBtcSetRfReg(pBtCoexist, BTC_RF_A, 0x1, 0xfffff, 0x0);

	halbtc8723b2ant_LimitedRx(pBtCoexist, NORMAL_EXEC, false, true, 0x5);

	halbtc8723b2ant_FwDacSwingLvl(pBtCoexist, NORMAL_EXEC, 6);

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U4_WIFI_BW, &wifiBw);
	if (BTC_WIFI_BW_LEGACY == wifiBw) {
		if (BTC_RSSI_HIGH(btRssiState))
			halbtc8723b2ant_DecBtPwr(pBtCoexist, NORMAL_EXEC, 2);
		else if (BTC_RSSI_MEDIUM(btRssiState))
			halbtc8723b2ant_DecBtPwr(pBtCoexist, NORMAL_EXEC, 2);
		else
			halbtc8723b2ant_DecBtPwr(pBtCoexist, NORMAL_EXEC, 0);
	} else {
		/*  only 802.11N mode we have to dec bt power to 4 degree */
		if (BTC_RSSI_HIGH(btRssiState)) {
			pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U1_AP_NUM, &apNum);
			/*  need to check ap Number of Not */
			if (apNum < 10)
				halbtc8723b2ant_DecBtPwr(pBtCoexist, NORMAL_EXEC, 4);
			else
				halbtc8723b2ant_DecBtPwr(pBtCoexist, NORMAL_EXEC, 2);
		} else if (BTC_RSSI_MEDIUM(btRssiState))
			halbtc8723b2ant_DecBtPwr(pBtCoexist, NORMAL_EXEC, 2);
		else
			halbtc8723b2ant_DecBtPwr(pBtCoexist, NORMAL_EXEC, 0);
	}

	halbtc8723b2ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 7);

	if (
		(btRssiState == BTC_RSSI_STATE_HIGH) ||
		(btRssiState == BTC_RSSI_STATE_STAY_HIGH)
	)
		halbtc8723b2ant_TdmaDurationAdjust(pBtCoexist, true, false, 2);
	else
		halbtc8723b2ant_TdmaDurationAdjust(pBtCoexist, true, true, 2);

	/*  sw mechanism */
	if (BTC_WIFI_BW_HT40 == wifiBw) {
		if (
			(wifiRssiState == BTC_RSSI_STATE_HIGH) ||
			(wifiRssiState == BTC_RSSI_STATE_STAY_HIGH)
		) {
			halbtc8723b2ant_SwMechanism1(pBtCoexist, true, true, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, true, false, false, 0x18);
		} else {
			halbtc8723b2ant_SwMechanism1(pBtCoexist, true, true, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, false, false, false, 0x18);
		}
	} else {
		if (
			(wifiRssiState == BTC_RSSI_STATE_HIGH) ||
			(wifiRssiState == BTC_RSSI_STATE_STAY_HIGH)
		) {
			halbtc8723b2ant_SwMechanism1(pBtCoexist, false, true, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, true, false, false, 0x18);
		} else {
			halbtc8723b2ant_SwMechanism1(pBtCoexist, false, true, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, false, false, false, 0x18);
		}
	}
}