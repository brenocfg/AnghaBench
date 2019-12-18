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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int btdm_ant_num; } ;
struct btc_coexist {int /*<<< orphan*/  adapter; TYPE_1__ board_info; } ;

/* Variables and functions */
 scalar_t__ IS_HARDWARE_TYPE_8192E (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_HARDWARE_TYPE_8723B (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_HARDWARE_TYPE_8821 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ex_btc8723b1ant_rf_status_notify (struct btc_coexist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  halbtc_is_bt_coexist_available (struct btc_coexist*) ; 

void exhalbtc_rf_status_notify(struct btc_coexist *btcoexist, u8 type)
{
	if (!halbtc_is_bt_coexist_available(btcoexist))
		return;

	if (IS_HARDWARE_TYPE_8821(btcoexist->adapter)) {
	} else if (IS_HARDWARE_TYPE_8723B(btcoexist->adapter)) {
		if (btcoexist->board_info.btdm_ant_num == 1)
			ex_btc8723b1ant_rf_status_notify(btcoexist, type);
	} else if (IS_HARDWARE_TYPE_8192E(btcoexist->adapter)) {
	}
}