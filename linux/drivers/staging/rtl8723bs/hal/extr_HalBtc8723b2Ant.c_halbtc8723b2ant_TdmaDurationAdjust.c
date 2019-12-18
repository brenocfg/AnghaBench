#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int s32 ;
struct TYPE_11__ {int bAutoTdmaAdjust; int curPsTdma; int psTdmaDuAdjType; } ;
struct TYPE_10__ {int btRetryCnt; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* fBtcGet ) (TYPE_1__*,int /*<<< orphan*/ ,int*) ;} ;
typedef  TYPE_1__* PBTC_COEXIST ;

/* Variables and functions */
 int /*<<< orphan*/  ALGO_TRACE_FW ; 
 int /*<<< orphan*/  ALGO_TRACE_FW_DETAIL ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_LINK ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_ROAM ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_SCAN ; 
 int /*<<< orphan*/  BTC_MSG_ALGORITHM ; 
 int /*<<< orphan*/  BTC_PRINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  HAL_BTC8723B2ANT_DMA_DURATION_ADJUST (int) ; 
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int /*<<< orphan*/  halbtc8723b2ant_PsTdma (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 TYPE_6__* pCoexDm ; 
 TYPE_5__* pCoexSta ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void halbtc8723b2ant_TdmaDurationAdjust(
	PBTC_COEXIST pBtCoexist, bool bScoHid, bool bTxPause, u8 maxInterval
)
{
	static s32 up, dn, m, n, WaitCount;
	s32 result;   /* 0: no change, +1: increase WiFi duration, -1: decrease WiFi duration */
	u8 retryCount = 0;

	BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE_FW, ("[BTCoex], TdmaDurationAdjust()\n"));

	if (!pCoexDm->bAutoTdmaAdjust) {
		pCoexDm->bAutoTdmaAdjust = true;
		BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE_FW_DETAIL, ("[BTCoex], first run TdmaDurationAdjust()!!\n"));
		{
			if (bScoHid) {
				if (bTxPause) {
					if (maxInterval == 1)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(13);
					else if (maxInterval == 2)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(14);
					else if (maxInterval == 3)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(15);
					else
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(15);
				} else {
					if (maxInterval == 1)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(9);
					else if (maxInterval == 2)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(10);
					else if (maxInterval == 3)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(11);
					else
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(11);
				}
			} else {
				if (bTxPause) {
					if (maxInterval == 1)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(5);
					else if (maxInterval == 2)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(6);
					else if (maxInterval == 3)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(7);
					else
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(7);
				} else {
					if (maxInterval == 1)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(1);
					else if (maxInterval == 2)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(2);
					else if (maxInterval == 3)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(3);
					else
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(3);
				}
			}
		}
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
		BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE_FW_DETAIL, ("[BTCoex], retryCount = %d\n", retryCount));
		BTC_PRINT(
			BTC_MSG_ALGORITHM,
			ALGO_TRACE_FW_DETAIL,
			(
				"[BTCoex], up =%d, dn =%d, m =%d, n =%d, WaitCount =%d\n",
				up, dn, m, n, WaitCount
			)
		);
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
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE_FW_DETAIL, ("[BTCoex], Increase wifi duration!!\n"));
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
			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE_FW_DETAIL, ("[BTCoex], Decrease wifi duration for retryCounter>3!!\n"));
		}

		BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE_FW_DETAIL, ("[BTCoex], max Interval = %d\n", maxInterval));
		if (maxInterval == 1) {
			if (bTxPause) {
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE_FW_DETAIL, ("[BTCoex], TxPause = 1\n"));

				if (pCoexDm->curPsTdma == 71)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(5);
				else if (pCoexDm->curPsTdma == 1)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(5);
				else if (pCoexDm->curPsTdma == 2)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(6);
				else if (pCoexDm->curPsTdma == 3)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(7);
				else if (pCoexDm->curPsTdma == 4)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(8);

				if (pCoexDm->curPsTdma == 9)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(13);
				else if (pCoexDm->curPsTdma == 10)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(14);
				else if (pCoexDm->curPsTdma == 11)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(15);
				else if (pCoexDm->curPsTdma == 12)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(16);

				if (result == -1) {
					if (pCoexDm->curPsTdma == 5)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(6);
					else if (pCoexDm->curPsTdma == 6)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(7);
					else if (pCoexDm->curPsTdma == 7)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(8);
					else if (pCoexDm->curPsTdma == 13)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(14);
					else if (pCoexDm->curPsTdma == 14)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(15);
					else if (pCoexDm->curPsTdma == 15)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(16);
				} else if (result == 1) {
					if (pCoexDm->curPsTdma == 8)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(7);
					else if (pCoexDm->curPsTdma == 7)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(6);
					else if (pCoexDm->curPsTdma == 6)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(5);
					else if (pCoexDm->curPsTdma == 16)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(15);
					else if (pCoexDm->curPsTdma == 15)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(14);
					else if (pCoexDm->curPsTdma == 14)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(13);
				}
			} else {
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE_FW_DETAIL, ("[BTCoex], TxPause = 0\n"));
				if (pCoexDm->curPsTdma == 5)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(71);
				else if (pCoexDm->curPsTdma == 6)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(2);
				else if (pCoexDm->curPsTdma == 7)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(3);
				else if (pCoexDm->curPsTdma == 8)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(4);

				if (pCoexDm->curPsTdma == 13)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(9);
				else if (pCoexDm->curPsTdma == 14)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(10);
				else if (pCoexDm->curPsTdma == 15)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(11);
				else if (pCoexDm->curPsTdma == 16)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(12);

				if (result == -1) {
					if (pCoexDm->curPsTdma == 71)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(1);
					else if (pCoexDm->curPsTdma == 1)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(2);
					else if (pCoexDm->curPsTdma == 2)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(3);
					else if (pCoexDm->curPsTdma == 3)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(4);
					else if (pCoexDm->curPsTdma == 9)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(10);
					else if (pCoexDm->curPsTdma == 10)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(11);
					else if (pCoexDm->curPsTdma == 11)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(12);
				} else if (result == 1) {
					if (pCoexDm->curPsTdma == 4)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(3);
					else if (pCoexDm->curPsTdma == 3)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(2);
					else if (pCoexDm->curPsTdma == 2)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(1);
					else if (pCoexDm->curPsTdma == 1)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(71);
					else if (pCoexDm->curPsTdma == 12)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(11);
					else if (pCoexDm->curPsTdma == 11)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(10);
					else if (pCoexDm->curPsTdma == 10)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(9);
				}
			}
		} else if (maxInterval == 2) {
			if (bTxPause) {
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE_FW_DETAIL, ("[BTCoex], TxPause = 1\n"));
				if (pCoexDm->curPsTdma == 1)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(6);
				else if (pCoexDm->curPsTdma == 2)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(6);
				else if (pCoexDm->curPsTdma == 3)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(7);
				else if (pCoexDm->curPsTdma == 4)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(8);

				if (pCoexDm->curPsTdma == 9)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(14);
				else if (pCoexDm->curPsTdma == 10)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(14);
				else if (pCoexDm->curPsTdma == 11)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(15);
				else if (pCoexDm->curPsTdma == 12)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(16);

				if (result == -1) {
					if (pCoexDm->curPsTdma == 5)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(6);
					else if (pCoexDm->curPsTdma == 6)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(7);
					else if (pCoexDm->curPsTdma == 7)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(8);
					else if (pCoexDm->curPsTdma == 13)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(14);
					else if (pCoexDm->curPsTdma == 14)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(15);
					else if (pCoexDm->curPsTdma == 15)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(16);
				} else if (result == 1) {
					if (pCoexDm->curPsTdma == 8)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(7);
					else if (pCoexDm->curPsTdma == 7)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(6);
					else if (pCoexDm->curPsTdma == 6)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(6);
					else if (pCoexDm->curPsTdma == 16)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(15);
					else if (pCoexDm->curPsTdma == 15)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(14);
					else if (pCoexDm->curPsTdma == 14)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(14);
				}
			} else {
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE_FW_DETAIL, ("[BTCoex], TxPause = 0\n"));
				if (pCoexDm->curPsTdma == 5)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(2);
				else if (pCoexDm->curPsTdma == 6)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(2);
				else if (pCoexDm->curPsTdma == 7)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(3);
				else if (pCoexDm->curPsTdma == 8)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(4);

				if (pCoexDm->curPsTdma == 13)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(10);
				else if (pCoexDm->curPsTdma == 14)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(10);
				else if (pCoexDm->curPsTdma == 15)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(11);
				else if (pCoexDm->curPsTdma == 16)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(12);

				if (result == -1) {
					if (pCoexDm->curPsTdma == 1)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(2);
					else if (pCoexDm->curPsTdma == 2)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(3);
					else if (pCoexDm->curPsTdma == 3)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(4);
					else if (pCoexDm->curPsTdma == 9)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(10);
					else if (pCoexDm->curPsTdma == 10)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(11);
					else if (pCoexDm->curPsTdma == 11)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(12);
				} else if (result == 1) {
					if (pCoexDm->curPsTdma == 4)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(3);
					else if (pCoexDm->curPsTdma == 3)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(2);
					else if (pCoexDm->curPsTdma == 2)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(2);
					else if (pCoexDm->curPsTdma == 12)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(11);
					else if (pCoexDm->curPsTdma == 11)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(10);
					else if (pCoexDm->curPsTdma == 10)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(10);
				}
			}
		} else if (maxInterval == 3) {
			if (bTxPause) {
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE_FW_DETAIL, ("[BTCoex], TxPause = 1\n"));
				if (pCoexDm->curPsTdma == 1)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(7);
				else if (pCoexDm->curPsTdma == 2)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(7);
				else if (pCoexDm->curPsTdma == 3)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(7);
				else if (pCoexDm->curPsTdma == 4)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(8);

				if (pCoexDm->curPsTdma == 9)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(15);
				else if (pCoexDm->curPsTdma == 10)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(15);
				else if (pCoexDm->curPsTdma == 11)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(15);
				else if (pCoexDm->curPsTdma == 12)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(16);

				if (result == -1) {
					if (pCoexDm->curPsTdma == 5)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(7);
					else if (pCoexDm->curPsTdma == 6)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(7);
					else if (pCoexDm->curPsTdma == 7)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(8);
					else if (pCoexDm->curPsTdma == 13)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(15);
					else if (pCoexDm->curPsTdma == 14)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(15);
					else if (pCoexDm->curPsTdma == 15)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(16);
				} else if (result == 1) {
					if (pCoexDm->curPsTdma == 8)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(7);
					else if (pCoexDm->curPsTdma == 7)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(7);
					else if (pCoexDm->curPsTdma == 6)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(7);
					else if (pCoexDm->curPsTdma == 16)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(15);
					else if (pCoexDm->curPsTdma == 15)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(15);
					else if (pCoexDm->curPsTdma == 14)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(15);
				}
			} else {
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE_FW_DETAIL, ("[BTCoex], TxPause = 0\n"));
				if (pCoexDm->curPsTdma == 5)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(3);
				else if (pCoexDm->curPsTdma == 6)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(3);
				else if (pCoexDm->curPsTdma == 7)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(3);
				else if (pCoexDm->curPsTdma == 8)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(4);

				if (pCoexDm->curPsTdma == 13)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(11);
				else if (pCoexDm->curPsTdma == 14)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(11);
				else if (pCoexDm->curPsTdma == 15)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(11);
				else if (pCoexDm->curPsTdma == 16)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(12);

				if (result == -1) {
					if (pCoexDm->curPsTdma == 1)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(3);
					else if (pCoexDm->curPsTdma == 2)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(3);
					else if (pCoexDm->curPsTdma == 3)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(4);
					else if (pCoexDm->curPsTdma == 9)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(11);
					else if (pCoexDm->curPsTdma == 10)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(11);
					else if (pCoexDm->curPsTdma == 11)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(12);
				} else if (result == 1) {
					if (pCoexDm->curPsTdma == 4)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(3);
					else if (pCoexDm->curPsTdma == 3)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(3);
					else if (pCoexDm->curPsTdma == 2)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(3);
					else if (pCoexDm->curPsTdma == 12)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(11);
					else if (pCoexDm->curPsTdma == 11)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(11);
					else if (pCoexDm->curPsTdma == 10)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(11);
				}
			}
		}
	}

	/*  if current PsTdma not match with the recorded one (when scan, dhcp...), */
	/*  then we have to adjust it back to the previous record one. */
	if (pCoexDm->curPsTdma != pCoexDm->psTdmaDuAdjType) {
		bool bScan = false, bLink = false, bRoam = false;
		BTC_PRINT(
			BTC_MSG_ALGORITHM,
			ALGO_TRACE_FW_DETAIL,
			(
				"[BTCoex], PsTdma type mismatch!!!, curPsTdma =%d, recordPsTdma =%d\n",
				pCoexDm->curPsTdma,
				pCoexDm->psTdmaDuAdjType
			)
		);

		pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_SCAN, &bScan);
		pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_LINK, &bLink);
		pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_ROAM, &bRoam);

		if (!bScan && !bLink && !bRoam)
			halbtc8723b2ant_PsTdma(pBtCoexist, NORMAL_EXEC, true, pCoexDm->psTdmaDuAdjType);
		else {
			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE_FW_DETAIL, ("[BTCoex], roaming/link/scan is under progress, will adjust next time!!!\n"));
		}
	}
}