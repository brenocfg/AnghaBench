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
struct btdm_8723 {int all_off; int agc_table_en; int adc_back_off_on; int b2_ant_hid_en; int low_penalty_rate_adaptive; int rf_rx_lpf_shrink; int reject_aggre_pkt; int tdma_on; int fw_dac_swing_lvl; int tra_tdma_on; int ignore_wlan_act; int ps_tdma_on; int* ps_tdma_byte; int pta_on; int val_0x6c0; int val_0x6c8; int val_0x6cc; int sw_dac_swing_on; int sw_dac_swing_lvl; int wlan_act_hi; int wlan_act_lo; int bt_retry_index; int dec_bt_pwr; void* tra_tdma_nav; void* tra_tdma_ant; int /*<<< orphan*/  tdma_dac_swing; void* tdma_nav; void* tdma_ant; } ;

/* Variables and functions */
 void* TDMA_2ANT ; 
 int /*<<< orphan*/  TDMA_DAC_SWING_OFF ; 
 void* TDMA_NAV_OFF ; 

__attribute__((used)) static void rtl8723e_dm_bt_btdm_structure_reload(struct ieee80211_hw *hw,
						 struct btdm_8723 *btdm)
{
	btdm->all_off = false;
	btdm->agc_table_en = false;
	btdm->adc_back_off_on = false;
	btdm->b2_ant_hid_en = false;
	btdm->low_penalty_rate_adaptive = false;
	btdm->rf_rx_lpf_shrink = false;
	btdm->reject_aggre_pkt = false;

	btdm->tdma_on = false;
	btdm->tdma_ant = TDMA_2ANT;
	btdm->tdma_nav = TDMA_NAV_OFF;
	btdm->tdma_dac_swing = TDMA_DAC_SWING_OFF;
	btdm->fw_dac_swing_lvl = 0x20;

	btdm->tra_tdma_on = false;
	btdm->tra_tdma_ant = TDMA_2ANT;
	btdm->tra_tdma_nav = TDMA_NAV_OFF;
	btdm->ignore_wlan_act = false;

	btdm->ps_tdma_on = false;
	btdm->ps_tdma_byte[0] = 0x0;
	btdm->ps_tdma_byte[1] = 0x0;
	btdm->ps_tdma_byte[2] = 0x0;
	btdm->ps_tdma_byte[3] = 0x8;
	btdm->ps_tdma_byte[4] = 0x0;

	btdm->pta_on = true;
	btdm->val_0x6c0 = 0x5a5aaaaa;
	btdm->val_0x6c8 = 0xcc;
	btdm->val_0x6cc = 0x3;

	btdm->sw_dac_swing_on = false;
	btdm->sw_dac_swing_lvl = 0xc0;
	btdm->wlan_act_hi = 0x20;
	btdm->wlan_act_lo = 0x10;
	btdm->bt_retry_index = 2;

	btdm->dec_bt_pwr = false;
}