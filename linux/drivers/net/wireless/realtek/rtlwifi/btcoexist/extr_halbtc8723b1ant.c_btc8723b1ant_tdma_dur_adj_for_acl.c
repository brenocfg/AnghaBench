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
struct rtl_priv {int dummy; } ;
struct btc_coexist {struct rtl_priv* adapter; } ;
typedef  int s32 ;
struct TYPE_4__ {int cur_ps_tdma; int ps_tdma_du_adj_type; int auto_tdma_adjust; } ;
struct TYPE_3__ {scalar_t__ bt_retry_cnt; scalar_t__ bt_info_ext; int low_priority_tx; int low_priority_rx; } ;

/* Variables and functions */
 scalar_t__ BT_8723B_1ANT_WIFI_STATUS_CONNECTED_BUSY ; 
 scalar_t__ BT_8723B_1ANT_WIFI_STATUS_CONNECTED_SCAN ; 
 scalar_t__ BT_8723B_1ANT_WIFI_STATUS_CONNECTED_SPECIAL_PKT ; 
 scalar_t__ BT_8723B_1ANT_WIFI_STATUS_NON_CONNECTED_ASSO_AUTH_SCAN ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* coex_dm ; 
 TYPE_1__* coex_sta ; 
 int /*<<< orphan*/  halbtc8723b1ant_ps_tdma (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static
void btc8723b1ant_tdma_dur_adj_for_acl(struct btc_coexist *btcoexist,
				       u8 wifi_status)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	static s32 up, dn, m, n, wait_count;
	/*  0: no change, +1: increase WiFi duration,
	 * -1: decrease WiFi duration
	 */
	s32 result;
	u8 retry_count = 0, bt_info_ext;
	bool wifi_busy = false;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], TdmaDurationAdjustForAcl()\n");

	if (wifi_status == BT_8723B_1ANT_WIFI_STATUS_CONNECTED_BUSY)
		wifi_busy = true;
	else
		wifi_busy = false;

	if ((wifi_status ==
	     BT_8723B_1ANT_WIFI_STATUS_NON_CONNECTED_ASSO_AUTH_SCAN) ||
	    (wifi_status == BT_8723B_1ANT_WIFI_STATUS_CONNECTED_SCAN) ||
	    (wifi_status == BT_8723B_1ANT_WIFI_STATUS_CONNECTED_SPECIAL_PKT)) {
		if (coex_dm->cur_ps_tdma != 1 && coex_dm->cur_ps_tdma != 2 &&
		    coex_dm->cur_ps_tdma != 3 && coex_dm->cur_ps_tdma != 9) {
			halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC,
						true, 9);
			coex_dm->ps_tdma_du_adj_type = 9;

			up = 0;
			dn = 0;
			m = 1;
			n = 3;
			result = 0;
			wait_count = 0;
		}
		return;
	}

	if (!coex_dm->auto_tdma_adjust) {
		coex_dm->auto_tdma_adjust = true;
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], first run TdmaDurationAdjust()!!\n");

		halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 2);
		coex_dm->ps_tdma_du_adj_type = 2;

		up = 0;
		dn = 0;
		m = 1;
		n = 3;
		result = 0;
		wait_count = 0;
	} else {
		/* acquire the BT TRx retry count from BT_Info byte2 */
		retry_count = coex_sta->bt_retry_cnt;
		bt_info_ext = coex_sta->bt_info_ext;

		if ((coex_sta->low_priority_tx) > 1050 ||
		    (coex_sta->low_priority_rx) > 1250)
			retry_count++;

		result = 0;
		wait_count++;
		/* no retry in the last 2-second duration */
		if (retry_count == 0) {
			up++;
			dn--;

			if (dn <= 0)
				dn = 0;

			if (up >= n) {
				/* if retry count during continuous n*2 seconds
				 * is 0, enlarge WiFi duration
				 */
				wait_count = 0;
				n = 3;
				up = 0;
				dn = 0;
				result = 1;
				RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					 "[BTCoex], Increase wifi duration!!\n");
			}
		} else if (retry_count <= 3) {
			/* <=3 retry in the last 2-second duration */
			up--;
			dn++;

			if (up <= 0)
				up = 0;

			if (dn == 2) {
				/* if continuous 2 retry count(every 2 seconds)
				 * >0 and < 3, reduce WiFi duration
				 */
				if (wait_count <= 2)
					/* avoid loop between the two levels */
					m++;
				else
					m = 1;

				if (m >= 20)
					/* maximum of m = 20 ' will recheck if
					 * need to adjust wifi duration in
					 * maximum time interval 120 seconds
					 */
					m = 20;

				n = 3 * m;
				up = 0;
				dn = 0;
				wait_count = 0;
				result = -1;
				RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					 "[BTCoex], Decrease wifi duration for retryCounter<3!!\n");
			}
		} else {
			/* retry count > 3, once retry count > 3, to reduce
			 * WiFi duration
			 */
			if (wait_count == 1)
				/* to avoid loop between the two levels */
				m++;
			else
				m = 1;

			if (m >= 20)
				/* maximum of m = 20 ' will recheck if need to
				 * adjust wifi duration in maximum time interval
				 * 120 seconds
				 */
				m = 20;

			n = 3 * m;
			up = 0;
			dn = 0;
			wait_count = 0;
			result = -1;
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], Decrease wifi duration for retryCounter>3!!\n");
		}

		if (result == -1) {
			if (coex_dm->cur_ps_tdma == 1) {
				halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC,
							true, 2);
				coex_dm->ps_tdma_du_adj_type = 2;
			} else if (coex_dm->cur_ps_tdma == 2) {
				halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC,
							true, 9);
				coex_dm->ps_tdma_du_adj_type = 9;
			} else if (coex_dm->cur_ps_tdma == 9) {
				halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC,
							true, 11);
				coex_dm->ps_tdma_du_adj_type = 11;
			}
		} else if (result == 1) {
			if (coex_dm->cur_ps_tdma == 11) {
				halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC,
							true, 9);
				coex_dm->ps_tdma_du_adj_type = 9;
			} else if (coex_dm->cur_ps_tdma == 9) {
				halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC,
							true, 2);
				coex_dm->ps_tdma_du_adj_type = 2;
			} else if (coex_dm->cur_ps_tdma == 2) {
				halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC,
							true, 1);
				coex_dm->ps_tdma_du_adj_type = 1;
			}
		}

		if (coex_dm->cur_ps_tdma != 1 && coex_dm->cur_ps_tdma != 2 &&
		    coex_dm->cur_ps_tdma != 9 && coex_dm->cur_ps_tdma != 11) {
			/* recover to previous adjust type */
			halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC, true,
						coex_dm->ps_tdma_du_adj_type);
		}
	}
}