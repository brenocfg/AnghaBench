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
struct btc_bt_link_info {scalar_t__ a2dp_exist; } ;
struct btc_coexist {struct btc_bt_link_info bt_link_info; } ;
struct TYPE_2__ {scalar_t__ bt_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_PS_WIFI_NATIVE ; 
 scalar_t__ BT_8821A_1ANT_BT_STATUS_ACL_BUSY ; 
 scalar_t__ BT_8821A_1ANT_BT_STATUS_ACL_SCO_BUSY ; 
 scalar_t__ BT_8821A_1ANT_BT_STATUS_SCO_BUSY ; 
 int /*<<< orphan*/  BT_8821A_1ANT_WIFI_STATUS_CONNECTED_SCAN ; 
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int /*<<< orphan*/  btc8821a1ant_act_bt_sco_hid_only_busy (struct btc_coexist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btc8821a1ant_coex_table_with_type (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  btc8821a1ant_power_save_state (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  btc8821a1ant_ps_tdma (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 
 TYPE_1__* coex_dm ; 

__attribute__((used)) static
void btc8821a1ant_action_wifi_connected_scan(struct btc_coexist *btcoexist)
{
	struct btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;

	/* power save state */
	btc8821a1ant_power_save_state(btcoexist,
				      BTC_PS_WIFI_NATIVE, 0x0, 0x0);

	/* tdma and coex table */
	if (BT_8821A_1ANT_BT_STATUS_ACL_BUSY == coex_dm->bt_status) {
		if (bt_link_info->a2dp_exist) {
			btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 14);
			btc8821a1ant_coex_table_with_type(btcoexist,
							  NORMAL_EXEC, 1);
		} else {
			btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 20);
			btc8821a1ant_coex_table_with_type(btcoexist,
							  NORMAL_EXEC, 4);
		}
	} else if ((coex_dm->bt_status == BT_8821A_1ANT_BT_STATUS_SCO_BUSY) ||
		   (coex_dm->bt_status ==
		    BT_8821A_1ANT_BT_STATUS_ACL_SCO_BUSY)) {
		btc8821a1ant_act_bt_sco_hid_only_busy(btcoexist,
			BT_8821A_1ANT_WIFI_STATUS_CONNECTED_SCAN);
	} else {
		btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 8);
		btc8821a1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 2);
	}
}