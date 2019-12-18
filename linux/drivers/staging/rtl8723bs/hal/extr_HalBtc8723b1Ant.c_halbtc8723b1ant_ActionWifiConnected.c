#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
struct TYPE_22__ {scalar_t__ nScanAPNum; int highPriorityTx; int highPriorityRx; int /*<<< orphan*/  bHidExist; int /*<<< orphan*/  bA2dpExist; int /*<<< orphan*/  bPanExist; } ;
struct TYPE_20__ {scalar_t__ bA2dpOnly; int /*<<< orphan*/  bHidOnly; } ;
struct TYPE_21__ {TYPE_1__ btLinkInfo; int /*<<< orphan*/  (* fBtcGet ) (TYPE_2__*,int /*<<< orphan*/ ,int*) ;} ;
struct TYPE_19__ {scalar_t__ btStatus; } ;
typedef  TYPE_2__* PBTC_COEXIST ;

/* Variables and functions */
 int /*<<< orphan*/  ALGO_TRACE ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_4_WAY_PROGRESS ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_AP_MODE_ENABLE ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_BUSY ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_LINK ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_ROAM ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_SCAN ; 
 int /*<<< orphan*/  BTC_MSG_ALGORITHM ; 
 int /*<<< orphan*/  BTC_PRINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  BTC_PS_LPS_ON ; 
 int /*<<< orphan*/  BTC_PS_WIFI_NATIVE ; 
 scalar_t__ BT_8723B_1ANT_BT_STATUS_ACL_BUSY ; 
 scalar_t__ BT_8723B_1ANT_BT_STATUS_ACL_SCO_BUSY ; 
 scalar_t__ BT_8723B_1ANT_BT_STATUS_SCO_BUSY ; 
 scalar_t__ BT_8723B_1ANT_WIFI_NOISY_THRESH ; 
 int /*<<< orphan*/  BT_8723B_1ANT_WIFI_STATUS_CONNECTED_BUSY ; 
 int /*<<< orphan*/  BT_8723B_1ANT_WIFI_STATUS_CONNECTED_IDLE ; 
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int /*<<< orphan*/  halbtc8723b1ant_ActionBtScoHidOnlyBusy (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  halbtc8723b1ant_ActionWifiConnectedBtAclBusy (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  halbtc8723b1ant_ActionWifiConnectedScan (TYPE_2__*) ; 
 int /*<<< orphan*/  halbtc8723b1ant_ActionWifiConnectedSpecialPacket (TYPE_2__*) ; 
 int /*<<< orphan*/  halbtc8723b1ant_CoexTableWithType (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8723b1ant_PowerSaveState (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  halbtc8723b1ant_PsTdma (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 TYPE_10__* pCoexDm ; 
 TYPE_9__* pCoexSta ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub4 (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub5 (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub6 (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void halbtc8723b1ant_ActionWifiConnected(PBTC_COEXIST pBtCoexist)
{
	bool bWifiBusy = false;
	bool bScan = false, bLink = false, bRoam = false;
	bool bUnder4way = false, bApEnable = false;

	BTC_PRINT(
		BTC_MSG_ALGORITHM,
		ALGO_TRACE,
		("[BTCoex], CoexForWifiConnect() ===>\n")
	);

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_4_WAY_PROGRESS, &bUnder4way);
	if (bUnder4way) {
		halbtc8723b1ant_ActionWifiConnectedSpecialPacket(pBtCoexist);
		BTC_PRINT(
			BTC_MSG_ALGORITHM,
			ALGO_TRACE,
			("[BTCoex], CoexForWifiConnect(), return for wifi is under 4way<===\n")
		);
		return;
	}

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_SCAN, &bScan);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_LINK, &bLink);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_ROAM, &bRoam);
	if (bScan || bLink || bRoam) {
		if (bScan)
			halbtc8723b1ant_ActionWifiConnectedScan(pBtCoexist);
		else
			halbtc8723b1ant_ActionWifiConnectedSpecialPacket(pBtCoexist);
		BTC_PRINT(
			BTC_MSG_ALGORITHM,
			ALGO_TRACE,
			("[BTCoex], CoexForWifiConnect(), return for wifi is under scan<===\n")
		);
		return;
	}

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_AP_MODE_ENABLE, &bApEnable);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_BUSY, &bWifiBusy);

	/*  power save state */
	if (
		!bApEnable &&
		BT_8723B_1ANT_BT_STATUS_ACL_BUSY == pCoexDm->btStatus &&
		!pBtCoexist->btLinkInfo.bHidOnly
	) {
		if (pBtCoexist->btLinkInfo.bA2dpOnly) { /* A2DP */
			if (!bWifiBusy)
				halbtc8723b1ant_PowerSaveState(
					pBtCoexist, BTC_PS_WIFI_NATIVE, 0x0, 0x0
				);
			else { /* busy */
				if  (pCoexSta->nScanAPNum >= BT_8723B_1ANT_WIFI_NOISY_THRESH)  /* no force LPS, no PS-TDMA, use pure TDMA */
					halbtc8723b1ant_PowerSaveState(
						pBtCoexist, BTC_PS_WIFI_NATIVE, 0x0, 0x0
					);
				else
					halbtc8723b1ant_PowerSaveState(
						pBtCoexist, BTC_PS_LPS_ON, 0x50, 0x4
					);
			}
		} else if (
			(!pCoexSta->bPanExist) &&
			(!pCoexSta->bA2dpExist) &&
			(!pCoexSta->bHidExist)
		)
			halbtc8723b1ant_PowerSaveState(pBtCoexist, BTC_PS_WIFI_NATIVE, 0x0, 0x0);
		else
			halbtc8723b1ant_PowerSaveState(pBtCoexist, BTC_PS_LPS_ON, 0x50, 0x4);
	} else
		halbtc8723b1ant_PowerSaveState(pBtCoexist, BTC_PS_WIFI_NATIVE, 0x0, 0x0);

	/*  tdma and coex table */
	if (!bWifiBusy) {
		if (BT_8723B_1ANT_BT_STATUS_ACL_BUSY == pCoexDm->btStatus) {
			halbtc8723b1ant_ActionWifiConnectedBtAclBusy(
				pBtCoexist,
				BT_8723B_1ANT_WIFI_STATUS_CONNECTED_IDLE
			);
		} else if (
			(BT_8723B_1ANT_BT_STATUS_SCO_BUSY == pCoexDm->btStatus) ||
			(BT_8723B_1ANT_BT_STATUS_ACL_SCO_BUSY == pCoexDm->btStatus)
		) {
			halbtc8723b1ant_ActionBtScoHidOnlyBusy(pBtCoexist,
				BT_8723B_1ANT_WIFI_STATUS_CONNECTED_IDLE);
		} else {
			halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, false, 8);

			if ((pCoexSta->highPriorityTx) + (pCoexSta->highPriorityRx) <= 60)
				halbtc8723b1ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 2);
			else
				halbtc8723b1ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 7);
		}
	} else {
		if (BT_8723B_1ANT_BT_STATUS_ACL_BUSY == pCoexDm->btStatus) {
			halbtc8723b1ant_ActionWifiConnectedBtAclBusy(
				pBtCoexist,
				BT_8723B_1ANT_WIFI_STATUS_CONNECTED_BUSY
			);
		} else if (
			(BT_8723B_1ANT_BT_STATUS_SCO_BUSY == pCoexDm->btStatus) ||
			(BT_8723B_1ANT_BT_STATUS_ACL_SCO_BUSY == pCoexDm->btStatus)
		) {
			halbtc8723b1ant_ActionBtScoHidOnlyBusy(
				pBtCoexist,
				BT_8723B_1ANT_WIFI_STATUS_CONNECTED_BUSY
			);
		} else {
			halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, false, 8);

			if ((pCoexSta->highPriorityTx) + (pCoexSta->highPriorityRx) <= 60)
				halbtc8723b1ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 2);
			else
				halbtc8723b1ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 7);
		}
	}
}