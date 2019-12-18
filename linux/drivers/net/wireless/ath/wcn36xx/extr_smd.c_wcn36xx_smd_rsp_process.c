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
typedef  int /*<<< orphan*/  u32 ;
struct wcn36xx_hal_msg_header {int msg_type; } ;
struct wcn36xx_hal_ind_msg {int msg_len; int /*<<< orphan*/  list; int /*<<< orphan*/  msg; } ;
struct wcn36xx {int hal_rsp_len; int /*<<< orphan*/  hal_ind_lock; int /*<<< orphan*/  hal_ind_work; int /*<<< orphan*/  hal_ind_wq; int /*<<< orphan*/  hal_ind_queue; int /*<<< orphan*/  hal_rsp_compl; int /*<<< orphan*/  hal_buf; } ;
struct rpmsg_device {int dummy; } ;
struct ieee80211_hw {struct wcn36xx* priv; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  WCN36XX_DBG_HAL ; 
 int /*<<< orphan*/  WCN36XX_DBG_SMD_DUMP ; 
#define  WCN36XX_HAL_8023_MULTICAST_LIST_RSP 173 
#define  WCN36XX_HAL_ADD_BA_RSP 172 
#define  WCN36XX_HAL_ADD_BA_SESSION_RSP 171 
#define  WCN36XX_HAL_ADD_STA_SELF_RSP 170 
#define  WCN36XX_HAL_AVOID_FREQ_RANGE_IND 169 
#define  WCN36XX_HAL_CH_SWITCH_RSP 168 
#define  WCN36XX_HAL_COEX_IND 167 
#define  WCN36XX_HAL_CONFIG_BSS_RSP 166 
#define  WCN36XX_HAL_CONFIG_STA_RSP 165 
#define  WCN36XX_HAL_DELETE_BSS_RSP 164 
#define  WCN36XX_HAL_DELETE_STA_CONTEXT_IND 163 
#define  WCN36XX_HAL_DELETE_STA_RSP 162 
#define  WCN36XX_HAL_DEL_BA_IND 161 
#define  WCN36XX_HAL_DEL_BA_RSP 160 
#define  WCN36XX_HAL_DEL_STA_SELF_RSP 159 
#define  WCN36XX_HAL_DOWNLOAD_NV_RSP 158 
#define  WCN36XX_HAL_DUMP_COMMAND_RSP 157 
#define  WCN36XX_HAL_END_SCAN_RSP 156 
#define  WCN36XX_HAL_ENTER_BMPS_RSP 155 
#define  WCN36XX_HAL_EXIT_BMPS_RSP 154 
#define  WCN36XX_HAL_FEATURE_CAPS_EXCHANGE_RSP 153 
#define  WCN36XX_HAL_FINISH_SCAN_RSP 152 
#define  WCN36XX_HAL_INIT_SCAN_RSP 151 
#define  WCN36XX_HAL_JOIN_RSP 150 
#define  WCN36XX_HAL_KEEP_ALIVE_RSP 149 
#define  WCN36XX_HAL_MISSED_BEACON_IND 148 
#define  WCN36XX_HAL_OTA_TX_COMPL_IND 147 
#define  WCN36XX_HAL_PRINT_REG_INFO_IND 146 
#define  WCN36XX_HAL_PROCESS_PTT_RSP 145 
#define  WCN36XX_HAL_RMV_BSSKEY_RSP 144 
#define  WCN36XX_HAL_RMV_STAKEY_RSP 143 
#define  WCN36XX_HAL_SCAN_OFFLOAD_IND 142 
#define  WCN36XX_HAL_SEND_BEACON_RSP 141 
#define  WCN36XX_HAL_SET_BSSKEY_RSP 140 
#define  WCN36XX_HAL_SET_LINK_ST_RSP 139 
#define  WCN36XX_HAL_SET_POWER_PARAMS_RSP 138 
#define  WCN36XX_HAL_SET_STAKEY_RSP 137 
#define  WCN36XX_HAL_START_RSP 136 
#define  WCN36XX_HAL_START_SCAN_OFFLOAD_RSP 135 
#define  WCN36XX_HAL_START_SCAN_RSP 134 
#define  WCN36XX_HAL_STOP_RSP 133 
#define  WCN36XX_HAL_STOP_SCAN_OFFLOAD_RSP 132 
#define  WCN36XX_HAL_TRIGGER_BA_RSP 131 
#define  WCN36XX_HAL_UPDATE_CFG_RSP 130 
#define  WCN36XX_HAL_UPDATE_PROBE_RSP_TEMPLATE_RSP 129 
#define  WCN36XX_HAL_UPDATE_SCAN_PARAM_RSP 128 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 struct wcn36xx_hal_ind_msg* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcn36xx_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wcn36xx_dbg_dump (int /*<<< orphan*/ ,char*,void*,int) ; 
 int /*<<< orphan*/  wcn36xx_err (char*,int) ; 

int wcn36xx_smd_rsp_process(struct rpmsg_device *rpdev,
			    void *buf, int len, void *priv, u32 addr)
{
	const struct wcn36xx_hal_msg_header *msg_header = buf;
	struct ieee80211_hw *hw = priv;
	struct wcn36xx *wcn = hw->priv;
	struct wcn36xx_hal_ind_msg *msg_ind;
	wcn36xx_dbg_dump(WCN36XX_DBG_SMD_DUMP, "SMD <<< ", buf, len);

	switch (msg_header->msg_type) {
	case WCN36XX_HAL_START_RSP:
	case WCN36XX_HAL_CONFIG_STA_RSP:
	case WCN36XX_HAL_CONFIG_BSS_RSP:
	case WCN36XX_HAL_ADD_STA_SELF_RSP:
	case WCN36XX_HAL_STOP_RSP:
	case WCN36XX_HAL_DEL_STA_SELF_RSP:
	case WCN36XX_HAL_DELETE_STA_RSP:
	case WCN36XX_HAL_INIT_SCAN_RSP:
	case WCN36XX_HAL_START_SCAN_RSP:
	case WCN36XX_HAL_END_SCAN_RSP:
	case WCN36XX_HAL_FINISH_SCAN_RSP:
	case WCN36XX_HAL_DOWNLOAD_NV_RSP:
	case WCN36XX_HAL_DELETE_BSS_RSP:
	case WCN36XX_HAL_SEND_BEACON_RSP:
	case WCN36XX_HAL_SET_LINK_ST_RSP:
	case WCN36XX_HAL_UPDATE_PROBE_RSP_TEMPLATE_RSP:
	case WCN36XX_HAL_SET_BSSKEY_RSP:
	case WCN36XX_HAL_SET_STAKEY_RSP:
	case WCN36XX_HAL_RMV_STAKEY_RSP:
	case WCN36XX_HAL_RMV_BSSKEY_RSP:
	case WCN36XX_HAL_ENTER_BMPS_RSP:
	case WCN36XX_HAL_SET_POWER_PARAMS_RSP:
	case WCN36XX_HAL_EXIT_BMPS_RSP:
	case WCN36XX_HAL_KEEP_ALIVE_RSP:
	case WCN36XX_HAL_DUMP_COMMAND_RSP:
	case WCN36XX_HAL_ADD_BA_SESSION_RSP:
	case WCN36XX_HAL_ADD_BA_RSP:
	case WCN36XX_HAL_DEL_BA_RSP:
	case WCN36XX_HAL_TRIGGER_BA_RSP:
	case WCN36XX_HAL_UPDATE_CFG_RSP:
	case WCN36XX_HAL_JOIN_RSP:
	case WCN36XX_HAL_UPDATE_SCAN_PARAM_RSP:
	case WCN36XX_HAL_CH_SWITCH_RSP:
	case WCN36XX_HAL_PROCESS_PTT_RSP:
	case WCN36XX_HAL_FEATURE_CAPS_EXCHANGE_RSP:
	case WCN36XX_HAL_8023_MULTICAST_LIST_RSP:
	case WCN36XX_HAL_START_SCAN_OFFLOAD_RSP:
	case WCN36XX_HAL_STOP_SCAN_OFFLOAD_RSP:
		memcpy(wcn->hal_buf, buf, len);
		wcn->hal_rsp_len = len;
		complete(&wcn->hal_rsp_compl);
		break;

	case WCN36XX_HAL_COEX_IND:
	case WCN36XX_HAL_AVOID_FREQ_RANGE_IND:
	case WCN36XX_HAL_DEL_BA_IND:
	case WCN36XX_HAL_OTA_TX_COMPL_IND:
	case WCN36XX_HAL_MISSED_BEACON_IND:
	case WCN36XX_HAL_DELETE_STA_CONTEXT_IND:
	case WCN36XX_HAL_PRINT_REG_INFO_IND:
	case WCN36XX_HAL_SCAN_OFFLOAD_IND:
		msg_ind = kmalloc(sizeof(*msg_ind) + len, GFP_ATOMIC);
		if (!msg_ind) {
			wcn36xx_err("Run out of memory while handling SMD_EVENT (%d)\n",
				    msg_header->msg_type);
			return -ENOMEM;
		}

		msg_ind->msg_len = len;
		memcpy(msg_ind->msg, buf, len);

		spin_lock(&wcn->hal_ind_lock);
		list_add_tail(&msg_ind->list, &wcn->hal_ind_queue);
		queue_work(wcn->hal_ind_wq, &wcn->hal_ind_work);
		spin_unlock(&wcn->hal_ind_lock);
		wcn36xx_dbg(WCN36XX_DBG_HAL, "indication arrived\n");
		break;
	default:
		wcn36xx_err("SMD_EVENT (%d) not supported\n",
			      msg_header->msg_type);
	}

	return 0;
}