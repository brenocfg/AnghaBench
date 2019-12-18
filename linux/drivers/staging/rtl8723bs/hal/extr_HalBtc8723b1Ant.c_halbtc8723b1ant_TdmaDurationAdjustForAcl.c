#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int s32 ;
struct TYPE_4__ {int curPsTdma; int psTdmaDuAdjType; int bAutoTdmaAdjust; } ;
struct TYPE_3__ {scalar_t__ btRetryCnt; scalar_t__ btInfoExt; int lowPriorityTx; int lowPriorityRx; } ;
typedef  int /*<<< orphan*/  PBTC_COEXIST ;

/* Variables and functions */
 int /*<<< orphan*/  ALGO_TRACE_FW ; 
 int /*<<< orphan*/  ALGO_TRACE_FW_DETAIL ; 
 int /*<<< orphan*/  BTC_MSG_ALGORITHM ; 
 int /*<<< orphan*/  BTC_PRINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ BT_8723B_1ANT_WIFI_STATUS_CONNECTED_SCAN ; 
 scalar_t__ BT_8723B_1ANT_WIFI_STATUS_CONNECTED_SPECIAL_PKT ; 
 scalar_t__ BT_8723B_1ANT_WIFI_STATUS_NON_CONNECTED_ASSO_AUTH_SCAN ; 
 scalar_t__ BT_INFO_8723B_1ANT_A2DP_BASIC_RATE (scalar_t__) ; 
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int /*<<< orphan*/  halbtc8723b1ant_PsTdma (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 TYPE_2__* pCoexDm ; 
 TYPE_1__* pCoexSta ; 

__attribute__((used)) static void halbtc8723b1ant_TdmaDurationAdjustForAcl(
	PBTC_COEXIST pBtCoexist, u8 wifiStatus
)
{
	static s32 up, dn, m, n, WaitCount;
	s32 result;   /* 0: no change, +1: increase WiFi duration, -1: decrease WiFi duration */
	u8 retryCount = 0, btInfoExt;

	BTC_PRINT(
		BTC_MSG_ALGORITHM,
		ALGO_TRACE_FW,
		("[BTCoex], TdmaDurationAdjustForAcl()\n")
	);

	if (
		(BT_8723B_1ANT_WIFI_STATUS_NON_CONNECTED_ASSO_AUTH_SCAN == wifiStatus) ||
		(BT_8723B_1ANT_WIFI_STATUS_CONNECTED_SCAN == wifiStatus) ||
		(BT_8723B_1ANT_WIFI_STATUS_CONNECTED_SPECIAL_PKT == wifiStatus)
	) {
		if (
			pCoexDm->curPsTdma != 1 &&
			pCoexDm->curPsTdma != 2 &&
			pCoexDm->curPsTdma != 3 &&
			pCoexDm->curPsTdma != 9
		) {
			halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, true, 9);
			pCoexDm->psTdmaDuAdjType = 9;

			up = 0;
			dn = 0;
			m = 1;
			n = 3;
			result = 0;
			WaitCount = 0;
		}
		return;
	}

	if (!pCoexDm->bAutoTdmaAdjust) {
		pCoexDm->bAutoTdmaAdjust = true;
		BTC_PRINT(
			BTC_MSG_ALGORITHM,
			ALGO_TRACE_FW_DETAIL,
			("[BTCoex], first run TdmaDurationAdjust()!!\n")
		);

		halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, true, 2);
		pCoexDm->psTdmaDuAdjType = 2;
		/*  */
		up = 0;
		dn = 0;
		m = 1;
		n = 3;
		result = 0;
		WaitCount = 0;
	} else {
		/* accquire the BT TRx retry count from BT_Info byte2 */
		retryCount = pCoexSta->btRetryCnt;
		btInfoExt = pCoexSta->btInfoExt;
		/* BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE_FW_DETAIL, ("[BTCoex], retryCount = %d\n", retryCount)); */
		/* BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE_FW_DETAIL, ("[BTCoex], up =%d, dn =%d, m =%d, n =%d, WaitCount =%d\n", */
		/* 	up, dn, m, n, WaitCount)); */

		if (pCoexSta->lowPriorityTx > 1050 || pCoexSta->lowPriorityRx > 1250)
			retryCount++;

		result = 0;
		WaitCount++;

		if (retryCount == 0) { /*  no retry in the last 2-second duration */
			up++;
			dn--;

			if (dn <= 0)
				dn = 0;

			if (up >= n) { /*  if 連續 n 個2秒 retry count為0, 則調寬WiFi duration */
				WaitCount = 0;
				n = 3;
				up = 0;
				dn = 0;
				result = 1;
				BTC_PRINT(
					BTC_MSG_ALGORITHM,
					ALGO_TRACE_FW_DETAIL,
					("[BTCoex], Increase wifi duration!!\n")
				);
			}
		} else if (retryCount <= 3) { /*  <=3 retry in the last 2-second duration */
			up--;
			dn++;

			if (up <= 0)
				up = 0;

			if (dn == 2) { /*  if 連續 2 個2秒 retry count< 3, 則調窄WiFi duration */
				if (WaitCount <= 2)
					m++; /*  避免一直在兩個level中來回 */
				else
					m = 1;

				if (m >= 20) /* m 最大值 = 20 ' 最大120秒 recheck是否調整 WiFi duration. */
					m = 20;

				n = 3*m;
				up = 0;
				dn = 0;
				WaitCount = 0;
				result = -1;
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE_FW_DETAIL, ("[BTCoex], Decrease wifi duration for retryCounter<3!!\n"));
			}
		} else { /* retry count > 3, 只要1次 retry count > 3, 則調窄WiFi duration */
			if (WaitCount == 1)
				m++; /*  避免一直在兩個level中來回 */
			else
				m = 1;

			if (m >= 20) /* m 最大值 = 20 ' 最大120秒 recheck是否調整 WiFi duration. */
				m = 20;

			n = 3*m;
			up = 0;
			dn = 0;
			WaitCount = 0;
			result = -1;
			BTC_PRINT(
				BTC_MSG_ALGORITHM,
				ALGO_TRACE_FW_DETAIL,
				("[BTCoex], Decrease wifi duration for retryCounter>3!!\n")
			);
		}

		if (result == -1) {
			if (
				BT_INFO_8723B_1ANT_A2DP_BASIC_RATE(btInfoExt) &&
				((pCoexDm->curPsTdma == 1) || (pCoexDm->curPsTdma == 2))
			) {
				halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, true, 9);
				pCoexDm->psTdmaDuAdjType = 9;
			} else if (pCoexDm->curPsTdma == 1) {
				halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, true, 2);
				pCoexDm->psTdmaDuAdjType = 2;
			} else if (pCoexDm->curPsTdma == 2) {
				halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, true, 9);
				pCoexDm->psTdmaDuAdjType = 9;
			} else if (pCoexDm->curPsTdma == 9) {
				halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, true, 11);
				pCoexDm->psTdmaDuAdjType = 11;
			}
		} else if (result == 1) {
			if (
				BT_INFO_8723B_1ANT_A2DP_BASIC_RATE(btInfoExt) &&
				((pCoexDm->curPsTdma == 1) || (pCoexDm->curPsTdma == 2))
			) {
				halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, true, 9);
				pCoexDm->psTdmaDuAdjType = 9;
			} else if (pCoexDm->curPsTdma == 11) {
				halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, true, 9);
				pCoexDm->psTdmaDuAdjType = 9;
			} else if (pCoexDm->curPsTdma == 9) {
				halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, true, 2);
				pCoexDm->psTdmaDuAdjType = 2;
			} else if (pCoexDm->curPsTdma == 2) {
				halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, true, 1);
				pCoexDm->psTdmaDuAdjType = 1;
			}
		} else {	  /* no change */
			BTC_PRINT(
				BTC_MSG_ALGORITHM,
				ALGO_TRACE_FW_DETAIL,
				(
					"[BTCoex], ********** TDMA(on, %d) **********\n",
					pCoexDm->curPsTdma
				)
			);
		}

		if (
			pCoexDm->curPsTdma != 1 &&
			pCoexDm->curPsTdma != 2 &&
			pCoexDm->curPsTdma != 9 &&
			pCoexDm->curPsTdma != 11
		) /*  recover to previous adjust type */
			halbtc8723b1ant_PsTdma(
				pBtCoexist, NORMAL_EXEC, true, pCoexDm->psTdmaDuAdjType
			);
	}
}