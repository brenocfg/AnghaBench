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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct wmi_cmd_hdr {int /*<<< orphan*/  info1; int /*<<< orphan*/  cmd_id; } ;
struct wmi {int dummy; } ;
struct sk_buff {int* data; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_WMI ; 
 int /*<<< orphan*/  ATH6KL_DBG_WMI_DUMP ; 
#define  WMI_ADDBA_RESP_EVENTID 158 
#define  WMI_APLIST_EVENTID 157 
#define  WMI_CHANNEL_CHANGE_EVENTID 156 
#define  WMI_CMDERROR_EVENTID 155 
 int WMI_CMD_HDR_IF_ID_MASK ; 
#define  WMI_ERROR_REPORT_EVENTID 154 
#define  WMI_EXTENSION_EVENTID 153 
#define  WMI_GET_BITRATE_CMDID 152 
#define  WMI_GET_CHANNEL_LIST_CMDID 151 
#define  WMI_GET_FIXRATES_CMDID 150 
#define  WMI_GET_KEEPALIVE_CMDID 149 
#define  WMI_GET_PMKID_LIST_EVENTID 148 
#define  WMI_GET_TX_PWR_CMDID 147 
#define  WMI_GET_WOW_LIST_EVENTID 146 
#define  WMI_LQ_THRESHOLD_EVENTID 145 
#define  WMI_OPT_RX_FRAME_EVENTID 144 
#define  WMI_P2P_CAPABILITIES_EVENTID 143 
#define  WMI_P2P_INFO_EVENTID 142 
#define  WMI_PEER_NODE_EVENTID 141 
#define  WMI_PSTREAM_TIMEOUT_EVENTID 140 
#define  WMI_READY_EVENTID 139 
#define  WMI_REGDOMAIN_EVENTID 138 
#define  WMI_REPORT_BTCOEX_CONFIG_EVENTID 137 
#define  WMI_REPORT_BTCOEX_STATS_EVENTID 136 
#define  WMI_REPORT_ROAM_DATA_EVENTID 135 
#define  WMI_REPORT_ROAM_TBL_EVENTID 134 
#define  WMI_RSSI_THRESHOLD_EVENTID 133 
#define  WMI_SET_PARAMS_REPLY_EVENTID 132 
#define  WMI_SNR_THRESHOLD_EVENTID 131 
#define  WMI_TEST_EVENTID 130 
#define  WMI_TX_COMPLETE_EVENTID 129 
#define  WMI_TX_RETRY_ERR_EVENTID 128 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ath6kl_dbg_dump (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int*,int /*<<< orphan*/ ) ; 
 int ath6kl_wmi_aplist_event_rx (struct wmi*,int*,int /*<<< orphan*/ ) ; 
 int ath6kl_wmi_bitrate_reply_rx (struct wmi*,int*,int /*<<< orphan*/ ) ; 
 int ath6kl_wmi_ch_list_reply_rx (struct wmi*,int*,int /*<<< orphan*/ ) ; 
 int ath6kl_wmi_control_rx_xtnd (struct wmi*,struct sk_buff*) ; 
 int ath6kl_wmi_error_event_rx (struct wmi*,int*,int /*<<< orphan*/ ) ; 
 int ath6kl_wmi_get_pmkid_list_event_rx (struct wmi*,int*,int /*<<< orphan*/ ) ; 
 int ath6kl_wmi_keepalive_reply_rx (struct wmi*,int*,int /*<<< orphan*/ ) ; 
 int ath6kl_wmi_p2p_capabilities_event_rx (int*,int /*<<< orphan*/ ) ; 
 int ath6kl_wmi_p2p_info_event_rx (int*,int /*<<< orphan*/ ) ; 
 int ath6kl_wmi_peer_node_event_rx (struct wmi*,int*,int /*<<< orphan*/ ) ; 
 int ath6kl_wmi_proc_events_vif (struct wmi*,int,int,int*,int /*<<< orphan*/ ) ; 
 int ath6kl_wmi_pstream_timeout_event_rx (struct wmi*,int*,int /*<<< orphan*/ ) ; 
 int ath6kl_wmi_ratemask_reply_rx (struct wmi*,int*,int /*<<< orphan*/ ) ; 
 int ath6kl_wmi_ready_event_rx (struct wmi*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath6kl_wmi_regdomain_event (struct wmi*,int*,int /*<<< orphan*/ ) ; 
 int ath6kl_wmi_roam_tbl_event_rx (struct wmi*,int*,int /*<<< orphan*/ ) ; 
 int ath6kl_wmi_rssi_threshold_event_rx (struct wmi*,int*,int /*<<< orphan*/ ) ; 
 int ath6kl_wmi_snr_threshold_event_rx (struct wmi*,int*,int /*<<< orphan*/ ) ; 
 int ath6kl_wmi_test_rx (struct wmi*,int*,int /*<<< orphan*/ ) ; 
 int ath6kl_wmi_tx_complete_event_rx (int*,int /*<<< orphan*/ ) ; 
 int ath6kl_wmi_tx_pwr_reply_rx (struct wmi*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 

__attribute__((used)) static int ath6kl_wmi_proc_events(struct wmi *wmi, struct sk_buff *skb)
{
	struct wmi_cmd_hdr *cmd;
	int ret = 0;
	u32 len;
	u16 id;
	u8 if_idx;
	u8 *datap;

	cmd = (struct wmi_cmd_hdr *) skb->data;
	id = le16_to_cpu(cmd->cmd_id);
	if_idx = le16_to_cpu(cmd->info1) & WMI_CMD_HDR_IF_ID_MASK;

	skb_pull(skb, sizeof(struct wmi_cmd_hdr));
	datap = skb->data;
	len = skb->len;

	ath6kl_dbg(ATH6KL_DBG_WMI, "wmi rx id %d len %d\n", id, len);
	ath6kl_dbg_dump(ATH6KL_DBG_WMI_DUMP, NULL, "wmi rx ",
			datap, len);

	switch (id) {
	case WMI_GET_BITRATE_CMDID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_GET_BITRATE_CMDID\n");
		ret = ath6kl_wmi_bitrate_reply_rx(wmi, datap, len);
		break;
	case WMI_GET_CHANNEL_LIST_CMDID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_GET_CHANNEL_LIST_CMDID\n");
		ret = ath6kl_wmi_ch_list_reply_rx(wmi, datap, len);
		break;
	case WMI_GET_TX_PWR_CMDID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_GET_TX_PWR_CMDID\n");
		ret = ath6kl_wmi_tx_pwr_reply_rx(wmi, datap, len);
		break;
	case WMI_READY_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_READY_EVENTID\n");
		ret = ath6kl_wmi_ready_event_rx(wmi, datap, len);
		break;
	case WMI_PEER_NODE_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_PEER_NODE_EVENTID\n");
		ret = ath6kl_wmi_peer_node_event_rx(wmi, datap, len);
		break;
	case WMI_REGDOMAIN_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_REGDOMAIN_EVENTID\n");
		ath6kl_wmi_regdomain_event(wmi, datap, len);
		break;
	case WMI_PSTREAM_TIMEOUT_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_PSTREAM_TIMEOUT_EVENTID\n");
		ret = ath6kl_wmi_pstream_timeout_event_rx(wmi, datap, len);
		break;
	case WMI_CMDERROR_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_CMDERROR_EVENTID\n");
		ret = ath6kl_wmi_error_event_rx(wmi, datap, len);
		break;
	case WMI_RSSI_THRESHOLD_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_RSSI_THRESHOLD_EVENTID\n");
		ret = ath6kl_wmi_rssi_threshold_event_rx(wmi, datap, len);
		break;
	case WMI_ERROR_REPORT_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_ERROR_REPORT_EVENTID\n");
		break;
	case WMI_OPT_RX_FRAME_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_OPT_RX_FRAME_EVENTID\n");
		/* this event has been deprecated */
		break;
	case WMI_REPORT_ROAM_TBL_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_REPORT_ROAM_TBL_EVENTID\n");
		ret = ath6kl_wmi_roam_tbl_event_rx(wmi, datap, len);
		break;
	case WMI_EXTENSION_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_EXTENSION_EVENTID\n");
		ret = ath6kl_wmi_control_rx_xtnd(wmi, skb);
		break;
	case WMI_CHANNEL_CHANGE_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_CHANNEL_CHANGE_EVENTID\n");
		break;
	case WMI_REPORT_ROAM_DATA_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_REPORT_ROAM_DATA_EVENTID\n");
		break;
	case WMI_TEST_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_TEST_EVENTID\n");
		ret = ath6kl_wmi_test_rx(wmi, datap, len);
		break;
	case WMI_GET_FIXRATES_CMDID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_GET_FIXRATES_CMDID\n");
		ret = ath6kl_wmi_ratemask_reply_rx(wmi, datap, len);
		break;
	case WMI_TX_RETRY_ERR_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_TX_RETRY_ERR_EVENTID\n");
		break;
	case WMI_SNR_THRESHOLD_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_SNR_THRESHOLD_EVENTID\n");
		ret = ath6kl_wmi_snr_threshold_event_rx(wmi, datap, len);
		break;
	case WMI_LQ_THRESHOLD_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_LQ_THRESHOLD_EVENTID\n");
		break;
	case WMI_APLIST_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_APLIST_EVENTID\n");
		ret = ath6kl_wmi_aplist_event_rx(wmi, datap, len);
		break;
	case WMI_GET_KEEPALIVE_CMDID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_GET_KEEPALIVE_CMDID\n");
		ret = ath6kl_wmi_keepalive_reply_rx(wmi, datap, len);
		break;
	case WMI_GET_WOW_LIST_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_GET_WOW_LIST_EVENTID\n");
		break;
	case WMI_GET_PMKID_LIST_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_GET_PMKID_LIST_EVENTID\n");
		ret = ath6kl_wmi_get_pmkid_list_event_rx(wmi, datap, len);
		break;
	case WMI_SET_PARAMS_REPLY_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_SET_PARAMS_REPLY_EVENTID\n");
		break;
	case WMI_ADDBA_RESP_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_ADDBA_RESP_EVENTID\n");
		break;
	case WMI_REPORT_BTCOEX_CONFIG_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI,
			   "WMI_REPORT_BTCOEX_CONFIG_EVENTID\n");
		break;
	case WMI_REPORT_BTCOEX_STATS_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI,
			   "WMI_REPORT_BTCOEX_STATS_EVENTID\n");
		break;
	case WMI_TX_COMPLETE_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_TX_COMPLETE_EVENTID\n");
		ret = ath6kl_wmi_tx_complete_event_rx(datap, len);
		break;
	case WMI_P2P_CAPABILITIES_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_P2P_CAPABILITIES_EVENTID\n");
		ret = ath6kl_wmi_p2p_capabilities_event_rx(datap, len);
		break;
	case WMI_P2P_INFO_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_P2P_INFO_EVENTID\n");
		ret = ath6kl_wmi_p2p_info_event_rx(datap, len);
		break;
	default:
		/* may be the event is interface specific */
		ret = ath6kl_wmi_proc_events_vif(wmi, if_idx, id, datap, len);
		break;
	}

	dev_kfree_skb(skb);
	return ret;
}