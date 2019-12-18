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
struct TYPE_4__ {int btdm_ant_num; } ;
struct TYPE_3__ {int /*<<< orphan*/  cnt_connect_notify; } ;
struct btc_coexist {TYPE_2__ board_info; int /*<<< orphan*/  adapter; int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;scalar_t__ manual_control; TYPE_1__ statistics; } ;

/* Variables and functions */
 scalar_t__ BTC_ASSOCIATE_FINISH ; 
 scalar_t__ BTC_ASSOCIATE_START ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_UNDER_5G ; 
 scalar_t__ IS_HARDWARE_TYPE_8192E (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_HARDWARE_TYPE_8723B (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_HARDWARE_TYPE_8821 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ex_btc8192e2ant_connect_notify (struct btc_coexist*,scalar_t__) ; 
 int /*<<< orphan*/  ex_btc8723b1ant_connect_notify (struct btc_coexist*,scalar_t__) ; 
 int /*<<< orphan*/  ex_btc8723b2ant_connect_notify (struct btc_coexist*,scalar_t__) ; 
 int /*<<< orphan*/  ex_btc8821a1ant_connect_notify (struct btc_coexist*,scalar_t__) ; 
 int /*<<< orphan*/  ex_btc8821a2ant_connect_notify (struct btc_coexist*,scalar_t__) ; 
 int /*<<< orphan*/  halbtc_is_bt_coexist_available (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc_leave_low_power (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc_normal_low_power (struct btc_coexist*) ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 

void exhalbtc_connect_notify(struct btc_coexist *btcoexist, u8 action)
{
	u8 asso_type;
	bool wifi_under_5g;

	if (!halbtc_is_bt_coexist_available(btcoexist))
		return;
	btcoexist->statistics.cnt_connect_notify++;
	if (btcoexist->manual_control)
		return;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_UNDER_5G, &wifi_under_5g);

	if (action)
		asso_type = BTC_ASSOCIATE_START;
	else
		asso_type = BTC_ASSOCIATE_FINISH;

	halbtc_leave_low_power(btcoexist);

	if (IS_HARDWARE_TYPE_8821(btcoexist->adapter)) {
		if (btcoexist->board_info.btdm_ant_num == 2)
			ex_btc8821a2ant_connect_notify(btcoexist, asso_type);
		else if (btcoexist->board_info.btdm_ant_num == 1)
			ex_btc8821a1ant_connect_notify(btcoexist, asso_type);
	} else if (IS_HARDWARE_TYPE_8723B(btcoexist->adapter)) {
		if (btcoexist->board_info.btdm_ant_num == 2)
			ex_btc8723b2ant_connect_notify(btcoexist, asso_type);
		else if (btcoexist->board_info.btdm_ant_num == 1)
			ex_btc8723b1ant_connect_notify(btcoexist, asso_type);
	} else if (IS_HARDWARE_TYPE_8192E(btcoexist->adapter)) {
		if (btcoexist->board_info.btdm_ant_num == 2)
			ex_btc8192e2ant_connect_notify(btcoexist, asso_type);
	}

	halbtc_normal_low_power(btcoexist);
}