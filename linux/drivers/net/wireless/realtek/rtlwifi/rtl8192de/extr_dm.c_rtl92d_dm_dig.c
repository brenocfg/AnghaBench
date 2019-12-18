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
typedef  int u8 ;
struct TYPE_6__ {scalar_t__ current_bandtype; scalar_t__ earlymode_enable; } ;
struct TYPE_5__ {scalar_t__ opmode; scalar_t__ link_state; } ;
struct TYPE_4__ {int /*<<< orphan*/  dm_initialgain_enable; } ;
struct false_alarm_statistics {int cnt_all; } ;
struct dig_t {int cur_igvalue; int large_fa_hit; int forbidden_igi; int recover_cnt; int rx_gain_min; int /*<<< orphan*/  cursta_cstate; int /*<<< orphan*/  min_undec_pwdb_for_dm; int /*<<< orphan*/  last_min_undec_pwdb_for_dm; } ;
struct rtl_priv {TYPE_3__ rtlhal; TYPE_2__ mac80211; TYPE_1__ dm; struct false_alarm_statistics falsealm_cnt; struct dig_t dm_digtable; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ BAND_ON_5G ; 
 int /*<<< orphan*/  COMP_DIG ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  DIG_STA_CONNECT ; 
 int /*<<< orphan*/  DIG_STA_DISCONNECT ; 
 int DM_DIG_FA_LOWER ; 
 int DM_DIG_FA_TH0 ; 
 int DM_DIG_FA_TH1 ; 
 int DM_DIG_FA_TH2 ; 
 int DM_DIG_MAX ; 
 scalar_t__ MAC80211_LINKED ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  rtl92d_dm_cck_packet_detection_thresh (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl92d_dm_write_dig (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl92d_early_mode_enabled (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void rtl92d_dm_dig(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct dig_t *de_digtable = &rtlpriv->dm_digtable;
	u8 value_igi = de_digtable->cur_igvalue;
	struct false_alarm_statistics *falsealm_cnt = &(rtlpriv->falsealm_cnt);

	RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD, "==>\n");
	if (rtlpriv->rtlhal.earlymode_enable) {
		rtl92d_early_mode_enabled(rtlpriv);
		de_digtable->last_min_undec_pwdb_for_dm =
				 de_digtable->min_undec_pwdb_for_dm;
	}
	if (!rtlpriv->dm.dm_initialgain_enable)
		return;

	/* because we will send data pkt when scanning
	 * this will cause some ap like gear-3700 wep TP
	 * lower if we return here, this is the diff of
	 * mac80211 driver vs ieee80211 driver */
	/* if (rtlpriv->mac80211.act_scanning)
	 *      return; */

	/* Not STA mode return tmp */
	if (rtlpriv->mac80211.opmode != NL80211_IFTYPE_STATION)
		return;
	RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD, "progress\n");
	/* Decide the current status and if modify initial gain or not */
	if (rtlpriv->mac80211.link_state >= MAC80211_LINKED)
		de_digtable->cursta_cstate = DIG_STA_CONNECT;
	else
		de_digtable->cursta_cstate = DIG_STA_DISCONNECT;

	/* adjust initial gain according to false alarm counter */
	if (falsealm_cnt->cnt_all < DM_DIG_FA_TH0)
		value_igi--;
	else if (falsealm_cnt->cnt_all < DM_DIG_FA_TH1)
		value_igi += 0;
	else if (falsealm_cnt->cnt_all < DM_DIG_FA_TH2)
		value_igi++;
	else if (falsealm_cnt->cnt_all >= DM_DIG_FA_TH2)
		value_igi += 2;
	RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD,
		 "dm_DIG() Before: large_fa_hit=%d, forbidden_igi=%x\n",
		 de_digtable->large_fa_hit, de_digtable->forbidden_igi);
	RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD,
		 "dm_DIG() Before: Recover_cnt=%d, rx_gain_min=%x\n",
		 de_digtable->recover_cnt, de_digtable->rx_gain_min);

	/* deal with abnormally large false alarm */
	if (falsealm_cnt->cnt_all > 10000) {
		RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD,
			 "dm_DIG(): Abnormally false alarm case\n");

		de_digtable->large_fa_hit++;
		if (de_digtable->forbidden_igi < de_digtable->cur_igvalue) {
			de_digtable->forbidden_igi = de_digtable->cur_igvalue;
			de_digtable->large_fa_hit = 1;
		}
		if (de_digtable->large_fa_hit >= 3) {
			if ((de_digtable->forbidden_igi + 1) > DM_DIG_MAX)
				de_digtable->rx_gain_min = DM_DIG_MAX;
			else
				de_digtable->rx_gain_min =
				    (de_digtable->forbidden_igi + 1);
			de_digtable->recover_cnt = 3600;	/* 3600=2hr */
		}
	} else {
		/* Recovery mechanism for IGI lower bound */
		if (de_digtable->recover_cnt != 0) {
			de_digtable->recover_cnt--;
		} else {
			if (de_digtable->large_fa_hit == 0) {
				if ((de_digtable->forbidden_igi - 1) <
				    DM_DIG_FA_LOWER) {
					de_digtable->forbidden_igi =
							 DM_DIG_FA_LOWER;
					de_digtable->rx_gain_min =
							 DM_DIG_FA_LOWER;

				} else {
					de_digtable->forbidden_igi--;
					de_digtable->rx_gain_min =
					    (de_digtable->forbidden_igi + 1);
				}
			} else if (de_digtable->large_fa_hit == 3) {
				de_digtable->large_fa_hit = 0;
			}
		}
	}
	RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD,
		 "dm_DIG() After: large_fa_hit=%d, forbidden_igi=%x\n",
		 de_digtable->large_fa_hit, de_digtable->forbidden_igi);
	RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD,
		 "dm_DIG() After: recover_cnt=%d, rx_gain_min=%x\n",
		 de_digtable->recover_cnt, de_digtable->rx_gain_min);

	if (value_igi > DM_DIG_MAX)
		value_igi = DM_DIG_MAX;
	else if (value_igi < de_digtable->rx_gain_min)
		value_igi = de_digtable->rx_gain_min;
	de_digtable->cur_igvalue = value_igi;
	rtl92d_dm_write_dig(hw);
	if (rtlpriv->rtlhal.current_bandtype != BAND_ON_5G)
		rtl92d_dm_cck_packet_detection_thresh(hw);
	RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD, "<<==\n");
}