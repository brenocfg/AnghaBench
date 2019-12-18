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
typedef  void* u8 ;
typedef  void* u16 ;
struct TYPE_2__ {int SsidLength; int /*<<< orphan*/  Ssid; } ;
struct registry_priv {int accept_addba_req; int RegPowerBase; int TxBBSwing_2G; int TxBBSwing_5G; int bEn_RFE; int RFE_Type; void* hiq_filter; void* qos_opt_enable; void* RegDecryptCustomFile; void* load_phy_file; void* RegEnableTxPowerByRate; void* RegEnableTxPowerLimit; void* notch_filter; int /*<<< orphan*/  ifname; void* enable80211d; void* max_roaming_times; void* hw_wps_pbc; void* antdiv_type; void* antdiv_cfg; scalar_t__ ant_num; void* bt_ampdu; void* bt_sco; void* bt_iso; void* btcoex; void* channel_plan; void* wifi_spec; void* low_power; void* rf_config; void* lowrate_two_xmit; void* beamform_cap; void* stbc_cap; void* ldpc_cap; void* short_gi; void* ampdu_amsdu; void* rx_stbc; void* ampdu_enable; void* bw_mode; void* ht_enable; void* uapsd_acvo_en; void* uapsd_acvi_en; void* uapsd_acbe_en; void* uapsd_acbk_en; void* uapsd_max_sp; void* uapsd_enable; void* wmm_enable; void* usb_rxagg_mode; void* acm_method; void* software_decrypt; void* software_encrypt; void* ack_policy; void* busy_thresh; void* short_retry_lmt; void* long_retry_lmt; void* radio_enable; void* ips_mode; void* power_mgnt; void* check_fw_ps; void* smart_ps; void* soft_ap; void* adhoc_tx_pwr; void* scan_mode; void* preamble; void* frag_thresh; void* rts_thresh; void* vcs_type; void* vrtl_carrier_sense; void* wireless_mode; void* channel; TYPE_1__ ssid; void* network_mode; void* lbkmode; void* rfintfs; void* chip_version; } ;
struct adapter {struct registry_priv registrypriv; } ;
typedef  scalar_t__ s8 ;
typedef  int /*<<< orphan*/  _nic_hdl ;

