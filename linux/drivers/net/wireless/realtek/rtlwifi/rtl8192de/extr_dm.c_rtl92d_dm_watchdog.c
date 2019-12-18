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
struct rtl_ps_ctl {scalar_t__ rfpwr_state; int /*<<< orphan*/  rfchange_inprogress; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ ERFON ; 
 int /*<<< orphan*/  rtl92d_dm_check_edca_turbo (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl92d_dm_dig (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl92d_dm_dynamic_txpower (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl92d_dm_false_alarm_counter_statistics (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl92d_dm_find_minimum_rssi (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl92d_dm_pwdb_monitor (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_priv (struct ieee80211_hw*) ; 
 struct rtl_ps_ctl* rtl_psc (int /*<<< orphan*/ ) ; 

void rtl92d_dm_watchdog(struct ieee80211_hw *hw)
{
	struct rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	bool fw_current_inpsmode = false;
	bool fwps_awake = true;

	/* 1. RF is OFF. (No need to do DM.)
	 * 2. Fw is under power saving mode for FwLPS.
	 *    (Prevent from SW/FW I/O racing.)
	 * 3. IPS workitem is scheduled. (Prevent from IPS sequence
	 *    to be swapped with DM.
	 * 4. RFChangeInProgress is TRUE.
	 *    (Prevent from broken by IPS/HW/SW Rf off.) */

	if ((ppsc->rfpwr_state == ERFON) && ((!fw_current_inpsmode) &&
	    fwps_awake) && (!ppsc->rfchange_inprogress)) {
		rtl92d_dm_pwdb_monitor(hw);
		rtl92d_dm_false_alarm_counter_statistics(hw);
		rtl92d_dm_find_minimum_rssi(hw);
		rtl92d_dm_dig(hw);
		/* rtl92d_dm_dynamic_bb_powersaving(hw); */
		rtl92d_dm_dynamic_txpower(hw);
		/* rtl92d_dm_check_txpower_tracking_thermal_meter(hw); */
		/* rtl92d_dm_refresh_rate_adaptive_mask(hw); */
		/* rtl92d_dm_interrupt_migration(hw); */
		rtl92d_dm_check_edca_turbo(hw);
	}
}