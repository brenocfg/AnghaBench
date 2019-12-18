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
struct TYPE_2__ {int cnt_cck_fail; } ;
struct dig_t {scalar_t__ cursta_cstate; int rssi_val_min; scalar_t__ pre_cck_pd_state; scalar_t__ cur_cck_pd_state; scalar_t__ cur_cck_fa_state; scalar_t__ pre_cck_fa_state; } ;
struct rtl_priv {TYPE_1__ falsealm_cnt; struct dig_t dm_digtable; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ CCK_FA_STAGE_HIGH ; 
 scalar_t__ CCK_FA_STAGE_LOW ; 
 void* CCK_PD_STAGE_HIGHRSSI ; 
 scalar_t__ CCK_PD_STAGE_LOWRSSI ; 
 scalar_t__ CCK_PD_STAGE_MAX ; 
 int /*<<< orphan*/  COMP_DIG ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 scalar_t__ DIG_STA_CONNECT ; 
 int /*<<< orphan*/  MASKBYTE1 ; 
 int /*<<< orphan*/  MASKBYTE2 ; 
 int /*<<< orphan*/  RCCK0_CCA ; 
 int /*<<< orphan*/  RCCK0_SYSTEM ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int rtl8723e_dm_initial_gain_min_pwdb (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtl8723e_dm_cck_packet_detection_thresh(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct dig_t *dm_digtable = &rtlpriv->dm_digtable;

	if (dm_digtable->cursta_cstate == DIG_STA_CONNECT) {
		dm_digtable->rssi_val_min = rtl8723e_dm_initial_gain_min_pwdb(hw);

		if (dm_digtable->pre_cck_pd_state == CCK_PD_STAGE_LOWRSSI) {
			if (dm_digtable->rssi_val_min <= 25)
				dm_digtable->cur_cck_pd_state =
				    CCK_PD_STAGE_LOWRSSI;
			else
				dm_digtable->cur_cck_pd_state =
				    CCK_PD_STAGE_HIGHRSSI;
		} else {
			if (dm_digtable->rssi_val_min <= 20)
				dm_digtable->cur_cck_pd_state =
				    CCK_PD_STAGE_LOWRSSI;
			else
				dm_digtable->cur_cck_pd_state =
				    CCK_PD_STAGE_HIGHRSSI;
		}
	} else {
		dm_digtable->cur_cck_pd_state = CCK_PD_STAGE_MAX;
	}

	if (dm_digtable->pre_cck_pd_state != dm_digtable->cur_cck_pd_state) {
		if (dm_digtable->cur_cck_pd_state == CCK_PD_STAGE_LOWRSSI) {
			if (rtlpriv->falsealm_cnt.cnt_cck_fail > 800)
				dm_digtable->cur_cck_fa_state =
				    CCK_FA_STAGE_HIGH;
			else
				dm_digtable->cur_cck_fa_state =
				    CCK_FA_STAGE_LOW;
			if (dm_digtable->pre_cck_fa_state !=
			    dm_digtable->cur_cck_fa_state) {
				if (dm_digtable->cur_cck_fa_state ==
				    CCK_FA_STAGE_LOW)
					rtl_set_bbreg(hw, RCCK0_CCA, MASKBYTE2,
						      0x83);
				else
					rtl_set_bbreg(hw, RCCK0_CCA, MASKBYTE2,
						      0xcd);

				dm_digtable->pre_cck_fa_state =
				    dm_digtable->cur_cck_fa_state;
			}

			rtl_set_bbreg(hw, RCCK0_SYSTEM, MASKBYTE1, 0x40);

		} else {
			rtl_set_bbreg(hw, RCCK0_CCA, MASKBYTE2, 0xcd);
			rtl_set_bbreg(hw, RCCK0_SYSTEM, MASKBYTE1, 0x47);
			dm_digtable->pre_cck_fa_state = 0;
			dm_digtable->cur_cck_fa_state = 0;

		}
		dm_digtable->pre_cck_pd_state = dm_digtable->cur_cck_pd_state;
	}

	RT_TRACE(rtlpriv, COMP_DIG, DBG_TRACE,
		 "CCKPDStage=%x\n", dm_digtable->cur_cck_pd_state);

}