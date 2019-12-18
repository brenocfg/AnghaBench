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
struct rtl_priv {int dummy; } ;
struct btc_bt_link_info {int hid_exist; } ;
struct btc_coexist {int /*<<< orphan*/  auto_report_2ant; struct btc_bt_link_info bt_link_info; struct rtl_priv* adapter; } ;
struct TYPE_4__ {scalar_t__ auto_tdma_adjust; } ;
struct TYPE_3__ {int dis_ver_info_cnt; int high_priority_tx; int high_priority_rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_ANT_WIFI_AT_MAIN ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ btc8723b2ant_is_wifi_status_changed (struct btc_coexist*) ; 
 int /*<<< orphan*/  btc8723b2ant_monitor_bt_ctr (struct btc_coexist*) ; 
 int /*<<< orphan*/  btc8723b2ant_monitor_wifi_ctr (struct btc_coexist*) ; 
 int /*<<< orphan*/  btc8723b2ant_query_bt_info (struct btc_coexist*) ; 
 int /*<<< orphan*/  btc8723b2ant_run_coexist_mechanism (struct btc_coexist*) ; 
 int /*<<< orphan*/  btc8723b2ant_set_ant_path (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 
 TYPE_2__* coex_dm ; 
 TYPE_1__* coex_sta ; 

void ex_btc8723b2ant_periodical(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	struct btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], ==========================Periodical===========================\n");

	if (coex_sta->dis_ver_info_cnt <= 5) {
		coex_sta->dis_ver_info_cnt += 1;
		if (coex_sta->dis_ver_info_cnt == 3) {
			/* Antenna config to set 0x765 = 0x0 (GNT_BT control by
			 * PTA) after initial
			 */
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], Set GNT_BT control by PTA\n");
			btc8723b2ant_set_ant_path(
				btcoexist, BTC_ANT_WIFI_AT_MAIN, false, false);
		}
	}

	if (!btcoexist->auto_report_2ant) {
		btc8723b2ant_query_bt_info(btcoexist);
	} else {
		btc8723b2ant_monitor_bt_ctr(btcoexist);
		btc8723b2ant_monitor_wifi_ctr(btcoexist);

		/* for some BT speakers that High-Priority pkts appear before
		 * playing, this will cause HID exist
		 */
		if ((coex_sta->high_priority_tx +
		    coex_sta->high_priority_rx < 50) &&
		    (bt_link_info->hid_exist))
			bt_link_info->hid_exist = false;

		if (btc8723b2ant_is_wifi_status_changed(btcoexist) ||
		    coex_dm->auto_tdma_adjust)
			btc8723b2ant_run_coexist_mechanism(btcoexist);
	}
}