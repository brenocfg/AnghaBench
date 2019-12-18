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
struct wmi_cmd_hdr {int /*<<< orphan*/  cmd_id; } ;
struct sk_buff {int /*<<< orphan*/  len; scalar_t__ data; } ;
struct ath10k {int dummy; } ;
typedef  enum wmi_tlv_event_id { ____Placeholder_wmi_tlv_event_id } wmi_tlv_event_id ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_WMI ; 
 int MS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WMI_CMD_HDR_CMD_ID ; 
#define  WMI_TLV_CHAN_INFO_EVENTID 170 
#define  WMI_TLV_DCS_INTERFERENCE_EVENTID 169 
#define  WMI_TLV_DEBUG_MESG_EVENTID 168 
#define  WMI_TLV_DEBUG_PRINT_EVENTID 167 
#define  WMI_TLV_DIAG_DATA_CONTAINER_EVENTID 166 
#define  WMI_TLV_DIAG_EVENTID 165 
#define  WMI_TLV_ECHO_EVENTID 164 
#define  WMI_TLV_GTK_OFFLOAD_STATUS_EVENTID 163 
#define  WMI_TLV_GTK_REKEY_FAIL_EVENTID 162 
#define  WMI_TLV_HOST_SWBA_EVENTID 161 
#define  WMI_TLV_MGMT_RX_EVENTID 160 
#define  WMI_TLV_MGMT_TX_BUNDLE_COMPLETION_EVENTID 159 
#define  WMI_TLV_MGMT_TX_COMPLETION_EVENTID 158 
#define  WMI_TLV_OFFLOAD_BCN_TX_STATUS_EVENTID 157 
#define  WMI_TLV_P2P_NOA_EVENTID 156 
#define  WMI_TLV_PDEV_FTM_INTG_EVENTID 155 
#define  WMI_TLV_PDEV_QVIT_EVENTID 154 
#define  WMI_TLV_PDEV_TEMPERATURE_EVENTID 153 
#define  WMI_TLV_PDEV_TPC_CONFIG_EVENTID 152 
#define  WMI_TLV_PEER_DELETE_RESP_EVENTID 151 
#define  WMI_TLV_PEER_STA_KICKOUT_EVENTID 150 
#define  WMI_TLV_PHYERR_EVENTID 149 
#define  WMI_TLV_PROFILE_MATCH 148 
#define  WMI_TLV_READY_EVENTID 147 
#define  WMI_TLV_ROAM_EVENTID 146 
#define  WMI_TLV_RTT_ERROR_REPORT_EVENTID 145 
#define  WMI_TLV_RTT_MEASUREMENT_REPORT_EVENTID 144 
#define  WMI_TLV_SCAN_EVENTID 143 
#define  WMI_TLV_SERVICE_AVAILABLE_EVENTID 142 
#define  WMI_TLV_SERVICE_READY_EVENTID 141 
#define  WMI_TLV_TBTTOFFSET_UPDATE_EVENTID 140 
#define  WMI_TLV_TDLS_PEER_EVENTID 139 
#define  WMI_TLV_TSF_MEASUREMENT_REPORT_EVENTID 138 
#define  WMI_TLV_TX_ADDBA_COMPLETE_EVENTID 137 
#define  WMI_TLV_TX_DELBA_COMPLETE_EVENTID 136 
#define  WMI_TLV_TX_PAUSE_EVENTID 135 
#define  WMI_TLV_UPDATE_STATS_EVENTID 134 
#define  WMI_TLV_VDEV_DELETE_RESP_EVENTID 133 
#define  WMI_TLV_VDEV_INSTALL_KEY_COMPLETE_EVENTID 132 
#define  WMI_TLV_VDEV_START_RESP_EVENTID 131 
#define  WMI_TLV_VDEV_STOPPED_EVENTID 130 
#define  WMI_TLV_WLAN_PROFILE_DATA_EVENTID 129 
#define  WMI_TLV_WOW_WAKEUP_HOST_EVENTID 128 
 int /*<<< orphan*/  __le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int) ; 
 int ath10k_tm_event_wmi (struct ath10k*,int,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_addba_complete (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_chan_info (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_dcs_interference (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_debug_mesg (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_debug_print (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_delba_complete (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_echo (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_gtk_offload_status (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_gtk_rekey_fail (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_host_swba (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_mgmt_rx (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_mgmt_tx_bundle_compl (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_mgmt_tx_compl (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_pdev_ftm_intg (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_pdev_qvit (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_pdev_tpc_config (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_peer_sta_kickout (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_phyerr (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_profile_match (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_ready (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_roam (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_rtt_error_report (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_rtt_measurement_report (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_scan (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_service_available (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_service_ready (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_tbttoffset_update (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_tdls_peer (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_tsf_measurement_report (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_update_stats (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_vdev_install_key_complete (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_vdev_start_resp (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_vdev_stopped (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_wlan_profile_data (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_wow_wakeup_host (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_tlv_event_bcn_tx_status (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_tlv_event_diag (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_tlv_event_diag_data (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_tlv_event_p2p_noa (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_tlv_event_peer_delete_resp (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_tlv_event_temperature (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_tlv_event_tx_pause (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_tlv_event_vdev_delete_resp (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/ * skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  trace_ath10k_wmi_event (struct ath10k*,int,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath10k_wmi_tlv_op_rx(struct ath10k *ar, struct sk_buff *skb)
{
	struct wmi_cmd_hdr *cmd_hdr;
	enum wmi_tlv_event_id id;
	bool consumed;

	cmd_hdr = (struct wmi_cmd_hdr *)skb->data;
	id = MS(__le32_to_cpu(cmd_hdr->cmd_id), WMI_CMD_HDR_CMD_ID);

	if (skb_pull(skb, sizeof(struct wmi_cmd_hdr)) == NULL)
		goto out;

	trace_ath10k_wmi_event(ar, id, skb->data, skb->len);

	consumed = ath10k_tm_event_wmi(ar, id, skb);

	/* Ready event must be handled normally also in UTF mode so that we
	 * know the UTF firmware has booted, others we are just bypass WMI
	 * events to testmode.
	 */
	if (consumed && id != WMI_TLV_READY_EVENTID) {
		ath10k_dbg(ar, ATH10K_DBG_WMI,
			   "wmi tlv testmode consumed 0x%x\n", id);
		goto out;
	}

	switch (id) {
	case WMI_TLV_MGMT_RX_EVENTID:
		ath10k_wmi_event_mgmt_rx(ar, skb);
		/* mgmt_rx() owns the skb now! */
		return;
	case WMI_TLV_SCAN_EVENTID:
		ath10k_wmi_event_scan(ar, skb);
		break;
	case WMI_TLV_CHAN_INFO_EVENTID:
		ath10k_wmi_event_chan_info(ar, skb);
		break;
	case WMI_TLV_ECHO_EVENTID:
		ath10k_wmi_event_echo(ar, skb);
		break;
	case WMI_TLV_DEBUG_MESG_EVENTID:
		ath10k_wmi_event_debug_mesg(ar, skb);
		break;
	case WMI_TLV_UPDATE_STATS_EVENTID:
		ath10k_wmi_event_update_stats(ar, skb);
		break;
	case WMI_TLV_VDEV_START_RESP_EVENTID:
		ath10k_wmi_event_vdev_start_resp(ar, skb);
		break;
	case WMI_TLV_VDEV_STOPPED_EVENTID:
		ath10k_wmi_event_vdev_stopped(ar, skb);
		break;
	case WMI_TLV_VDEV_DELETE_RESP_EVENTID:
		ath10k_wmi_tlv_event_vdev_delete_resp(ar, skb);
		break;
	case WMI_TLV_PEER_STA_KICKOUT_EVENTID:
		ath10k_wmi_event_peer_sta_kickout(ar, skb);
		break;
	case WMI_TLV_HOST_SWBA_EVENTID:
		ath10k_wmi_event_host_swba(ar, skb);
		break;
	case WMI_TLV_TBTTOFFSET_UPDATE_EVENTID:
		ath10k_wmi_event_tbttoffset_update(ar, skb);
		break;
	case WMI_TLV_PHYERR_EVENTID:
		ath10k_wmi_event_phyerr(ar, skb);
		break;
	case WMI_TLV_ROAM_EVENTID:
		ath10k_wmi_event_roam(ar, skb);
		break;
	case WMI_TLV_PROFILE_MATCH:
		ath10k_wmi_event_profile_match(ar, skb);
		break;
	case WMI_TLV_DEBUG_PRINT_EVENTID:
		ath10k_wmi_event_debug_print(ar, skb);
		break;
	case WMI_TLV_PDEV_QVIT_EVENTID:
		ath10k_wmi_event_pdev_qvit(ar, skb);
		break;
	case WMI_TLV_WLAN_PROFILE_DATA_EVENTID:
		ath10k_wmi_event_wlan_profile_data(ar, skb);
		break;
	case WMI_TLV_RTT_MEASUREMENT_REPORT_EVENTID:
		ath10k_wmi_event_rtt_measurement_report(ar, skb);
		break;
	case WMI_TLV_TSF_MEASUREMENT_REPORT_EVENTID:
		ath10k_wmi_event_tsf_measurement_report(ar, skb);
		break;
	case WMI_TLV_RTT_ERROR_REPORT_EVENTID:
		ath10k_wmi_event_rtt_error_report(ar, skb);
		break;
	case WMI_TLV_WOW_WAKEUP_HOST_EVENTID:
		ath10k_wmi_event_wow_wakeup_host(ar, skb);
		break;
	case WMI_TLV_DCS_INTERFERENCE_EVENTID:
		ath10k_wmi_event_dcs_interference(ar, skb);
		break;
	case WMI_TLV_PDEV_TPC_CONFIG_EVENTID:
		ath10k_wmi_event_pdev_tpc_config(ar, skb);
		break;
	case WMI_TLV_PDEV_FTM_INTG_EVENTID:
		ath10k_wmi_event_pdev_ftm_intg(ar, skb);
		break;
	case WMI_TLV_GTK_OFFLOAD_STATUS_EVENTID:
		ath10k_wmi_event_gtk_offload_status(ar, skb);
		break;
	case WMI_TLV_GTK_REKEY_FAIL_EVENTID:
		ath10k_wmi_event_gtk_rekey_fail(ar, skb);
		break;
	case WMI_TLV_TX_DELBA_COMPLETE_EVENTID:
		ath10k_wmi_event_delba_complete(ar, skb);
		break;
	case WMI_TLV_TX_ADDBA_COMPLETE_EVENTID:
		ath10k_wmi_event_addba_complete(ar, skb);
		break;
	case WMI_TLV_VDEV_INSTALL_KEY_COMPLETE_EVENTID:
		ath10k_wmi_event_vdev_install_key_complete(ar, skb);
		break;
	case WMI_TLV_SERVICE_READY_EVENTID:
		ath10k_wmi_event_service_ready(ar, skb);
		return;
	case WMI_TLV_READY_EVENTID:
		ath10k_wmi_event_ready(ar, skb);
		break;
	case WMI_TLV_SERVICE_AVAILABLE_EVENTID:
		ath10k_wmi_event_service_available(ar, skb);
		break;
	case WMI_TLV_OFFLOAD_BCN_TX_STATUS_EVENTID:
		ath10k_wmi_tlv_event_bcn_tx_status(ar, skb);
		break;
	case WMI_TLV_DIAG_DATA_CONTAINER_EVENTID:
		ath10k_wmi_tlv_event_diag_data(ar, skb);
		break;
	case WMI_TLV_DIAG_EVENTID:
		ath10k_wmi_tlv_event_diag(ar, skb);
		break;
	case WMI_TLV_P2P_NOA_EVENTID:
		ath10k_wmi_tlv_event_p2p_noa(ar, skb);
		break;
	case WMI_TLV_TX_PAUSE_EVENTID:
		ath10k_wmi_tlv_event_tx_pause(ar, skb);
		break;
	case WMI_TLV_PDEV_TEMPERATURE_EVENTID:
		ath10k_wmi_tlv_event_temperature(ar, skb);
		break;
	case WMI_TLV_TDLS_PEER_EVENTID:
		ath10k_wmi_event_tdls_peer(ar, skb);
		break;
	case WMI_TLV_PEER_DELETE_RESP_EVENTID:
		ath10k_wmi_tlv_event_peer_delete_resp(ar, skb);
		break;
	case WMI_TLV_MGMT_TX_COMPLETION_EVENTID:
		ath10k_wmi_event_mgmt_tx_compl(ar, skb);
		break;
	case WMI_TLV_MGMT_TX_BUNDLE_COMPLETION_EVENTID:
		ath10k_wmi_event_mgmt_tx_bundle_compl(ar, skb);
		break;
	default:
		ath10k_dbg(ar, ATH10K_DBG_WMI, "Unknown eventid: %d\n", id);
		break;
	}

out:
	dev_kfree_skb(skb);
}