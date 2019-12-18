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
struct dig_t {scalar_t__ cursta_cstate; int rssi_val_min; scalar_t__ pre_cck_pd_state; scalar_t__ cur_cck_pd_state; } ;
struct rtl_priv {struct dig_t dm_digtable; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 void* CCK_PD_STAGE_HIGHRSSI ; 
 scalar_t__ CCK_PD_STAGE_LOWRSSI ; 
 scalar_t__ CCK_PD_STAGE_MAX ; 
 scalar_t__ DIG_STA_CONNECT ; 
 int /*<<< orphan*/  MASKBYTE2 ; 
 int /*<<< orphan*/  RCCK0_CCA ; 
 int rtl92c_dm_initial_gain_min_pwdb (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtl92c_dm_cck_packet_detection_thresh(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct dig_t *dm_digtable = &rtlpriv->dm_digtable;

	if (dm_digtable->cursta_cstate == DIG_STA_CONNECT) {
		dm_digtable->rssi_val_min = rtl92c_dm_initial_gain_min_pwdb(hw);
		if (dm_digtable->rssi_val_min > 100)
			dm_digtable->rssi_val_min = 100;

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
		if ((dm_digtable->cur_cck_pd_state == CCK_PD_STAGE_LOWRSSI) ||
		    (dm_digtable->cur_cck_pd_state == CCK_PD_STAGE_MAX))
			rtl_set_bbreg(hw, RCCK0_CCA, MASKBYTE2, 0x83);
		else
			rtl_set_bbreg(hw, RCCK0_CCA, MASKBYTE2, 0xcd);

		dm_digtable->pre_cck_pd_state = dm_digtable->cur_cck_pd_state;
	}
}