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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dm_type; } ;
struct rtl_priv {TYPE_1__ dm; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_TYPE_BYDRIVER ; 
 int /*<<< orphan*/  ROFDM0_XAAGCCORE1 ; 
 int /*<<< orphan*/  rtl88e_dm_antenna_div_init (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl88e_dm_init_dynamic_txpower (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl88e_dm_init_edca_turbo (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl88e_dm_init_rate_adaptive_mask (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl88e_dm_init_txpower_tracking (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl92c_dm_init_dynamic_bb_powersaving (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_dm_diginit (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_get_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

void rtl88e_dm_init(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u32 cur_igvalue = rtl_get_bbreg(hw, ROFDM0_XAAGCCORE1, 0x7f);

	rtlpriv->dm.dm_type = DM_TYPE_BYDRIVER;
	rtl_dm_diginit(hw, cur_igvalue);
	rtl88e_dm_init_dynamic_txpower(hw);
	rtl88e_dm_init_edca_turbo(hw);
	rtl88e_dm_init_rate_adaptive_mask(hw);
	rtl88e_dm_init_txpower_tracking(hw);
	rtl92c_dm_init_dynamic_bb_powersaving(hw);
	rtl88e_dm_antenna_div_init(hw);
}