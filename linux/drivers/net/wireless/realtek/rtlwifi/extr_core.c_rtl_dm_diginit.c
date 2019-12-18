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
struct TYPE_2__ {int dm_initialgain_enable; } ;
struct dig_t {int dig_enable_flag; int pre_cck_cca_thres; int cur_cck_cca_thres; int dig_min_0; int dig_min_1; int media_connect_0; int media_connect_1; int bt30_cur_igi; scalar_t__ cur_cck_fa_state; scalar_t__ pre_cck_fa_state; int /*<<< orphan*/  cur_cck_pd_state; int /*<<< orphan*/  pre_cck_pd_state; scalar_t__ recover_cnt; scalar_t__ large_fa_hit; void* forbidden_igi; int /*<<< orphan*/  back_range_min; int /*<<< orphan*/  back_range_max; int /*<<< orphan*/  back_val; void* rx_gain_min; int /*<<< orphan*/  rx_gain_max; int /*<<< orphan*/  fa_highthresh; int /*<<< orphan*/  fa_lowthresh; int /*<<< orphan*/  rssi_highthresh; int /*<<< orphan*/  rssi_lowthresh; int /*<<< orphan*/  curmultista_cstate; void* presta_cstate; void* cur_sta_cstate; scalar_t__ pre_igvalue; int /*<<< orphan*/  cur_igvalue; int /*<<< orphan*/  dig_ext_port_stage; } ;
struct rtl_priv {TYPE_1__ dm; struct dig_t dm_digtable; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCK_PD_STAGE_LOWRSSI ; 
 int /*<<< orphan*/  CCK_PD_STAGE_MAX ; 
 int /*<<< orphan*/  DIG_EXT_PORT_STAGE_MAX ; 
 int /*<<< orphan*/  DIG_MULTISTA_DISCONNECT ; 
 void* DIG_STA_DISCONNECT ; 
 int /*<<< orphan*/  DM_DIG_BACKOFF_DEFAULT ; 
 int /*<<< orphan*/  DM_DIG_BACKOFF_MAX ; 
 int /*<<< orphan*/  DM_DIG_BACKOFF_MIN ; 
 int /*<<< orphan*/  DM_DIG_MAX ; 
 void* DM_DIG_MIN ; 
 int /*<<< orphan*/  DM_DIG_THRESH_HIGH ; 
 int /*<<< orphan*/  DM_DIG_THRESH_LOW ; 
 int /*<<< orphan*/  DM_FALSEALARM_THRESH_HIGH ; 
 int /*<<< orphan*/  DM_FALSEALARM_THRESH_LOW ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

void rtl_dm_diginit(struct ieee80211_hw *hw, u32 cur_igvalue)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct dig_t *dm_digtable = &rtlpriv->dm_digtable;

	dm_digtable->dig_enable_flag = true;
	dm_digtable->dig_ext_port_stage = DIG_EXT_PORT_STAGE_MAX;
	dm_digtable->cur_igvalue = cur_igvalue;
	dm_digtable->pre_igvalue = 0;
	dm_digtable->cur_sta_cstate = DIG_STA_DISCONNECT;
	dm_digtable->presta_cstate = DIG_STA_DISCONNECT;
	dm_digtable->curmultista_cstate = DIG_MULTISTA_DISCONNECT;
	dm_digtable->rssi_lowthresh = DM_DIG_THRESH_LOW;
	dm_digtable->rssi_highthresh = DM_DIG_THRESH_HIGH;
	dm_digtable->fa_lowthresh = DM_FALSEALARM_THRESH_LOW;
	dm_digtable->fa_highthresh = DM_FALSEALARM_THRESH_HIGH;
	dm_digtable->rx_gain_max = DM_DIG_MAX;
	dm_digtable->rx_gain_min = DM_DIG_MIN;
	dm_digtable->back_val = DM_DIG_BACKOFF_DEFAULT;
	dm_digtable->back_range_max = DM_DIG_BACKOFF_MAX;
	dm_digtable->back_range_min = DM_DIG_BACKOFF_MIN;
	dm_digtable->pre_cck_cca_thres = 0xff;
	dm_digtable->cur_cck_cca_thres = 0x83;
	dm_digtable->forbidden_igi = DM_DIG_MIN;
	dm_digtable->large_fa_hit = 0;
	dm_digtable->recover_cnt = 0;
	dm_digtable->dig_min_0 = 0x25;
	dm_digtable->dig_min_1 = 0x25;
	dm_digtable->media_connect_0 = false;
	dm_digtable->media_connect_1 = false;
	rtlpriv->dm.dm_initialgain_enable = true;
	dm_digtable->bt30_cur_igi = 0x32;
	dm_digtable->pre_cck_pd_state = CCK_PD_STAGE_MAX;
	dm_digtable->cur_cck_pd_state = CCK_PD_STAGE_LOWRSSI;
	dm_digtable->pre_cck_fa_state = 0;
	dm_digtable->cur_cck_fa_state = 0;
}