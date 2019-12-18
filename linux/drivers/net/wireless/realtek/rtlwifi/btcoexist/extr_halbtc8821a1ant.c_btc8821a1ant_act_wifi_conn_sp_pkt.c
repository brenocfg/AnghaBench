#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct btc_bt_link_info {scalar_t__ pan_exist; scalar_t__ a2dp_exist; scalar_t__ hid_exist; scalar_t__ sco_exist; } ;
struct btc_coexist {struct btc_bt_link_info bt_link_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_PS_WIFI_NATIVE ; 
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int /*<<< orphan*/  btc8821a1ant_coex_table_with_type (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  btc8821a1ant_power_save_state (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  btc8821a1ant_ps_tdma (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void btc8821a1ant_act_wifi_conn_sp_pkt(struct btc_coexist *btcoexist)
{
	struct btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;

	btc8821a1ant_power_save_state(btcoexist, BTC_PS_WIFI_NATIVE,
				      0x0, 0x0);

	/* tdma and coex table */
	if ((bt_link_info->sco_exist) || (bt_link_info->hid_exist) ||
	    (bt_link_info->a2dp_exist)) {
		btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 32);
		btc8821a1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 4);
	}

	if ((bt_link_info->hid_exist) && (bt_link_info->a2dp_exist)) {
		btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 14);
		btc8821a1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 1);
	} else if (bt_link_info->pan_exist) {
		btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 20);
		btc8821a1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 4);
	} else {
		btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 8);
		btc8821a1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 2);
	}
}