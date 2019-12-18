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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct wmi {int /*<<< orphan*/  parent_dev; } ;
struct ath6kl_vif {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_WMI ; 
 int EINVAL ; 
#define  WMI_ADDBA_REQ_EVENTID 146 
#define  WMI_BSSINFO_EVENTID 145 
#define  WMI_CAC_EVENTID 144 
#define  WMI_CANCEL_REMAIN_ON_CHNL_EVENTID 143 
#define  WMI_CONNECT_EVENTID 142 
#define  WMI_DELBA_REQ_EVENTID 141 
#define  WMI_DISCONNECT_EVENTID 140 
#define  WMI_DTIMEXPIRY_EVENTID 139 
#define  WMI_NEIGHBOR_REPORT_EVENTID 138 
#define  WMI_PSPOLL_EVENTID 137 
#define  WMI_REMAIN_ON_CHNL_EVENTID 136 
#define  WMI_REPORT_STATISTICS_EVENTID 135 
#define  WMI_RX_ACTION_EVENTID 134 
#define  WMI_RX_PROBE_REQ_EVENTID 133 
#define  WMI_SCAN_COMPLETE_EVENTID 132 
#define  WMI_SET_HOST_SLEEP_MODE_CMD_PROCESSED_EVENTID 131 
#define  WMI_TKIP_MICERR_EVENTID 130 
#define  WMI_TXE_NOTIFY_EVENTID 129 
#define  WMI_TX_STATUS_EVENTID 128 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,...) ; 
 struct ath6kl_vif* ath6kl_get_vif_by_index (int /*<<< orphan*/ ,int) ; 
 int ath6kl_wmi_addba_req_event_rx (struct wmi*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ath6kl_vif*) ; 
 int ath6kl_wmi_bssinfo_event_rx (struct wmi*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ath6kl_vif*) ; 
 int ath6kl_wmi_cac_event_rx (struct wmi*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ath6kl_vif*) ; 
 int ath6kl_wmi_cancel_remain_on_chnl_event_rx (struct wmi*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ath6kl_vif*) ; 
 int ath6kl_wmi_connect_event_rx (struct wmi*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ath6kl_vif*) ; 
 int ath6kl_wmi_delba_req_event_rx (struct wmi*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ath6kl_vif*) ; 
 int ath6kl_wmi_disconnect_event_rx (struct wmi*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ath6kl_vif*) ; 
 int ath6kl_wmi_dtimexpiry_event_rx (struct wmi*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ath6kl_vif*) ; 
 int ath6kl_wmi_host_sleep_mode_cmd_prcd_evt_rx (struct wmi*,struct ath6kl_vif*) ; 
 int ath6kl_wmi_neighbor_report_event_rx (struct wmi*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ath6kl_vif*) ; 
 int ath6kl_wmi_pspoll_event_rx (struct wmi*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ath6kl_vif*) ; 
 int ath6kl_wmi_remain_on_chnl_event_rx (struct wmi*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ath6kl_vif*) ; 
 int ath6kl_wmi_rx_action_event_rx (struct wmi*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ath6kl_vif*) ; 
 int ath6kl_wmi_rx_probe_req_event_rx (struct wmi*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ath6kl_vif*) ; 
 int ath6kl_wmi_scan_complete_rx (struct wmi*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ath6kl_vif*) ; 
 int ath6kl_wmi_stats_event_rx (struct wmi*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ath6kl_vif*) ; 
 int ath6kl_wmi_tkip_micerr_event_rx (struct wmi*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ath6kl_vif*) ; 
 int ath6kl_wmi_tx_status_event_rx (struct wmi*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ath6kl_vif*) ; 
 int ath6kl_wmi_txe_notify_event_rx (struct wmi*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ath6kl_vif*) ; 

__attribute__((used)) static int ath6kl_wmi_proc_events_vif(struct wmi *wmi, u16 if_idx, u16 cmd_id,
					u8 *datap, u32 len)
{
	struct ath6kl_vif *vif;

	vif = ath6kl_get_vif_by_index(wmi->parent_dev, if_idx);
	if (!vif) {
		ath6kl_dbg(ATH6KL_DBG_WMI,
			   "Wmi event for unavailable vif, vif_index:%d\n",
			    if_idx);
		return -EINVAL;
	}

	switch (cmd_id) {
	case WMI_CONNECT_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_CONNECT_EVENTID\n");
		return ath6kl_wmi_connect_event_rx(wmi, datap, len, vif);
	case WMI_DISCONNECT_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_DISCONNECT_EVENTID\n");
		return ath6kl_wmi_disconnect_event_rx(wmi, datap, len, vif);
	case WMI_TKIP_MICERR_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_TKIP_MICERR_EVENTID\n");
		return ath6kl_wmi_tkip_micerr_event_rx(wmi, datap, len, vif);
	case WMI_BSSINFO_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_BSSINFO_EVENTID\n");
		return ath6kl_wmi_bssinfo_event_rx(wmi, datap, len, vif);
	case WMI_NEIGHBOR_REPORT_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_NEIGHBOR_REPORT_EVENTID\n");
		return ath6kl_wmi_neighbor_report_event_rx(wmi, datap, len,
							   vif);
	case WMI_SCAN_COMPLETE_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_SCAN_COMPLETE_EVENTID\n");
		return ath6kl_wmi_scan_complete_rx(wmi, datap, len, vif);
	case WMI_REPORT_STATISTICS_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_REPORT_STATISTICS_EVENTID\n");
		return ath6kl_wmi_stats_event_rx(wmi, datap, len, vif);
	case WMI_CAC_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_CAC_EVENTID\n");
		return ath6kl_wmi_cac_event_rx(wmi, datap, len, vif);
	case WMI_PSPOLL_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_PSPOLL_EVENTID\n");
		return ath6kl_wmi_pspoll_event_rx(wmi, datap, len, vif);
	case WMI_DTIMEXPIRY_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_DTIMEXPIRY_EVENTID\n");
		return ath6kl_wmi_dtimexpiry_event_rx(wmi, datap, len, vif);
	case WMI_ADDBA_REQ_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_ADDBA_REQ_EVENTID\n");
		return ath6kl_wmi_addba_req_event_rx(wmi, datap, len, vif);
	case WMI_DELBA_REQ_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_DELBA_REQ_EVENTID\n");
		return ath6kl_wmi_delba_req_event_rx(wmi, datap, len, vif);
	case WMI_SET_HOST_SLEEP_MODE_CMD_PROCESSED_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI,
			   "WMI_SET_HOST_SLEEP_MODE_CMD_PROCESSED_EVENTID");
		return ath6kl_wmi_host_sleep_mode_cmd_prcd_evt_rx(wmi, vif);
	case WMI_REMAIN_ON_CHNL_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_REMAIN_ON_CHNL_EVENTID\n");
		return ath6kl_wmi_remain_on_chnl_event_rx(wmi, datap, len, vif);
	case WMI_CANCEL_REMAIN_ON_CHNL_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI,
			   "WMI_CANCEL_REMAIN_ON_CHNL_EVENTID\n");
		return ath6kl_wmi_cancel_remain_on_chnl_event_rx(wmi, datap,
								 len, vif);
	case WMI_TX_STATUS_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_TX_STATUS_EVENTID\n");
		return ath6kl_wmi_tx_status_event_rx(wmi, datap, len, vif);
	case WMI_RX_PROBE_REQ_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_RX_PROBE_REQ_EVENTID\n");
		return ath6kl_wmi_rx_probe_req_event_rx(wmi, datap, len, vif);
	case WMI_RX_ACTION_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_RX_ACTION_EVENTID\n");
		return ath6kl_wmi_rx_action_event_rx(wmi, datap, len, vif);
	case WMI_TXE_NOTIFY_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_TXE_NOTIFY_EVENTID\n");
		return ath6kl_wmi_txe_notify_event_rx(wmi, datap, len, vif);
	default:
		ath6kl_dbg(ATH6KL_DBG_WMI, "unknown cmd id 0x%x\n", cmd_id);
		return -EINVAL;
	}

	return 0;
}