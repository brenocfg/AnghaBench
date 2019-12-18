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
typedef  enum wmi_cmd_id { ____Placeholder_wmi_cmd_id } wmi_cmd_id ;

/* Variables and functions */
#define  WMI_ABORT_TXQ_CMDID 159 
#define  WMI_ABORT_TX_DMA_CMDID 158 
#define  WMI_ACCESS_MEMORY_CMDID 157 
#define  WMI_ATH_INIT_CMDID 156 
#define  WMI_BITRATE_MASK_CMDID 155 
#define  WMI_DISABLE_INTR_CMDID 154 
#define  WMI_DRAIN_TXQ_ALL_CMDID 153 
#define  WMI_DRAIN_TXQ_CMDID 152 
#define  WMI_ECHO_CMDID 151 
#define  WMI_ENABLE_INTR_CMDID 150 
#define  WMI_FLUSH_RECV_CMDID 149 
#define  WMI_GET_FW_VERSION 148 
#define  WMI_INT_STATS_CMDID 147 
#define  WMI_NODE_CREATE_CMDID 146 
#define  WMI_NODE_REMOVE_CMDID 145 
#define  WMI_NODE_UPDATE_CMDID 144 
#define  WMI_RC_RATE_UPDATE_CMDID 143 
#define  WMI_RC_STATE_CHANGE_CMDID 142 
#define  WMI_REG_READ_CMDID 141 
#define  WMI_REG_RMW_CMDID 140 
#define  WMI_REG_WRITE_CMDID 139 
#define  WMI_RX_STATS_CMDID 138 
#define  WMI_SET_MODE_CMDID 137 
#define  WMI_START_RECV_CMDID 136 
#define  WMI_STOP_RECV_CMDID 135 
#define  WMI_STOP_TX_DMA_CMDID 134 
#define  WMI_TARGET_IC_UPDATE_CMDID 133 
#define  WMI_TGT_DETACH_CMDID 132 
#define  WMI_TX_AGGR_ENABLE_CMDID 131 
#define  WMI_TX_STATS_CMDID 130 
#define  WMI_VAP_CREATE_CMDID 129 
#define  WMI_VAP_REMOVE_CMDID 128 

__attribute__((used)) static const char *wmi_cmd_to_name(enum wmi_cmd_id wmi_cmd)
{
	switch (wmi_cmd) {
	case WMI_ECHO_CMDID:
		return "WMI_ECHO_CMDID";
	case WMI_ACCESS_MEMORY_CMDID:
		return "WMI_ACCESS_MEMORY_CMDID";
	case WMI_GET_FW_VERSION:
		return "WMI_GET_FW_VERSION";
	case WMI_DISABLE_INTR_CMDID:
		return "WMI_DISABLE_INTR_CMDID";
	case WMI_ENABLE_INTR_CMDID:
		return "WMI_ENABLE_INTR_CMDID";
	case WMI_ATH_INIT_CMDID:
		return "WMI_ATH_INIT_CMDID";
	case WMI_ABORT_TXQ_CMDID:
		return "WMI_ABORT_TXQ_CMDID";
	case WMI_STOP_TX_DMA_CMDID:
		return "WMI_STOP_TX_DMA_CMDID";
	case WMI_ABORT_TX_DMA_CMDID:
		return "WMI_ABORT_TX_DMA_CMDID";
	case WMI_DRAIN_TXQ_CMDID:
		return "WMI_DRAIN_TXQ_CMDID";
	case WMI_DRAIN_TXQ_ALL_CMDID:
		return "WMI_DRAIN_TXQ_ALL_CMDID";
	case WMI_START_RECV_CMDID:
		return "WMI_START_RECV_CMDID";
	case WMI_STOP_RECV_CMDID:
		return "WMI_STOP_RECV_CMDID";
	case WMI_FLUSH_RECV_CMDID:
		return "WMI_FLUSH_RECV_CMDID";
	case WMI_SET_MODE_CMDID:
		return "WMI_SET_MODE_CMDID";
	case WMI_NODE_CREATE_CMDID:
		return "WMI_NODE_CREATE_CMDID";
	case WMI_NODE_REMOVE_CMDID:
		return "WMI_NODE_REMOVE_CMDID";
	case WMI_VAP_REMOVE_CMDID:
		return "WMI_VAP_REMOVE_CMDID";
	case WMI_VAP_CREATE_CMDID:
		return "WMI_VAP_CREATE_CMDID";
	case WMI_REG_READ_CMDID:
		return "WMI_REG_READ_CMDID";
	case WMI_REG_WRITE_CMDID:
		return "WMI_REG_WRITE_CMDID";
	case WMI_REG_RMW_CMDID:
		return "WMI_REG_RMW_CMDID";
	case WMI_RC_STATE_CHANGE_CMDID:
		return "WMI_RC_STATE_CHANGE_CMDID";
	case WMI_RC_RATE_UPDATE_CMDID:
		return "WMI_RC_RATE_UPDATE_CMDID";
	case WMI_TARGET_IC_UPDATE_CMDID:
		return "WMI_TARGET_IC_UPDATE_CMDID";
	case WMI_TX_AGGR_ENABLE_CMDID:
		return "WMI_TX_AGGR_ENABLE_CMDID";
	case WMI_TGT_DETACH_CMDID:
		return "WMI_TGT_DETACH_CMDID";
	case WMI_NODE_UPDATE_CMDID:
		return "WMI_NODE_UPDATE_CMDID";
	case WMI_INT_STATS_CMDID:
		return "WMI_INT_STATS_CMDID";
	case WMI_TX_STATS_CMDID:
		return "WMI_TX_STATS_CMDID";
	case WMI_RX_STATS_CMDID:
		return "WMI_RX_STATS_CMDID";
	case WMI_BITRATE_MASK_CMDID:
		return "WMI_BITRATE_MASK_CMDID";
	}

	return "Bogus";
}