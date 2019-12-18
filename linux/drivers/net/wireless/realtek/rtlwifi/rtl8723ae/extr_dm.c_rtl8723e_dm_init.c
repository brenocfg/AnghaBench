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
struct TYPE_2__ {int /*<<< orphan*/  dm_type; } ;
struct rtl_priv {TYPE_1__ dm; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_TYPE_BYDRIVER ; 
 int /*<<< orphan*/  rtl8723_dm_init_dynamic_bb_powersaving (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8723_dm_init_dynamic_txpower (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8723_dm_init_edca_turbo (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8723e_dm_init_rate_adaptive_mask (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8723e_dm_initialize_txpower_tracking (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_dm_diginit (struct ieee80211_hw*,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

void rtl8723e_dm_init(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpriv->dm.dm_type = DM_TYPE_BYDRIVER;
	rtl_dm_diginit(hw, 0x20);
	rtl8723_dm_init_dynamic_txpower(hw);
	rtl8723_dm_init_edca_turbo(hw);
	rtl8723e_dm_init_rate_adaptive_mask(hw);
	rtl8723e_dm_initialize_txpower_tracking(hw);
	rtl8723_dm_init_dynamic_bb_powersaving(hw);
}