/* Variables and functions */
 char* ifname ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ rtw_80211d ; 
 scalar_t__ rtw_ack_policy ; 
 scalar_t__ rtw_acm_method ; 
 scalar_t__ rtw_adhoc_tx_pwr ; 
 scalar_t__ rtw_ampdu_amsdu ; 
 scalar_t__ rtw_ampdu_enable ; 
 scalar_t__ rtw_ant_num ; 
 scalar_t__ rtw_antdiv_cfg ; 
 scalar_t__ rtw_antdiv_type ; 
 scalar_t__ rtw_beamform_cap ; 
 scalar_t__ rtw_bt_ampdu ; 
 scalar_t__ rtw_bt_iso ; 
 scalar_t__ rtw_bt_sco ; 
 scalar_t__ rtw_btcoex_enable ; 
 scalar_t__ rtw_busy_thresh ; 
 scalar_t__ rtw_bw_mode ; 
 scalar_t__ rtw_channel ; 
 scalar_t__ rtw_channel_plan ; 
 scalar_t__ rtw_check_fw_ps ; 
 scalar_t__ rtw_chip_version ; 
 scalar_t__ rtw_decrypt_phy_file ; 
 scalar_t__ rtw_frag_thresh ; 
 scalar_t__ rtw_hiq_filter ; 
 scalar_t__ rtw_ht_enable ; 
 scalar_t__ rtw_hw_wps_pbc ; 
 scalar_t__ rtw_ips_mode ; 
 scalar_t__ rtw_lbkmode ; 
 scalar_t__ rtw_ldpc_cap ; 
 scalar_t__ rtw_load_phy_file ; 
 scalar_t__ rtw_long_retry_lmt ; 
 scalar_t__ rtw_low_power ; 
 scalar_t__ rtw_lowrate_two_xmit ; 
 scalar_t__ rtw_max_roaming_times ; 
 scalar_t__ rtw_network_mode ; 
 scalar_t__ rtw_notch_filter ; 
 scalar_t__ rtw_power_mgnt ; 
 scalar_t__ rtw_preamble ; 
 scalar_t__ rtw_qos_opt_enable ; 
 scalar_t__ rtw_radio_enable ; 
 scalar_t__ rtw_rf_config ; 
 scalar_t__ rtw_rfintfs ; 
 scalar_t__ rtw_rts_thresh ; 
 scalar_t__ rtw_rx_stbc ; 
 scalar_t__ rtw_scan_mode ; 
 scalar_t__ rtw_short_gi ; 
 scalar_t__ rtw_short_retry_lmt ; 
 scalar_t__ rtw_smart_ps ; 
 scalar_t__ rtw_soft_ap ; 
 scalar_t__ rtw_software_decrypt ; 
 scalar_t__ rtw_software_encrypt ; 
 scalar_t__ rtw_stbc_cap ; 
 scalar_t__ rtw_tx_pwr_by_rate ; 
 scalar_t__ rtw_tx_pwr_lmt_enable ; 
 scalar_t__ rtw_uapsd_acbe_en ; 
 scalar_t__ rtw_uapsd_acbk_en ; 
 scalar_t__ rtw_uapsd_acvi_en ; 
 scalar_t__ rtw_uapsd_acvo_en ; 
 scalar_t__ rtw_uapsd_enable ; 
 scalar_t__ rtw_uapsd_max_sp ; 
 scalar_t__ rtw_usb_rxagg_mode ; 
 scalar_t__ rtw_vcs_type ; 
 scalar_t__ rtw_vrtl_carrier_sense ; 
 scalar_t__ rtw_wifi_spec ; 
 scalar_t__ rtw_wireless_mode ; 
 scalar_t__ rtw_wmm_enable ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 

