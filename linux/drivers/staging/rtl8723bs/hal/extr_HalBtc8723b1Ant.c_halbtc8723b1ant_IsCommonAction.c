#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ btStatus; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* fBtcGet ) (TYPE_1__*,int /*<<< orphan*/ ,int*) ;} ;
typedef  TYPE_1__* PBTC_COEXIST ;

/* Variables and functions */
 int /*<<< orphan*/  ALGO_TRACE ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_BUSY ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_CONNECTED ; 
 int /*<<< orphan*/  BTC_MSG_ALGORITHM ; 
 int /*<<< orphan*/  BTC_PRINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ BT_8723B_1ANT_BT_STATUS_CONNECTED_IDLE ; 
 scalar_t__ BT_8723B_1ANT_BT_STATUS_NON_CONNECTED_IDLE ; 
 TYPE_4__* pCoexDm ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static bool halbtc8723b1ant_IsCommonAction(PBTC_COEXIST pBtCoexist)
{
	bool bCommon = false, bWifiConnected = false, bWifiBusy = false;

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_CONNECTED, &bWifiConnected);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_BUSY, &bWifiBusy);

	if (
		!bWifiConnected &&
		BT_8723B_1ANT_BT_STATUS_NON_CONNECTED_IDLE == pCoexDm->btStatus
	) {
		BTC_PRINT(
			BTC_MSG_ALGORITHM,
			ALGO_TRACE,
			("[BTCoex], Wifi non connected-idle + BT non connected-idle!!\n")
		);

		/* halbtc8723b1ant_SwMechanism(pBtCoexist, false); */

		bCommon = true;
	} else if (
		bWifiConnected &&
		(BT_8723B_1ANT_BT_STATUS_NON_CONNECTED_IDLE == pCoexDm->btStatus)
	) {
		BTC_PRINT(
			BTC_MSG_ALGORITHM,
			ALGO_TRACE,
			("[BTCoex], Wifi connected + BT non connected-idle!!\n")
		);

		/* halbtc8723b1ant_SwMechanism(pBtCoexist, false); */

		bCommon = true;
	} else if (
		!bWifiConnected &&
		(BT_8723B_1ANT_BT_STATUS_CONNECTED_IDLE == pCoexDm->btStatus)
	) {
		BTC_PRINT(
			BTC_MSG_ALGORITHM,
			ALGO_TRACE,
			("[BTCoex], Wifi non connected-idle + BT connected-idle!!\n")
		);

		/* halbtc8723b1ant_SwMechanism(pBtCoexist, false); */

		bCommon = true;
	} else if (
		bWifiConnected &&
		(BT_8723B_1ANT_BT_STATUS_CONNECTED_IDLE == pCoexDm->btStatus)
	) {
		BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], Wifi connected + BT connected-idle!!\n"));

		/* halbtc8723b1ant_SwMechanism(pBtCoexist, false); */

		bCommon = true;
	} else if (
		!bWifiConnected &&
		(BT_8723B_1ANT_BT_STATUS_CONNECTED_IDLE != pCoexDm->btStatus)
	) {
		BTC_PRINT(
			BTC_MSG_ALGORITHM,
			ALGO_TRACE,
			("[BTCoex], Wifi non connected-idle + BT Busy!!\n")
		);

		/* halbtc8723b1ant_SwMechanism(pBtCoexist, false); */

		bCommon = true;
	} else {
		if (bWifiBusy) {
			BTC_PRINT(
				BTC_MSG_ALGORITHM,
				ALGO_TRACE,
				("[BTCoex], Wifi Connected-Busy + BT Busy!!\n")
			);
		} else {
			BTC_PRINT(
				BTC_MSG_ALGORITHM,
				ALGO_TRACE,
				("[BTCoex], Wifi Connected-Idle + BT Busy!!\n")
			);
		}

		bCommon = false;
	}

	return bCommon;
}