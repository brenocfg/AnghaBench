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
 int /*<<< orphan*/  DM_BIT_IGI_11N ; 
 int /*<<< orphan*/  DM_REG_IGI_A_11N ; 
 int /*<<< orphan*/  DM_TYPE_BYDRIVER ; 
 int /*<<< orphan*/  rtl92ee_dm_init_dynamic_atc_switch (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl92ee_dm_init_edca_turbo (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl92ee_dm_init_primary_cca_check (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl92ee_dm_init_rate_adaptive_mask (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl92ee_dm_init_txpower_tracking (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_dm_diginit (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_get_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

void rtl92ee_dm_init(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u32 cur_igvalue = rtl_get_bbreg(hw, DM_REG_IGI_A_11N, DM_BIT_IGI_11N);

	rtlpriv->dm.dm_type = DM_TYPE_BYDRIVER;

	rtl_dm_diginit(hw, cur_igvalue);
	rtl92ee_dm_init_rate_adaptive_mask(hw);
	rtl92ee_dm_init_primary_cca_check(hw);
	rtl92ee_dm_init_edca_turbo(hw);
	rtl92ee_dm_init_txpower_tracking(hw);
	rtl92ee_dm_init_dynamic_atc_switch(hw);
}