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
 int /*<<< orphan*/  ex_btc8723b1ant_pnp_notify (struct btc_coexist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ex_btc8723b2ant_pnp_notify (struct btc_coexist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ex_btc8821a1ant_pnp_notify (struct btc_coexist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ex_btc8821a2ant_pnp_notify (struct btc_coexist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  halbtc_is_bt_coexist_available (struct btc_coexist*) ; 

void exhalbtc_pnp_notify(struct btc_coexist *btcoexist, u8 pnp_state)
{
	if (!halbtc_is_bt_coexist_available(btcoexist))
		return;

	/* currently only 1ant we have to do the notification,
	 * once pnp is notified to sleep state, we have to leave LPS that
	 * we can sleep normally.
	 */

	if (IS_HARDWARE_TYPE_8723B(btcoexist->adapter)) {
		if (btcoexist->board_info.btdm_ant_num == 1)
			ex_btc8723b1ant_pnp_notify(btcoexist, pnp_state);
		else if (btcoexist->board_info.btdm_ant_num == 2)
			ex_btc8723b2ant_pnp_notify(btcoexist, pnp_state);
	} else if (IS_HARDWARE_TYPE_8821(btcoexist->adapter)) {
		if (btcoexist->board_info.btdm_ant_num == 1)
			ex_btc8821a1ant_pnp_notify(btcoexist, pnp_state);
		else if (btcoexist->board_info.btdm_ant_num == 2)
			ex_btc8821a2ant_pnp_notify(btcoexist, pnp_state);
	} else if (IS_HARDWARE_TYPE_8192E(btcoexist->adapter)) {
	}
}