#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct btc_bt_link_info {scalar_t__ pan_exist; scalar_t__ a2dp_exist; scalar_t__ hid_exist; scalar_t__ pan_only; scalar_t__ a2dp_only; scalar_t__ hid_only; } ;
struct btc_coexist {struct btc_bt_link_info bt_link_info; } ;
struct TYPE_2__ {int auto_tdma_adjust; } ;

/* Variables and functions */
 scalar_t__ BTC_RSSI_STATE_HIGH ; 
 scalar_t__ BTC_RSSI_STATE_STAY_HIGH ; 
 scalar_t__ BT_8821A_1ANT_WIFI_STATUS_CONNECTED_IDLE ; 
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int /*<<< orphan*/  btc8821a1ant_act_bt_sco_hid_only_busy (struct btc_coexist*,scalar_t__) ; 
 scalar_t__ btc8821a1ant_bt_rssi_state (struct btc_coexist*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btc8821a1ant_coex_table_with_type (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  btc8821a1ant_ps_tdma (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 
 TYPE_1__* coex_dm ; 

__attribute__((used)) static void btc8821a1ant_act_wifi_con_bt_acl_busy(struct btc_coexist *btcoexist,
						  u8 wifi_status)
{
	u8 bt_rssi_state;

	struct btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;

	bt_rssi_state = btc8821a1ant_bt_rssi_state(btcoexist, 2, 28, 0);

	if (bt_link_info->hid_only) {
		/* HID */
		btc8821a1ant_act_bt_sco_hid_only_busy(btcoexist,
						      wifi_status);
		coex_dm->auto_tdma_adjust = false;
		return;
	} else if (bt_link_info->a2dp_only) {
		/* A2DP */
		if (wifi_status == BT_8821A_1ANT_WIFI_STATUS_CONNECTED_IDLE) {
			btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 32);
			btc8821a1ant_coex_table_with_type(btcoexist,
							  NORMAL_EXEC, 1);
			coex_dm->auto_tdma_adjust = false;
		} else if ((bt_rssi_state != BTC_RSSI_STATE_HIGH) &&
			   (bt_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) {
			btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 14);
			btc8821a1ant_coex_table_with_type(btcoexist,
							  NORMAL_EXEC, 1);
		} else {
			/* for low BT RSSI */
			btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 14);
			btc8821a1ant_coex_table_with_type(btcoexist,
							  NORMAL_EXEC, 1);
			coex_dm->auto_tdma_adjust = false;
		}
	} else if (bt_link_info->hid_exist && bt_link_info->a2dp_exist) {
		/* HID+A2DP */
		if ((bt_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (bt_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) {
			btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC,
					     true, 14);
			coex_dm->auto_tdma_adjust = false;
		} else {
			/*for low BT RSSI*/
			btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC,
					     true, 14);
			coex_dm->auto_tdma_adjust = false;
		}

		btc8821a1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 1);
	} else if ((bt_link_info->pan_only) ||
		(bt_link_info->hid_exist && bt_link_info->pan_exist)) {
		/* PAN(OPP, FTP), HID+PAN(OPP, FTP) */
		btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 3);
		btc8821a1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 6);
		coex_dm->auto_tdma_adjust = false;
	} else if (((bt_link_info->a2dp_exist) && (bt_link_info->pan_exist)) ||
		   (bt_link_info->hid_exist && bt_link_info->a2dp_exist &&
		    bt_link_info->pan_exist)) {
		/* A2DP+PAN(OPP, FTP), HID+A2DP+PAN(OPP, FTP) */
		btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 43);
		btc8821a1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 1);
		coex_dm->auto_tdma_adjust = false;
	} else {
		btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 11);
		btc8821a1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 1);
		coex_dm->auto_tdma_adjust = false;
	}
}