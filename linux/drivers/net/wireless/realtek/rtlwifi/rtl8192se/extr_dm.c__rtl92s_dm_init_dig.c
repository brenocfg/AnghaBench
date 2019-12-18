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
struct TYPE_2__ {scalar_t__ dm_type; } ;
struct dig_t {int dig_enable_flag; int backoff_enable_flag; int rssi_val; int /*<<< orphan*/  backoffval_range_min; void* backoffval_range_max; int /*<<< orphan*/  rx_gain_min; int /*<<< orphan*/  rx_gain_max; void* back_val; int /*<<< orphan*/  rssi_highpower_highthresh; int /*<<< orphan*/  rssi_highpower_lowthresh; int /*<<< orphan*/  fa_highthresh; int /*<<< orphan*/  fa_lowthresh; int /*<<< orphan*/  rssi_highthresh; int /*<<< orphan*/  rssi_lowthresh; void* pre_ap_cstate; void* cur_ap_cstate; void* pre_sta_cstate; void* cur_sta_cstate; void* dig_highpwrstate; void* dig_state; scalar_t__ dig_slgorithm_switch; int /*<<< orphan*/  dig_dbgmode; int /*<<< orphan*/  dig_ext_port_stage; int /*<<< orphan*/  dig_twoport_algorithm; int /*<<< orphan*/  dig_algorithm; } ;
struct rtl_priv {TYPE_1__ dm; struct dig_t dm_digtable; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIG_ALGO_BEFORE_CONNECT_BY_RSSI_AND_ALARM ; 
 int /*<<< orphan*/  DIG_ALGO_BY_TOW_PORT ; 
 void* DIG_AP_DISCONNECT ; 
 int /*<<< orphan*/  DIG_EXT_PORT_STAGE_MAX ; 
 void* DIG_STA_DISCONNECT ; 
 int /*<<< orphan*/  DIG_TWO_PORT_ALGO_RSSI ; 
 int /*<<< orphan*/  DM_DBG_OFF ; 
 void* DM_DIG_BACKOFF_MAX ; 
 int /*<<< orphan*/  DM_DIG_BACKOFF_MIN ; 
 int /*<<< orphan*/  DM_DIG_HIGH_PWR_THRESH_HIGH ; 
 int /*<<< orphan*/  DM_DIG_HIGH_PWR_THRESH_LOW ; 
 int /*<<< orphan*/  DM_DIG_MAX ; 
 int /*<<< orphan*/  DM_DIG_MIN ; 
 int /*<<< orphan*/  DM_DIG_THRESH_HIGH ; 
 int /*<<< orphan*/  DM_DIG_THRESH_LOW ; 
 int /*<<< orphan*/  DM_FALSEALARM_THRESH_HIGH ; 
 int /*<<< orphan*/  DM_FALSEALARM_THRESH_LOW ; 
 void* DM_STA_DIG_MAX ; 
 scalar_t__ DM_TYPE_BYDRIVER ; 
 int hal_get_firmwareversion (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl92s_dm_init_dig(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct dig_t *digtable = &rtlpriv->dm_digtable;

	/* Disable DIG scheme now.*/
	digtable->dig_enable_flag = true;
	digtable->backoff_enable_flag = true;

	if ((rtlpriv->dm.dm_type == DM_TYPE_BYDRIVER) &&
	    (hal_get_firmwareversion(rtlpriv) >= 0x3c))
		digtable->dig_algorithm = DIG_ALGO_BY_TOW_PORT;
	else
		digtable->dig_algorithm =
			 DIG_ALGO_BEFORE_CONNECT_BY_RSSI_AND_ALARM;

	digtable->dig_twoport_algorithm = DIG_TWO_PORT_ALGO_RSSI;
	digtable->dig_ext_port_stage = DIG_EXT_PORT_STAGE_MAX;
	/* off=by real rssi value, on=by digtable->rssi_val for new dig */
	digtable->dig_dbgmode = DM_DBG_OFF;
	digtable->dig_slgorithm_switch = 0;

	/* 2007/10/04 MH Define init gain threshol. */
	digtable->dig_state = DM_STA_DIG_MAX;
	digtable->dig_highpwrstate = DM_STA_DIG_MAX;

	digtable->cur_sta_cstate = DIG_STA_DISCONNECT;
	digtable->pre_sta_cstate = DIG_STA_DISCONNECT;
	digtable->cur_ap_cstate = DIG_AP_DISCONNECT;
	digtable->pre_ap_cstate = DIG_AP_DISCONNECT;

	digtable->rssi_lowthresh = DM_DIG_THRESH_LOW;
	digtable->rssi_highthresh = DM_DIG_THRESH_HIGH;

	digtable->fa_lowthresh = DM_FALSEALARM_THRESH_LOW;
	digtable->fa_highthresh = DM_FALSEALARM_THRESH_HIGH;

	digtable->rssi_highpower_lowthresh = DM_DIG_HIGH_PWR_THRESH_LOW;
	digtable->rssi_highpower_highthresh = DM_DIG_HIGH_PWR_THRESH_HIGH;

	/* for dig debug rssi value */
	digtable->rssi_val = 50;
	digtable->back_val = DM_DIG_BACKOFF_MAX;
	digtable->rx_gain_max = DM_DIG_MAX;

	digtable->rx_gain_min = DM_DIG_MIN;

	digtable->backoffval_range_max = DM_DIG_BACKOFF_MAX;
	digtable->backoffval_range_min = DM_DIG_BACKOFF_MIN;
}