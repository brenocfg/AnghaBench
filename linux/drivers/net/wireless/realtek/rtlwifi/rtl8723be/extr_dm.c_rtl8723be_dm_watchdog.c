#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_9__ {scalar_t__ p2p_ps_mode; } ;
struct rtl_ps_ctl {scalar_t__ rfpwr_state; int /*<<< orphan*/  rfchange_inprogress; TYPE_3__ p2p_ps_info; } ;
struct TYPE_11__ {scalar_t__ num_qry_beacon_pkt; } ;
struct TYPE_12__ {TYPE_5__ dbginfo; } ;
struct TYPE_10__ {int /*<<< orphan*/  rf_ps_lock; } ;
struct rtl_priv {TYPE_6__ dm; TYPE_4__ locks; TYPE_2__* cfg; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_8__ {TYPE_1__* ops; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* get_hw_reg ) (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ ERFON ; 
 int /*<<< orphan*/  HW_VAR_FWLPS_RF_ON ; 
 int /*<<< orphan*/  HW_VAR_FW_PSMODE_STATUS ; 
 int /*<<< orphan*/  rtl8723be_dm_cck_packet_detection_thresh (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8723be_dm_check_edca_turbo (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8723be_dm_check_rssi_monitor (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8723be_dm_check_txpower_tracking (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8723be_dm_common_info_self_update (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8723be_dm_dig (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8723be_dm_dynamic_atc_switch (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8723be_dm_dynamic_edcca (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8723be_dm_dynamic_txpower (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8723be_dm_false_alarm_counter_statistics (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8723be_dm_refresh_rate_adaptive_mask (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 struct rtl_ps_ctl* rtl_psc (struct rtl_priv*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void rtl8723be_dm_watchdog(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	bool fw_current_inpsmode = false;
	bool fw_ps_awake = true;

	rtlpriv->cfg->ops->get_hw_reg(hw, HW_VAR_FW_PSMODE_STATUS,
				      (u8 *)(&fw_current_inpsmode));

	rtlpriv->cfg->ops->get_hw_reg(hw, HW_VAR_FWLPS_RF_ON,
				      (u8 *)(&fw_ps_awake));

	if (ppsc->p2p_ps_info.p2p_ps_mode)
		fw_ps_awake = false;

	spin_lock(&rtlpriv->locks.rf_ps_lock);
	if ((ppsc->rfpwr_state == ERFON) &&
		((!fw_current_inpsmode) && fw_ps_awake) &&
		(!ppsc->rfchange_inprogress)) {
		rtl8723be_dm_common_info_self_update(hw);
		rtl8723be_dm_false_alarm_counter_statistics(hw);
		rtl8723be_dm_check_rssi_monitor(hw);
		rtl8723be_dm_dig(hw);
		rtl8723be_dm_dynamic_edcca(hw);
		rtl8723be_dm_cck_packet_detection_thresh(hw);
		rtl8723be_dm_refresh_rate_adaptive_mask(hw);
		rtl8723be_dm_check_edca_turbo(hw);
		rtl8723be_dm_dynamic_atc_switch(hw);
		rtl8723be_dm_check_txpower_tracking(hw);
		rtl8723be_dm_dynamic_txpower(hw);
	}
	spin_unlock(&rtlpriv->locks.rf_ps_lock);
	rtlpriv->dm.dbginfo.num_qry_beacon_pkt = 0;
}