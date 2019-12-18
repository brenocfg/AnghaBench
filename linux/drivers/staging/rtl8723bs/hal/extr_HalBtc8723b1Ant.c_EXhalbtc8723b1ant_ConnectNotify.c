#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct TYPE_20__ {scalar_t__ nArpCnt; } ;
struct TYPE_19__ {int bWiFiIsHighPriTask; scalar_t__ bC2hBtInquiryPage; } ;
struct TYPE_17__ {scalar_t__ bBtDisabled; } ;
struct TYPE_18__ {int /*<<< orphan*/  (* fBtcGet ) (TYPE_2__*,int /*<<< orphan*/ ,int*) ;TYPE_1__ btInfo; scalar_t__ bStopCoexDm; scalar_t__ bManualControl; } ;
typedef  TYPE_2__* PBTC_COEXIST ;

/* Variables and functions */
 scalar_t__ BTC_ASSOCIATE_FINISH ; 
 scalar_t__ BTC_ASSOCIATE_START ; 
 int /*<<< orphan*/  BTC_GET_BL_HS_OPERATION ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_CONNECTED ; 
 int /*<<< orphan*/  BTC_GET_U4_WIFI_LINK_STATUS ; 
 int /*<<< orphan*/  BTC_MSG_INTERFACE ; 
 int /*<<< orphan*/  BTC_PRINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  INTF_NOTIFY ; 
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int /*<<< orphan*/  halbtc8723b1ant_ActionBtInquiry (TYPE_2__*) ; 
 int /*<<< orphan*/  halbtc8723b1ant_ActionHs (TYPE_2__*) ; 
 int /*<<< orphan*/  halbtc8723b1ant_ActionWifiConnected (TYPE_2__*) ; 
 int /*<<< orphan*/  halbtc8723b1ant_ActionWifiMultiPort (TYPE_2__*) ; 
 int /*<<< orphan*/  halbtc8723b1ant_ActionWifiNotConnected (TYPE_2__*) ; 
 int /*<<< orphan*/  halbtc8723b1ant_ActionWifiNotConnectedAssoAuth (TYPE_2__*) ; 
 int /*<<< orphan*/  halbtc8723b1ant_LimitedRx (TYPE_2__*,int /*<<< orphan*/ ,int,int,scalar_t__) ; 
 int /*<<< orphan*/  halbtc8723b1ant_LimitedTx (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__* pCoexDm ; 
 TYPE_6__* pCoexSta ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 

void EXhalbtc8723b1ant_ConnectNotify(PBTC_COEXIST pBtCoexist, u8 type)
{
	bool bWifiConnected = false, bBtHsOn = false;
	u32 wifiLinkStatus = 0;
	u32 numOfWifiLink = 0;
	bool bBtCtrlAggBufSize = false;
	u8 aggBufSize = 5;

	if (
		pBtCoexist->bManualControl ||
		pBtCoexist->bStopCoexDm ||
		pBtCoexist->btInfo.bBtDisabled
	)
		return;

	if (BTC_ASSOCIATE_START == type) {
		pCoexSta->bWiFiIsHighPriTask = true;
		BTC_PRINT(BTC_MSG_INTERFACE, INTF_NOTIFY, ("[BTCoex], CONNECT START notify\n"));
		 pCoexDm->nArpCnt = 0;
	} else {
		pCoexSta->bWiFiIsHighPriTask = false;
		BTC_PRINT(BTC_MSG_INTERFACE, INTF_NOTIFY, ("[BTCoex], CONNECT FINISH notify\n"));
		/* pCoexDm->nArpCnt = 0; */
	}

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U4_WIFI_LINK_STATUS, &wifiLinkStatus);
	numOfWifiLink = wifiLinkStatus>>16;
	if (numOfWifiLink >= 2) {
		halbtc8723b1ant_LimitedTx(pBtCoexist, NORMAL_EXEC, 0, 0, 0, 0);
		halbtc8723b1ant_LimitedRx(pBtCoexist, NORMAL_EXEC, false, bBtCtrlAggBufSize, aggBufSize);
		halbtc8723b1ant_ActionWifiMultiPort(pBtCoexist);
		return;
	}

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_HS_OPERATION, &bBtHsOn);
	if (pCoexSta->bC2hBtInquiryPage) {
		halbtc8723b1ant_ActionBtInquiry(pBtCoexist);
		return;
	} else if (bBtHsOn) {
		halbtc8723b1ant_ActionHs(pBtCoexist);
		return;
	}

	if (BTC_ASSOCIATE_START == type) {
		/* BTC_PRINT(BTC_MSG_INTERFACE, INTF_NOTIFY, ("[BTCoex], CONNECT START notify\n")); */
		halbtc8723b1ant_ActionWifiNotConnectedAssoAuth(pBtCoexist);
	} else if (BTC_ASSOCIATE_FINISH == type) {
		/* BTC_PRINT(BTC_MSG_INTERFACE, INTF_NOTIFY, ("[BTCoex], CONNECT FINISH notify\n")); */

		pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_CONNECTED, &bWifiConnected);
		if (!bWifiConnected) /*  non-connected scan */
			halbtc8723b1ant_ActionWifiNotConnected(pBtCoexist);
		else
			halbtc8723b1ant_ActionWifiConnected(pBtCoexist);
	}
}