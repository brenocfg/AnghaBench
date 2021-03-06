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

/* Variables and functions */
#define  MLX5_EVENT_TYPE_CMD 158 
#define  MLX5_EVENT_TYPE_COMM_EST 157 
#define  MLX5_EVENT_TYPE_COMP 156 
#define  MLX5_EVENT_TYPE_CQ_ERROR 155 
#define  MLX5_EVENT_TYPE_DB_BF_CONGESTION 154 
#define  MLX5_EVENT_TYPE_DEVICE_TRACER 153 
#define  MLX5_EVENT_TYPE_ESW_FUNCTIONS_CHANGED 152 
#define  MLX5_EVENT_TYPE_FPGA_ERROR 151 
#define  MLX5_EVENT_TYPE_FPGA_QP_ERROR 150 
#define  MLX5_EVENT_TYPE_GENERAL_EVENT 149 
#define  MLX5_EVENT_TYPE_GPIO_EVENT 148 
#define  MLX5_EVENT_TYPE_INTERNAL_ERROR 147 
#define  MLX5_EVENT_TYPE_MONITOR_COUNTER 146 
#define  MLX5_EVENT_TYPE_NIC_VPORT_CHANGE 145 
#define  MLX5_EVENT_TYPE_PAGE_FAULT 144 
#define  MLX5_EVENT_TYPE_PAGE_REQUEST 143 
#define  MLX5_EVENT_TYPE_PATH_MIG 142 
#define  MLX5_EVENT_TYPE_PATH_MIG_FAILED 141 
#define  MLX5_EVENT_TYPE_PORT_CHANGE 140 
#define  MLX5_EVENT_TYPE_PORT_MODULE_EVENT 139 
#define  MLX5_EVENT_TYPE_PPS_EVENT 138 
#define  MLX5_EVENT_TYPE_REMOTE_CONFIG 137 
#define  MLX5_EVENT_TYPE_SQ_DRAINED 136 
#define  MLX5_EVENT_TYPE_SRQ_CATAS_ERROR 135 
#define  MLX5_EVENT_TYPE_SRQ_LAST_WQE 134 
#define  MLX5_EVENT_TYPE_SRQ_RQ_LIMIT 133 
#define  MLX5_EVENT_TYPE_STALL_EVENT 132 
#define  MLX5_EVENT_TYPE_TEMP_WARN_EVENT 131 
#define  MLX5_EVENT_TYPE_WQ_ACCESS_ERROR 130 
#define  MLX5_EVENT_TYPE_WQ_CATAS_ERROR 129 
#define  MLX5_EVENT_TYPE_WQ_INVAL_REQ_ERROR 128 

__attribute__((used)) static const char *eqe_type_str(u8 type)
{
	switch (type) {
	case MLX5_EVENT_TYPE_COMP:
		return "MLX5_EVENT_TYPE_COMP";
	case MLX5_EVENT_TYPE_PATH_MIG:
		return "MLX5_EVENT_TYPE_PATH_MIG";
	case MLX5_EVENT_TYPE_COMM_EST:
		return "MLX5_EVENT_TYPE_COMM_EST";
	case MLX5_EVENT_TYPE_SQ_DRAINED:
		return "MLX5_EVENT_TYPE_SQ_DRAINED";
	case MLX5_EVENT_TYPE_SRQ_LAST_WQE:
		return "MLX5_EVENT_TYPE_SRQ_LAST_WQE";
	case MLX5_EVENT_TYPE_SRQ_RQ_LIMIT:
		return "MLX5_EVENT_TYPE_SRQ_RQ_LIMIT";
	case MLX5_EVENT_TYPE_CQ_ERROR:
		return "MLX5_EVENT_TYPE_CQ_ERROR";
	case MLX5_EVENT_TYPE_WQ_CATAS_ERROR:
		return "MLX5_EVENT_TYPE_WQ_CATAS_ERROR";
	case MLX5_EVENT_TYPE_PATH_MIG_FAILED:
		return "MLX5_EVENT_TYPE_PATH_MIG_FAILED";
	case MLX5_EVENT_TYPE_WQ_INVAL_REQ_ERROR:
		return "MLX5_EVENT_TYPE_WQ_INVAL_REQ_ERROR";
	case MLX5_EVENT_TYPE_WQ_ACCESS_ERROR:
		return "MLX5_EVENT_TYPE_WQ_ACCESS_ERROR";
	case MLX5_EVENT_TYPE_SRQ_CATAS_ERROR:
		return "MLX5_EVENT_TYPE_SRQ_CATAS_ERROR";
	case MLX5_EVENT_TYPE_INTERNAL_ERROR:
		return "MLX5_EVENT_TYPE_INTERNAL_ERROR";
	case MLX5_EVENT_TYPE_PORT_CHANGE:
		return "MLX5_EVENT_TYPE_PORT_CHANGE";
	case MLX5_EVENT_TYPE_GPIO_EVENT:
		return "MLX5_EVENT_TYPE_GPIO_EVENT";
	case MLX5_EVENT_TYPE_PORT_MODULE_EVENT:
		return "MLX5_EVENT_TYPE_PORT_MODULE_EVENT";
	case MLX5_EVENT_TYPE_TEMP_WARN_EVENT:
		return "MLX5_EVENT_TYPE_TEMP_WARN_EVENT";
	case MLX5_EVENT_TYPE_REMOTE_CONFIG:
		return "MLX5_EVENT_TYPE_REMOTE_CONFIG";
	case MLX5_EVENT_TYPE_DB_BF_CONGESTION:
		return "MLX5_EVENT_TYPE_DB_BF_CONGESTION";
	case MLX5_EVENT_TYPE_STALL_EVENT:
		return "MLX5_EVENT_TYPE_STALL_EVENT";
	case MLX5_EVENT_TYPE_CMD:
		return "MLX5_EVENT_TYPE_CMD";
	case MLX5_EVENT_TYPE_ESW_FUNCTIONS_CHANGED:
		return "MLX5_EVENT_TYPE_ESW_FUNCTIONS_CHANGED";
	case MLX5_EVENT_TYPE_PAGE_REQUEST:
		return "MLX5_EVENT_TYPE_PAGE_REQUEST";
	case MLX5_EVENT_TYPE_PAGE_FAULT:
		return "MLX5_EVENT_TYPE_PAGE_FAULT";
	case MLX5_EVENT_TYPE_PPS_EVENT:
		return "MLX5_EVENT_TYPE_PPS_EVENT";
	case MLX5_EVENT_TYPE_NIC_VPORT_CHANGE:
		return "MLX5_EVENT_TYPE_NIC_VPORT_CHANGE";
	case MLX5_EVENT_TYPE_FPGA_ERROR:
		return "MLX5_EVENT_TYPE_FPGA_ERROR";
	case MLX5_EVENT_TYPE_FPGA_QP_ERROR:
		return "MLX5_EVENT_TYPE_FPGA_QP_ERROR";
	case MLX5_EVENT_TYPE_GENERAL_EVENT:
		return "MLX5_EVENT_TYPE_GENERAL_EVENT";
	case MLX5_EVENT_TYPE_MONITOR_COUNTER:
		return "MLX5_EVENT_TYPE_MONITOR_COUNTER";
	case MLX5_EVENT_TYPE_DEVICE_TRACER:
		return "MLX5_EVENT_TYPE_DEVICE_TRACER";
	default:
		return "Unrecognized event";
	}
}