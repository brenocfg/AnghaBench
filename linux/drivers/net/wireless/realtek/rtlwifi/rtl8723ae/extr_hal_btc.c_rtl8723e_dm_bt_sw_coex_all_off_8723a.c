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
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_AGCTABLE_OFF ; 
 int /*<<< orphan*/  BT_BB_BACKOFF_OFF ; 
 int /*<<< orphan*/  BT_RF_RX_LPF_CORNER_RESUME ; 
 int /*<<< orphan*/  BT_TX_RATE_ADAPTIVE_NORMAL ; 
 int /*<<< orphan*/  dm_bt_set_sw_penalty_tx_rate_adapt (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8723e_dm_bt_agc_table (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8723e_dm_bt_bb_back_off_level (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8723e_dm_bt_reject_ap_aggregated_packet (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  rtl8723e_dm_bt_set_sw_full_time_dac_swing (struct ieee80211_hw*,int,int) ; 
 int /*<<< orphan*/  rtl8723e_dm_bt_set_sw_rf_rx_lpf_corner (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 

void rtl8723e_dm_bt_sw_coex_all_off_8723a(struct ieee80211_hw *hw)
{
	rtl8723e_dm_bt_agc_table(hw, BT_AGCTABLE_OFF);
	rtl8723e_dm_bt_bb_back_off_level(hw, BT_BB_BACKOFF_OFF);
	rtl8723e_dm_bt_reject_ap_aggregated_packet(hw, false);

	dm_bt_set_sw_penalty_tx_rate_adapt(hw, BT_TX_RATE_ADAPTIVE_NORMAL);
	rtl8723e_dm_bt_set_sw_rf_rx_lpf_corner(hw, BT_RF_RX_LPF_CORNER_RESUME);
	rtl8723e_dm_bt_set_sw_full_time_dac_swing(hw, false, 0xc0);
}