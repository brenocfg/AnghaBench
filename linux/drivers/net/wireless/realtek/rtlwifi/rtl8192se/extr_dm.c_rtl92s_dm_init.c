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
struct TYPE_2__ {int undec_sm_pwdb; int /*<<< orphan*/  dm_type; } ;
struct rtl_priv {TYPE_1__ dm; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_TYPE_BYDRIVER ; 
 int /*<<< orphan*/  FW_CCA_CHK_ENABLE ; 
 int /*<<< orphan*/  WFM5 ; 
 int /*<<< orphan*/  _rtl92s_dm_init_dig (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  _rtl92s_dm_init_dynamic_txpower (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  _rtl92s_dm_init_rate_adaptive_mask (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  _rtl92s_dm_init_txpowertracking_thermalmeter (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl92s_dm_init_edca_turbo (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rtl92s_dm_init(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpriv->dm.dm_type = DM_TYPE_BYDRIVER;
	rtlpriv->dm.undec_sm_pwdb = -1;

	_rtl92s_dm_init_dynamic_txpower(hw);
	rtl92s_dm_init_edca_turbo(hw);
	_rtl92s_dm_init_rate_adaptive_mask(hw);
	_rtl92s_dm_init_txpowertracking_thermalmeter(hw);
	_rtl92s_dm_init_dig(hw);

	rtl_write_dword(rtlpriv, WFM5, FW_CCA_CHK_ENABLE);
}