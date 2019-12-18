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
typedef  scalar_t__ u8 ;
struct TYPE_2__ {int cnt_all; } ;
struct dig_t {scalar_t__ cur_igvalue; } ;
struct rtl_priv {TYPE_1__ falsealm_cnt; struct dig_t dm_digtable; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ DM_DIG_FA_LOWER ; 
 int DM_DIG_FA_TH0 ; 
 int DM_DIG_FA_TH1 ; 
 int DM_DIG_FA_TH2 ; 
 scalar_t__ DM_DIG_FA_UPPER ; 
 int /*<<< orphan*/  rtl92c_dm_write_dig (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void rtl92c_dm_ctrl_initgain_by_fa(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct dig_t *dm_digtable = &rtlpriv->dm_digtable;
	u8 value_igi = dm_digtable->cur_igvalue;

	if (rtlpriv->falsealm_cnt.cnt_all < DM_DIG_FA_TH0)
		value_igi--;
	else if (rtlpriv->falsealm_cnt.cnt_all < DM_DIG_FA_TH1)
		value_igi += 0;
	else if (rtlpriv->falsealm_cnt.cnt_all < DM_DIG_FA_TH2)
		value_igi++;
	else if (rtlpriv->falsealm_cnt.cnt_all >= DM_DIG_FA_TH2)
		value_igi += 2;

	if (value_igi > DM_DIG_FA_UPPER)
		value_igi = DM_DIG_FA_UPPER;
	else if (value_igi < DM_DIG_FA_LOWER)
		value_igi = DM_DIG_FA_LOWER;

	if (rtlpriv->falsealm_cnt.cnt_all > 10000)
		value_igi = DM_DIG_FA_UPPER;

	dm_digtable->cur_igvalue = value_igi;
	rtl92c_dm_write_dig(hw);
}