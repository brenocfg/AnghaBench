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
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rtl_priv {int dummy; } ;
struct TYPE_4__ {scalar_t__ a2dp_only; int /*<<< orphan*/  hid_only; } ;
struct btc_coexist {TYPE_1__ bt_link_info; int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;struct rtl_priv* adapter; } ;
struct TYPE_6__ {scalar_t__ bt_status; } ;
struct TYPE_5__ {scalar_t__ scan_ap_num; int /*<<< orphan*/  hid_exist; int /*<<< orphan*/  a2dp_exist; int /*<<< orphan*/  pan_exist; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_ANT_PATH_PTA ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_4_WAY_PROGRESS ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_AP_MODE_ENABLE ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_BUSY ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_LINK ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_ROAM ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_SCAN ; 
 int /*<<< orphan*/  BTC_PS_LPS_ON ; 
 int /*<<< orphan*/  BTC_PS_WIFI_NATIVE ; 
 scalar_t__ BT_8723B_1ANT_BT_STATUS_ACL_BUSY ; 
 scalar_t__ BT_8723B_1ANT_BT_STATUS_ACL_SCO_BUSY ; 
 scalar_t__ BT_8723B_1ANT_BT_STATUS_SCO_BUSY ; 
 scalar_t__ BT_8723B_1ANT_WIFI_NOISY_THRESH ; 
 int /*<<< orphan*/  BT_8723B_1ANT_WIFI_STATUS_CONNECTED_BUSY ; 
 int /*<<< orphan*/  BT_8723B_1ANT_WIFI_STATUS_CONNECTED_IDLE ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  btc8723b1ant_act_bt_sco_hid_only_busy (struct btc_coexist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btc8723b1ant_action_wifi_conn_scan (struct btc_coexist*) ; 
 TYPE_3__* coex_dm ; 
 TYPE_2__* coex_sta ; 
 int /*<<< orphan*/  halbtc8723b1ant_action_wifi_connected_bt_acl_busy (struct btc_coexist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  halbtc8723b1ant_action_wifi_connected_special_packet (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8723b1ant_coex_table_with_type (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8723b1ant_power_save_state (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  halbtc8723b1ant_ps_tdma (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  halbtc8723b1ant_set_ant_path (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub4 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub5 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub6 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void halbtc8723b1ant_action_wifi_connected(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	bool wifi_busy = false;
	bool scan = false, link = false, roam = false;
	bool under_4way = false, ap_enable = false;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], CoexForWifiConnect()===>\n");

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_4_WAY_PROGRESS,
			   &under_4way);
	if (under_4way) {
		halbtc8723b1ant_action_wifi_connected_special_packet(btcoexist);
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], CoexForWifiConnect(), return for wifi is under 4way<===\n");
		return;
	}

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_SCAN, &scan);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_LINK, &link);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_ROAM, &roam);

	if (scan || link || roam) {
		if (scan)
			btc8723b1ant_action_wifi_conn_scan(btcoexist);
		else
			halbtc8723b1ant_action_wifi_connected_special_packet(
								     btcoexist);
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], CoexForWifiConnect(), return for wifi is under scan<===\n");
		return;
	}

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_AP_MODE_ENABLE,
			   &ap_enable);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_BUSY, &wifi_busy);
	/* power save state */
	if (!ap_enable &&
	    coex_dm->bt_status == BT_8723B_1ANT_BT_STATUS_ACL_BUSY &&
	    !btcoexist->bt_link_info.hid_only) {
		if (btcoexist->bt_link_info.a2dp_only) {
			if (!wifi_busy) {
				halbtc8723b1ant_power_save_state(btcoexist,
							 BTC_PS_WIFI_NATIVE,
							 0x0, 0x0);
			} else { /* busy */
				if (coex_sta->scan_ap_num >=
				    BT_8723B_1ANT_WIFI_NOISY_THRESH)
					/* no force LPS, no PS-TDMA,
					 * use pure TDMA
					 */
					halbtc8723b1ant_power_save_state(
						btcoexist, BTC_PS_WIFI_NATIVE,
						0x0, 0x0);
				else
					halbtc8723b1ant_power_save_state(
						btcoexist, BTC_PS_LPS_ON, 0x50,
						0x4);
			}
		} else if ((!coex_sta->pan_exist) && (!coex_sta->a2dp_exist) &&
			   (!coex_sta->hid_exist))
			halbtc8723b1ant_power_save_state(
				btcoexist, BTC_PS_WIFI_NATIVE, 0x0, 0x0);
		else
			halbtc8723b1ant_power_save_state(btcoexist,
							 BTC_PS_LPS_ON,
							 0x50, 0x4);
	} else {
		halbtc8723b1ant_power_save_state(btcoexist, BTC_PS_WIFI_NATIVE,
						 0x0, 0x0);
	}
	/* tdma and coex table */
	if (!wifi_busy) {
		if (coex_dm->bt_status == BT_8723B_1ANT_BT_STATUS_ACL_BUSY) {
			halbtc8723b1ant_action_wifi_connected_bt_acl_busy(
				btcoexist,
				BT_8723B_1ANT_WIFI_STATUS_CONNECTED_IDLE);
		} else if (coex_dm->bt_status ==
				BT_8723B_1ANT_BT_STATUS_SCO_BUSY ||
			   coex_dm->bt_status ==
				BT_8723B_1ANT_BT_STATUS_ACL_SCO_BUSY) {
			btc8723b1ant_act_bt_sco_hid_only_busy(btcoexist,
				     BT_8723B_1ANT_WIFI_STATUS_CONNECTED_IDLE);
		} else {
			halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC,
						false, 8);
			halbtc8723b1ant_set_ant_path(btcoexist,
						     BTC_ANT_PATH_PTA,
						     NORMAL_EXEC, false, false);
			halbtc8723b1ant_coex_table_with_type(btcoexist,
							     NORMAL_EXEC, 2);
		}
	} else {
		if (coex_dm->bt_status == BT_8723B_1ANT_BT_STATUS_ACL_BUSY) {
			halbtc8723b1ant_action_wifi_connected_bt_acl_busy(
				btcoexist,
				BT_8723B_1ANT_WIFI_STATUS_CONNECTED_BUSY);
		} else if (coex_dm->bt_status ==
				BT_8723B_1ANT_BT_STATUS_SCO_BUSY ||
			   coex_dm->bt_status ==
				BT_8723B_1ANT_BT_STATUS_ACL_SCO_BUSY) {
			btc8723b1ant_act_bt_sco_hid_only_busy(btcoexist,
				    BT_8723B_1ANT_WIFI_STATUS_CONNECTED_BUSY);
		} else {
			halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC,
						true, 32);
			halbtc8723b1ant_set_ant_path(btcoexist,
						     BTC_ANT_PATH_PTA,
						     NORMAL_EXEC, false, false);
			halbtc8723b1ant_coex_table_with_type(btcoexist,
							     NORMAL_EXEC, 4);
		}
	}
}