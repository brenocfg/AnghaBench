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
struct rtl_priv {int dummy; } ;
struct rtl_mac {scalar_t__ link_state; } ;
struct rtl_efuse {scalar_t__ antenna_div_type; } ;
struct fast_ant_training {int becomelinked; } ;
struct rtl_dm {struct fast_ant_training fat_table; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 scalar_t__ CGCS_RX_HW_ANTDIV ; 
 scalar_t__ CG_TRX_HW_ANTDIV ; 
 scalar_t__ CG_TRX_SMART_ANTDIV ; 
 int /*<<< orphan*/  COMP_DIG ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  DM_REG_CCK_ANTDIV_PARA1_11N ; 
 int /*<<< orphan*/  DM_REG_IGI_A_11N ; 
 int /*<<< orphan*/  DM_REG_TX_ANT_CTRL_11N ; 
 scalar_t__ MAC80211_LINKED ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rtl88e_dm_fast_ant_training (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl88e_dm_hw_ant_div (struct ieee80211_hw*) ; 
 struct rtl_dm* rtl_dm (struct rtl_priv*) ; 
 struct rtl_efuse* rtl_efuse (struct rtl_priv*) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtl88e_dm_antenna_diversity(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	struct rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	struct rtl_dm *rtldm = rtl_dm(rtl_priv(hw));
	struct fast_ant_training *pfat_table = &rtldm->fat_table;

	if (mac->link_state < MAC80211_LINKED) {
		RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD, "No Link\n");
		if (pfat_table->becomelinked) {
			RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD,
				 "need to turn off HW AntDiv\n");
			rtl_set_bbreg(hw, DM_REG_IGI_A_11N, BIT(7), 0);
			rtl_set_bbreg(hw, DM_REG_CCK_ANTDIV_PARA1_11N,
				      BIT(15), 0);
			if (rtlefuse->antenna_div_type == CG_TRX_HW_ANTDIV)
				rtl_set_bbreg(hw, DM_REG_TX_ANT_CTRL_11N,
					      BIT(21), 0);
			pfat_table->becomelinked =
				(mac->link_state == MAC80211_LINKED) ?
				true : false;
		}
		return;
	} else {
		if (!pfat_table->becomelinked) {
			RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD,
				 "Need to turn on HW AntDiv\n");
			rtl_set_bbreg(hw, DM_REG_IGI_A_11N, BIT(7), 1);
			rtl_set_bbreg(hw, DM_REG_CCK_ANTDIV_PARA1_11N,
				      BIT(15), 1);
			if (rtlefuse->antenna_div_type == CG_TRX_HW_ANTDIV)
				rtl_set_bbreg(hw, DM_REG_TX_ANT_CTRL_11N,
					      BIT(21), 1);
			pfat_table->becomelinked =
				(mac->link_state >= MAC80211_LINKED) ?
				true : false;
		}
	}

	if ((rtlefuse->antenna_div_type == CG_TRX_HW_ANTDIV) ||
	    (rtlefuse->antenna_div_type == CGCS_RX_HW_ANTDIV))
		rtl88e_dm_hw_ant_div(hw);
	else if (rtlefuse->antenna_div_type == CG_TRX_SMART_ANTDIV)
		rtl88e_dm_fast_ant_training(hw);
}