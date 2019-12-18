#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_6__ {int cnt_all; } ;
struct TYPE_5__ {scalar_t__ opmode; } ;
struct TYPE_4__ {int dm_initialgain_enable; } ;
struct dig_t {scalar_t__ cur_igvalue; int dig_enable_flag; scalar_t__ cur_sta_cstate; scalar_t__ dig_min_0; int media_connect_0; scalar_t__ rssi_val_min; scalar_t__ rx_gain_max; scalar_t__ antdiv_rssi_max; int large_fa_hit; scalar_t__ forbidden_igi; int rx_gain_min; int recover_cnt; } ;
struct rtl_priv {TYPE_3__ falsealm_cnt; TYPE_2__ mac80211; TYPE_1__ dm; struct dig_t dm_digtable; } ;
struct rtl_mac {int act_scanning; scalar_t__ link_state; } ;
struct rtl_efuse {scalar_t__ antenna_div_type; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ CG_TRX_HW_ANTDIV ; 
 int /*<<< orphan*/  COMP_DIG ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 scalar_t__ DIG_STA_CONNECT ; 
 void* DIG_STA_DISCONNECT ; 
 scalar_t__ DM_DIG_FA_LOWER ; 
 int DM_DIG_FA_TH0 ; 
 int DM_DIG_FA_TH1 ; 
 int DM_DIG_FA_TH2 ; 
 scalar_t__ DM_DIG_FA_UPPER ; 
 scalar_t__ DM_DIG_MAX ; 
 scalar_t__ DM_DIG_MAX_AP ; 
 scalar_t__ DM_DIG_MIN ; 
 scalar_t__ MAC80211_LINKED ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rtl88e_dm_cck_packet_detection_thresh (struct ieee80211_hw*) ; 
 scalar_t__ rtl88e_dm_initial_gain_min_pwdb (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl88e_dm_write_dig (struct ieee80211_hw*) ; 
 struct rtl_efuse* rtl_efuse (struct rtl_priv*) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void rtl88e_dm_dig(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	struct rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	struct dig_t *dm_dig = &rtlpriv->dm_digtable;
	u8 dig_dynamic_min, dig_maxofmin;
	bool bfirstconnect;
	u8 dm_dig_max, dm_dig_min;
	u8 current_igi = dm_dig->cur_igvalue;

	if (rtlpriv->dm.dm_initialgain_enable == false)
		return;
	if (dm_dig->dig_enable_flag == false)
		return;
	if (mac->act_scanning == true)
		return;

	if (mac->link_state >= MAC80211_LINKED)
		dm_dig->cur_sta_cstate = DIG_STA_CONNECT;
	else
		dm_dig->cur_sta_cstate = DIG_STA_DISCONNECT;
	if (rtlpriv->mac80211.opmode == NL80211_IFTYPE_AP ||
	    rtlpriv->mac80211.opmode == NL80211_IFTYPE_ADHOC)
		dm_dig->cur_sta_cstate = DIG_STA_DISCONNECT;

	dm_dig_max = DM_DIG_MAX;
	dm_dig_min = DM_DIG_MIN;
	dig_maxofmin = DM_DIG_MAX_AP;
	dig_dynamic_min = dm_dig->dig_min_0;
	bfirstconnect = ((mac->link_state >= MAC80211_LINKED) ? true : false) &&
			 !dm_dig->media_connect_0;

	dm_dig->rssi_val_min =
		rtl88e_dm_initial_gain_min_pwdb(hw);

	if (mac->link_state >= MAC80211_LINKED) {
		if ((dm_dig->rssi_val_min + 20) > dm_dig_max)
			dm_dig->rx_gain_max = dm_dig_max;
		else if ((dm_dig->rssi_val_min + 20) < dm_dig_min)
			dm_dig->rx_gain_max = dm_dig_min;
		else
			dm_dig->rx_gain_max = dm_dig->rssi_val_min + 20;

		if (rtlefuse->antenna_div_type == CG_TRX_HW_ANTDIV) {
			dig_dynamic_min  = dm_dig->antdiv_rssi_max;
		} else {
			if (dm_dig->rssi_val_min < dm_dig_min)
				dig_dynamic_min = dm_dig_min;
			else if (dm_dig->rssi_val_min < dig_maxofmin)
				dig_dynamic_min = dig_maxofmin;
			else
				dig_dynamic_min = dm_dig->rssi_val_min;
		}
	} else {
		dm_dig->rx_gain_max = dm_dig_max;
		dig_dynamic_min = dm_dig_min;
		RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD, "no link\n");
	}

	if (rtlpriv->falsealm_cnt.cnt_all > 10000) {
		dm_dig->large_fa_hit++;
		if (dm_dig->forbidden_igi < current_igi) {
			dm_dig->forbidden_igi = current_igi;
			dm_dig->large_fa_hit = 1;
		}

		if (dm_dig->large_fa_hit >= 3) {
			if ((dm_dig->forbidden_igi + 1) >
				dm_dig->rx_gain_max)
				dm_dig->rx_gain_min =
					dm_dig->rx_gain_max;
			else
				dm_dig->rx_gain_min =
					dm_dig->forbidden_igi + 1;
			dm_dig->recover_cnt = 3600;
		}
	} else {
		if (dm_dig->recover_cnt != 0) {
			dm_dig->recover_cnt--;
		} else {
			if (dm_dig->large_fa_hit == 0) {
				if ((dm_dig->forbidden_igi - 1) <
				    dig_dynamic_min) {
					dm_dig->forbidden_igi = dig_dynamic_min;
					dm_dig->rx_gain_min = dig_dynamic_min;
				} else {
					dm_dig->forbidden_igi--;
					dm_dig->rx_gain_min =
						dm_dig->forbidden_igi + 1;
				}
			} else if (dm_dig->large_fa_hit == 3) {
				dm_dig->large_fa_hit = 0;
			}
		}
	}

	if (dm_dig->cur_sta_cstate == DIG_STA_CONNECT) {
		if (bfirstconnect) {
			current_igi = dm_dig->rssi_val_min;
		} else {
			if (rtlpriv->falsealm_cnt.cnt_all > DM_DIG_FA_TH2)
				current_igi += 2;
			else if (rtlpriv->falsealm_cnt.cnt_all > DM_DIG_FA_TH1)
				current_igi++;
			else if (rtlpriv->falsealm_cnt.cnt_all < DM_DIG_FA_TH0)
				current_igi--;
		}
	} else {
		if (rtlpriv->falsealm_cnt.cnt_all > 10000)
			current_igi += 2;
		else if (rtlpriv->falsealm_cnt.cnt_all > 8000)
			current_igi++;
		else if (rtlpriv->falsealm_cnt.cnt_all < 500)
			current_igi--;
	}

	if (current_igi > DM_DIG_FA_UPPER)
		current_igi = DM_DIG_FA_UPPER;
	else if (current_igi < DM_DIG_FA_LOWER)
		current_igi = DM_DIG_FA_LOWER;

	if (rtlpriv->falsealm_cnt.cnt_all > 10000)
		current_igi = DM_DIG_FA_UPPER;

	dm_dig->cur_igvalue = current_igi;
	rtl88e_dm_write_dig(hw);
	dm_dig->media_connect_0 =
		((mac->link_state >= MAC80211_LINKED) ? true : false);
	dm_dig->dig_min_0 = dig_dynamic_min;

	rtl88e_dm_cck_packet_detection_thresh(hw);
}