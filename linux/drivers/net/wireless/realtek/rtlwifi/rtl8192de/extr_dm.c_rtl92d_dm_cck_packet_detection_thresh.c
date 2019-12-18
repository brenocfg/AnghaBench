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
struct TYPE_2__ {int /*<<< orphan*/  version; } ;
struct dig_t {scalar_t__ cursta_cstate; scalar_t__ pre_cck_pd_state; int min_undec_pwdb_for_dm; scalar_t__ cur_cck_pd_state; } ;
struct rtl_priv {TYPE_1__ rtlhal; struct dig_t dm_digtable; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 void* CCK_PD_STAGE_HIGHRSSI ; 
 scalar_t__ CCK_PD_STAGE_LOWRSSI ; 
 int /*<<< orphan*/  COMP_DIG ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 scalar_t__ DIG_STA_CONNECT ; 
 char* IS_92D_SINGLEPHY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MASKBYTE2 ; 
 int /*<<< orphan*/  RCCK0_CCA ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  rtl92d_acquire_cckandrw_pagea_ctl (struct ieee80211_hw*,unsigned long*) ; 
 int /*<<< orphan*/  rtl92d_release_cckandrw_pagea_ctl (struct ieee80211_hw*,unsigned long*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtl92d_dm_cck_packet_detection_thresh(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct dig_t *de_digtable = &rtlpriv->dm_digtable;
	unsigned long flag = 0;

	if (de_digtable->cursta_cstate == DIG_STA_CONNECT) {
		if (de_digtable->pre_cck_pd_state == CCK_PD_STAGE_LOWRSSI) {
			if (de_digtable->min_undec_pwdb_for_dm <= 25)
				de_digtable->cur_cck_pd_state =
							 CCK_PD_STAGE_LOWRSSI;
			else
				de_digtable->cur_cck_pd_state =
							 CCK_PD_STAGE_HIGHRSSI;
		} else {
			if (de_digtable->min_undec_pwdb_for_dm <= 20)
				de_digtable->cur_cck_pd_state =
							 CCK_PD_STAGE_LOWRSSI;
			else
				de_digtable->cur_cck_pd_state =
							 CCK_PD_STAGE_HIGHRSSI;
		}
	} else {
		de_digtable->cur_cck_pd_state = CCK_PD_STAGE_LOWRSSI;
	}
	if (de_digtable->pre_cck_pd_state != de_digtable->cur_cck_pd_state) {
		if (de_digtable->cur_cck_pd_state == CCK_PD_STAGE_LOWRSSI) {
			rtl92d_acquire_cckandrw_pagea_ctl(hw, &flag);
			rtl_set_bbreg(hw, RCCK0_CCA, MASKBYTE2, 0x83);
			rtl92d_release_cckandrw_pagea_ctl(hw, &flag);
		} else {
			rtl92d_acquire_cckandrw_pagea_ctl(hw, &flag);
			rtl_set_bbreg(hw, RCCK0_CCA, MASKBYTE2, 0xcd);
			rtl92d_release_cckandrw_pagea_ctl(hw, &flag);
		}
		de_digtable->pre_cck_pd_state = de_digtable->cur_cck_pd_state;
	}
	RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD, "CurSTAConnectState=%s\n",
		 de_digtable->cursta_cstate == DIG_STA_CONNECT ?
		 "DIG_STA_CONNECT " : "DIG_STA_DISCONNECT");
	RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD, "CCKPDStage=%s\n",
		 de_digtable->cur_cck_pd_state == CCK_PD_STAGE_LOWRSSI ?
		 "Low RSSI " : "High RSSI ");
	RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD, "is92d single phy =%x\n",
		 IS_92D_SINGLEPHY(rtlpriv->rtlhal.version));

}