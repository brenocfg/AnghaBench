#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  size_t s32 ;
struct TYPE_6__ {size_t* preWifiRssiState; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* fBtcGet ) (TYPE_1__*,int /*<<< orphan*/ ,size_t*) ;} ;
typedef  TYPE_1__* PBTC_COEXIST ;

/* Variables and functions */
 int /*<<< orphan*/  ALGO_WIFI_RSSI_STATE ; 
 int /*<<< orphan*/  BTC_GET_S4_WIFI_RSSI ; 
 int /*<<< orphan*/  BTC_MSG_ALGORITHM ; 
 int /*<<< orphan*/  BTC_PRINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 size_t BTC_RSSI_COEX_THRESH_TOL_8723B_2ANT ; 
 size_t BTC_RSSI_STATE_HIGH ; 
 scalar_t__ BTC_RSSI_STATE_LOW ; 
 scalar_t__ BTC_RSSI_STATE_MEDIUM ; 
 size_t BTC_RSSI_STATE_STAY_HIGH ; 
 scalar_t__ BTC_RSSI_STATE_STAY_LOW ; 
 scalar_t__ BTC_RSSI_STATE_STAY_MEDIUM ; 
 TYPE_3__* pCoexSta ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static u8 halbtc8723b2ant_WifiRssiState(
	PBTC_COEXIST pBtCoexist,
	u8 index,
	u8 levelNum,
	u8 rssiThresh,
	u8 rssiThresh1
)
{
	s32 wifiRssi = 0;
	u8 wifiRssiState = pCoexSta->preWifiRssiState[index];

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_S4_WIFI_RSSI, &wifiRssi);

	if (levelNum == 2) {
		if (
			(pCoexSta->preWifiRssiState[index] == BTC_RSSI_STATE_LOW) ||
			(pCoexSta->preWifiRssiState[index] == BTC_RSSI_STATE_STAY_LOW)
		) {
			if (wifiRssi >= (rssiThresh+BTC_RSSI_COEX_THRESH_TOL_8723B_2ANT)) {
				wifiRssiState = BTC_RSSI_STATE_HIGH;
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_WIFI_RSSI_STATE, ("[BTCoex], wifi RSSI state switch to High\n"));
			} else {
				wifiRssiState = BTC_RSSI_STATE_STAY_LOW;
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_WIFI_RSSI_STATE, ("[BTCoex], wifi RSSI state stay at Low\n"));
			}
		} else {
			if (wifiRssi < rssiThresh) {
				wifiRssiState = BTC_RSSI_STATE_LOW;
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_WIFI_RSSI_STATE, ("[BTCoex], wifi RSSI state switch to Low\n"));
			} else {
				wifiRssiState = BTC_RSSI_STATE_STAY_HIGH;
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_WIFI_RSSI_STATE, ("[BTCoex], wifi RSSI state stay at High\n"));
			}
		}
	} else if (levelNum == 3) {
		if (rssiThresh > rssiThresh1) {
			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_WIFI_RSSI_STATE, ("[BTCoex], wifi RSSI thresh error!!\n"));
			return pCoexSta->preWifiRssiState[index];
		}

		if (
			(pCoexSta->preWifiRssiState[index] == BTC_RSSI_STATE_LOW) ||
			(pCoexSta->preWifiRssiState[index] == BTC_RSSI_STATE_STAY_LOW)
		) {
			if (wifiRssi >= (rssiThresh+BTC_RSSI_COEX_THRESH_TOL_8723B_2ANT)) {
				wifiRssiState = BTC_RSSI_STATE_MEDIUM;
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_WIFI_RSSI_STATE, ("[BTCoex], wifi RSSI state switch to Medium\n"));
			} else {
				wifiRssiState = BTC_RSSI_STATE_STAY_LOW;
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_WIFI_RSSI_STATE, ("[BTCoex], wifi RSSI state stay at Low\n"));
			}
		} else if (
			(pCoexSta->preWifiRssiState[index] == BTC_RSSI_STATE_MEDIUM) ||
			(pCoexSta->preWifiRssiState[index] == BTC_RSSI_STATE_STAY_MEDIUM)
		) {
			if (wifiRssi >= (rssiThresh1+BTC_RSSI_COEX_THRESH_TOL_8723B_2ANT)) {
				wifiRssiState = BTC_RSSI_STATE_HIGH;
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_WIFI_RSSI_STATE, ("[BTCoex], wifi RSSI state switch to High\n"));
			} else if (wifiRssi < rssiThresh) {
				wifiRssiState = BTC_RSSI_STATE_LOW;
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_WIFI_RSSI_STATE, ("[BTCoex], wifi RSSI state switch to Low\n"));
			} else {
				wifiRssiState = BTC_RSSI_STATE_STAY_MEDIUM;
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_WIFI_RSSI_STATE, ("[BTCoex], wifi RSSI state stay at Medium\n"));
			}
		} else {
			if (wifiRssi < rssiThresh1) {
				wifiRssiState = BTC_RSSI_STATE_MEDIUM;
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_WIFI_RSSI_STATE, ("[BTCoex], wifi RSSI state switch to Medium\n"));
			} else {
				wifiRssiState = BTC_RSSI_STATE_STAY_HIGH;
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_WIFI_RSSI_STATE, ("[BTCoex], wifi RSSI state stay at High\n"));
			}
		}
	}

	pCoexSta->preWifiRssiState[index] = wifiRssiState;

	return wifiRssiState;
}