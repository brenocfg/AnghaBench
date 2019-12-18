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
typedef  int u8 ;
struct rtl_priv {int dummy; } ;
struct btc_coexist {int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;struct rtl_priv* adapter; } ;
struct TYPE_4__ {int auto_tdma_adjust; int tdma_adj_type; int cur_ps_tdma; } ;
struct TYPE_3__ {int bt_retry_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_GET_BL_WIFI_LINK ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_ROAM ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_SCAN ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  btc8192e2ant_ps_tdma (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 
 TYPE_2__* coex_dm ; 
 TYPE_1__* coex_sta ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void btc8192e2ant_tdma_duration_adjust(struct btc_coexist *btcoexist,
					      bool sco_hid, bool tx_pause,
					      u8 max_interval)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	static int up, dn, m, n, wait_cnt;
	/* 0: no change, +1: increase WiFi duration,
	 * -1: decrease WiFi duration
	 */
	int result;
	u8 retry_cnt = 0;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], TdmaDurationAdjust()\n");

	if (!coex_dm->auto_tdma_adjust) {
		coex_dm->auto_tdma_adjust = true;
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], first run TdmaDurationAdjust()!!\n");
		if (sco_hid) {
			if (tx_pause) {
				if (max_interval == 1) {
					btc8192e2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 13);
					coex_dm->tdma_adj_type = 13;
				} else if (max_interval == 2) {
					btc8192e2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 14);
					coex_dm->tdma_adj_type = 14;
				} else {
					btc8192e2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 15);
					coex_dm->tdma_adj_type = 15;
				}
			} else {
				if (max_interval == 1) {
					btc8192e2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 9);
					coex_dm->tdma_adj_type = 9;
				} else if (max_interval == 2) {
					btc8192e2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 10);
					coex_dm->tdma_adj_type = 10;
				} else {
					btc8192e2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 11);
					coex_dm->tdma_adj_type = 11;
				}
			}
		} else {
			if (tx_pause) {
				if (max_interval == 1) {
					btc8192e2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 5);
					coex_dm->tdma_adj_type = 5;
				} else if (max_interval == 2) {
					btc8192e2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 6);
					coex_dm->tdma_adj_type = 6;
				} else {
					btc8192e2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 7);
					coex_dm->tdma_adj_type = 7;
				}
			} else {
				if (max_interval == 1) {
					btc8192e2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 1);
					coex_dm->tdma_adj_type = 1;
				} else if (max_interval == 2) {
					btc8192e2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 2);
					coex_dm->tdma_adj_type = 2;
				} else {
					btc8192e2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 3);
					coex_dm->tdma_adj_type = 3;
				}
			}
		}

		up = 0;
		dn = 0;
		m = 1;
		n = 3;
		result = 0;
		wait_cnt = 0;
	} else {
		/* accquire the BT TRx retry count from BT_Info byte2 */
		retry_cnt = coex_sta->bt_retry_cnt;
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], retry_cnt = %d\n", retry_cnt);
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], up=%d, dn=%d, m=%d, n=%d, wait_cnt=%d\n",
			 up, dn, m, n, wait_cnt);
		result = 0;
		wait_cnt++;
		/* no retry in the last 2-second duration */
		if (retry_cnt == 0) {
			up++;
			dn--;

			if (dn <= 0)
				dn = 0;

			if (up >= n) {
				wait_cnt = 0;
				n = 3;
				up = 0;
				dn = 0;
				result = 1;
				RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					 "[BTCoex]Increase wifi duration!!\n");
			}
		} else if (retry_cnt <= 3) {
			up--;
			dn++;

			if (up <= 0)
				up = 0;

			if (dn == 2) {
				if (wait_cnt <= 2)
					m++;
				else
					m = 1;

				if (m >= 20)
					m = 20;

				n = 3 * m;
				up = 0;
				dn = 0;
				wait_cnt = 0;
				result = -1;
				RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					 "Reduce wifi duration for retry<3\n");
			}
		} else {
			if (wait_cnt == 1)
				m++;
			else
				m = 1;

			if (m >= 20)
				m = 20;

			n = 3*m;
			up = 0;
			dn = 0;
			wait_cnt = 0;
			result = -1;
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "Decrease wifi duration for retryCounter>3!!\n");
		}

		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], max Interval = %d\n", max_interval);
	}

	/* if current PsTdma not match with
	 * the recorded one (when scan, dhcp...),
	 * then we have to adjust it back to the previous record one.
	 */
	if (coex_dm->cur_ps_tdma != coex_dm->tdma_adj_type) {
		bool scan = false, link = false, roam = false;

		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], PsTdma type mismatch!!!, ");
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "curPsTdma=%d, recordPsTdma=%d\n",
			 coex_dm->cur_ps_tdma, coex_dm->tdma_adj_type);

		btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_SCAN, &scan);
		btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_LINK, &link);
		btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_ROAM, &roam);

		if (!scan && !link && !roam)
			btc8192e2ant_ps_tdma(btcoexist, NORMAL_EXEC,
					     true, coex_dm->tdma_adj_type);
		else
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], roaming/link/scan is under progress, will adjust next time!!!\n");
	}
}