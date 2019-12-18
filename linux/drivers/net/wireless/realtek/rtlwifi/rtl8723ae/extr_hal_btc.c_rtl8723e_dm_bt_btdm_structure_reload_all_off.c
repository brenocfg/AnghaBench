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
struct ieee80211_hw {int dummy; } ;
struct btdm_8723 {int all_off; int pta_on; int wlan_act_hi; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtl8723e_dm_bt_btdm_structure_reload (struct ieee80211_hw*,struct btdm_8723*) ; 

__attribute__((used)) static void rtl8723e_dm_bt_btdm_structure_reload_all_off(struct ieee80211_hw *hw,
							 struct btdm_8723 *btdm)
{
	rtl8723e_dm_bt_btdm_structure_reload(hw, btdm);
	btdm->all_off = true;
	btdm->pta_on = false;
	btdm->wlan_act_hi = 0x10;
}