__attribute__((used)) static void loadparam(struct adapter *padapter, _nic_hdl pnetdev)
{
	struct registry_priv  *registry_par = &padapter->registrypriv;

	registry_par->chip_version = (u8)rtw_chip_version;
	registry_par->rfintfs = (u8)rtw_rfintfs;
	registry_par->lbkmode = (u8)rtw_lbkmode;
	/* registry_par->hci = (u8)hci; */
	registry_par->network_mode  = (u8)rtw_network_mode;

	memcpy(registry_par->ssid.Ssid, "ANY", 3);
	registry_par->ssid.SsidLength = 3;

	registry_par->channel = (u8)rtw_channel;
	registry_par->wireless_mode = (u8)rtw_wireless_mode;

	registry_par->vrtl_carrier_sense = (u8)rtw_vrtl_carrier_sense ;
	registry_par->vcs_type = (u8)rtw_vcs_type;
	registry_par->rts_thresh = (u16)rtw_rts_thresh;
	registry_par->frag_thresh = (u16)rtw_frag_thresh;
	registry_par->preamble = (u8)rtw_preamble;
	registry_par->scan_mode = (u8)rtw_scan_mode;
	registry_par->adhoc_tx_pwr = (u8)rtw_adhoc_tx_pwr;
	registry_par->soft_ap =  (u8)rtw_soft_ap;
	registry_par->smart_ps =  (u8)rtw_smart_ps;
	registry_par->check_fw_ps = (u8)rtw_check_fw_ps;
	registry_par->power_mgnt = (u8)rtw_power_mgnt;
	registry_par->ips_mode = (u8)rtw_ips_mode;
	registry_par->radio_enable = (u8)rtw_radio_enable;
	registry_par->long_retry_lmt = (u8)rtw_long_retry_lmt;
	registry_par->short_retry_lmt = (u8)rtw_short_retry_lmt;
	registry_par->busy_thresh = (u16)rtw_busy_thresh;
	/* registry_par->qos_enable = (u8)rtw_qos_enable; */
	registry_par->ack_policy = (u8)rtw_ack_policy;
	registry_par->software_encrypt = (u8)rtw_software_encrypt;
	registry_par->software_decrypt = (u8)rtw_software_decrypt;

	registry_par->acm_method = (u8)rtw_acm_method;
	registry_par->usb_rxagg_mode = (u8)rtw_usb_rxagg_mode;

	 /* UAPSD */
	registry_par->wmm_enable = (u8)rtw_wmm_enable;
	registry_par->uapsd_enable = (u8)rtw_uapsd_enable;
	registry_par->uapsd_max_sp = (u8)rtw_uapsd_max_sp;
	registry_par->uapsd_acbk_en = (u8)rtw_uapsd_acbk_en;
	registry_par->uapsd_acbe_en = (u8)rtw_uapsd_acbe_en;
	registry_par->uapsd_acvi_en = (u8)rtw_uapsd_acvi_en;
	registry_par->uapsd_acvo_en = (u8)rtw_uapsd_acvo_en;

	registry_par->ht_enable = (u8)rtw_ht_enable;
	registry_par->bw_mode = (u8)rtw_bw_mode;
	registry_par->ampdu_enable = (u8)rtw_ampdu_enable;
	registry_par->rx_stbc = (u8)rtw_rx_stbc;
	registry_par->ampdu_amsdu = (u8)rtw_ampdu_amsdu;
	registry_par->short_gi = (u8)rtw_short_gi;
	registry_par->ldpc_cap = (u8)rtw_ldpc_cap;
	registry_par->stbc_cap = (u8)rtw_stbc_cap;
	registry_par->beamform_cap = (u8)rtw_beamform_cap;

	registry_par->lowrate_two_xmit = (u8)rtw_lowrate_two_xmit;
	registry_par->rf_config = (u8)rtw_rf_config;
	registry_par->low_power = (u8)rtw_low_power;


	registry_par->wifi_spec = (u8)rtw_wifi_spec;

	registry_par->channel_plan = (u8)rtw_channel_plan;

	registry_par->btcoex = (u8)rtw_btcoex_enable;
	registry_par->bt_iso = (u8)rtw_bt_iso;
	registry_par->bt_sco = (u8)rtw_bt_sco;
	registry_par->bt_ampdu = (u8)rtw_bt_ampdu;
	registry_par->ant_num = (s8)rtw_ant_num;

	registry_par->accept_addba_req = true;

	registry_par->antdiv_cfg = (u8)rtw_antdiv_cfg;
	registry_par->antdiv_type = (u8)rtw_antdiv_type;

	registry_par->hw_wps_pbc = (u8)rtw_hw_wps_pbc;

	registry_par->max_roaming_times = (u8)rtw_max_roaming_times;

	registry_par->enable80211d = (u8)rtw_80211d;

	snprintf(registry_par->ifname, 16, "%s", ifname);

	registry_par->notch_filter = (u8)rtw_notch_filter;

	registry_par->RegEnableTxPowerLimit = (u8)rtw_tx_pwr_lmt_enable;
	registry_par->RegEnableTxPowerByRate = (u8)rtw_tx_pwr_by_rate;

	registry_par->RegPowerBase = 14;
	registry_par->TxBBSwing_2G = 0xFF;
	registry_par->TxBBSwing_5G = 0xFF;
	registry_par->bEn_RFE = 1;
	registry_par->RFE_Type = 64;

	registry_par->load_phy_file = (u8)rtw_load_phy_file;
	registry_par->RegDecryptCustomFile = (u8)rtw_decrypt_phy_file;
	registry_par->qos_opt_enable = (u8)rtw_qos_opt_enable;

	registry_par->hiq_filter = (u8)rtw_hiq_filter;
}