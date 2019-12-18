#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_13__ {int /*<<< orphan*/  (* fBtcGet ) (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__*) ;int /*<<< orphan*/  (* fBtcSetRfReg ) (TYPE_1__*,int /*<<< orphan*/ ,int,int,int) ;} ;
typedef  TYPE_1__* PBTC_COEXIST ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_GET_U4_WIFI_BW ; 
 int /*<<< orphan*/  BTC_RF_A ; 
 scalar_t__ BTC_RSSI_HIGH (scalar_t__) ; 
 scalar_t__ BTC_RSSI_STATE_HIGH ; 
 scalar_t__ BTC_RSSI_STATE_STAY_HIGH ; 
 scalar_t__ BTC_WIFI_BW_HT40 ; 
 scalar_t__ BTC_WIFI_BW_LEGACY ; 
 int /*<<< orphan*/  NORMAL_EXEC ; 
 scalar_t__ halbtc8723b2ant_BtRssiState (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  halbtc8723b2ant_CoexTableWithType (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8723b2ant_DecBtPwr (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8723b2ant_FwDacSwingLvl (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8723b2ant_LimitedRx (TYPE_1__*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  halbtc8723b2ant_PsTdma (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  halbtc8723b2ant_SwMechanism1 (TYPE_1__*,int,int,int,int) ; 
 int /*<<< orphan*/  halbtc8723b2ant_SwMechanism2 (TYPE_1__*,int,int,int,int) ; 
 scalar_t__ halbtc8723b2ant_WifiRssiState (TYPE_1__*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static void halbtc8723b2ant_ActionSco(PBTC_COEXIST pBtCoexist)
{
	u8 wifiRssiState, btRssiState;
	u32 wifiBw;

	wifiRssiState = halbtc8723b2ant_WifiRssiState(pBtCoexist, 0, 2, 15, 0);
	btRssiState = halbtc8723b2ant_BtRssiState(2, 29, 0);

	pBtCoexist->fBtcSetRfReg(pBtCoexist, BTC_RF_A, 0x1, 0xfffff, 0x0);

	halbtc8723b2ant_LimitedRx(pBtCoexist, NORMAL_EXEC, false, false, 0x8);

	halbtc8723b2ant_FwDacSwingLvl(pBtCoexist, NORMAL_EXEC, 4);

	if (BTC_RSSI_HIGH(btRssiState))
		halbtc8723b2ant_DecBtPwr(pBtCoexist, NORMAL_EXEC, 2);
	else
		halbtc8723b2ant_DecBtPwr(pBtCoexist, NORMAL_EXEC, 0);

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U4_WIFI_BW, &wifiBw);

	if (BTC_WIFI_BW_LEGACY == wifiBw) /* for SCO quality at 11b/g mode */
		halbtc8723b2ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 2);
	else  /* for SCO quality & wifi performance balance at 11n mode */
		halbtc8723b2ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 8);

	halbtc8723b2ant_PsTdma(pBtCoexist, NORMAL_EXEC, false, 0); /* for voice quality */

	/*  sw mechanism */
	if (BTC_WIFI_BW_HT40 == wifiBw) {
		if (
			(wifiRssiState == BTC_RSSI_STATE_HIGH) ||
			(wifiRssiState == BTC_RSSI_STATE_STAY_HIGH)
		) {
			halbtc8723b2ant_SwMechanism1(pBtCoexist, true, true, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, true, false, true, 0x4);
		} else {
			halbtc8723b2ant_SwMechanism1(pBtCoexist, true, true, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, false, false, true, 0x4);
		}
	} else {
		if (
			(wifiRssiState == BTC_RSSI_STATE_HIGH) ||
			(wifiRssiState == BTC_RSSI_STATE_STAY_HIGH)
		) {
			halbtc8723b2ant_SwMechanism1(pBtCoexist, false, true, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, true, false, true, 0x4);
		} else {
			halbtc8723b2ant_SwMechanism1(pBtCoexist, false, true, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, false, false, true, 0x4);
		}
	}
}