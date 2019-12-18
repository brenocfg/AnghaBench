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
#define  MLX5_CMD_STAT_BAD_INP_LEN_ERR 143 
#define  MLX5_CMD_STAT_BAD_OP_ERR 142 
#define  MLX5_CMD_STAT_BAD_OUTP_LEN_ERR 141 
#define  MLX5_CMD_STAT_BAD_PARAM_ERR 140 
#define  MLX5_CMD_STAT_BAD_PKT_ERR 139 
#define  MLX5_CMD_STAT_BAD_QP_STATE_ERR 138 
#define  MLX5_CMD_STAT_BAD_RES_ERR 137 
#define  MLX5_CMD_STAT_BAD_RES_STATE_ERR 136 
#define  MLX5_CMD_STAT_BAD_SIZE_OUTS_CQES_ERR 135 
#define  MLX5_CMD_STAT_BAD_SYS_STATE_ERR 134 
#define  MLX5_CMD_STAT_INT_ERR 133 
#define  MLX5_CMD_STAT_IX_ERR 132 
#define  MLX5_CMD_STAT_LIM_ERR 131 
#define  MLX5_CMD_STAT_NO_RES_ERR 130 
#define  MLX5_CMD_STAT_OK 129 
#define  MLX5_CMD_STAT_RES_BUSY 128 

__attribute__((used)) static const char *cmd_status_str(u8 status)
{
	switch (status) {
	case MLX5_CMD_STAT_OK:
		return "OK";
	case MLX5_CMD_STAT_INT_ERR:
		return "internal error";
	case MLX5_CMD_STAT_BAD_OP_ERR:
		return "bad operation";
	case MLX5_CMD_STAT_BAD_PARAM_ERR:
		return "bad parameter";
	case MLX5_CMD_STAT_BAD_SYS_STATE_ERR:
		return "bad system state";
	case MLX5_CMD_STAT_BAD_RES_ERR:
		return "bad resource";
	case MLX5_CMD_STAT_RES_BUSY:
		return "resource busy";
	case MLX5_CMD_STAT_LIM_ERR:
		return "limits exceeded";
	case MLX5_CMD_STAT_BAD_RES_STATE_ERR:
		return "bad resource state";
	case MLX5_CMD_STAT_IX_ERR:
		return "bad index";
	case MLX5_CMD_STAT_NO_RES_ERR:
		return "no resources";
	case MLX5_CMD_STAT_BAD_INP_LEN_ERR:
		return "bad input length";
	case MLX5_CMD_STAT_BAD_OUTP_LEN_ERR:
		return "bad output length";
	case MLX5_CMD_STAT_BAD_QP_STATE_ERR:
		return "bad QP state";
	case MLX5_CMD_STAT_BAD_PKT_ERR:
		return "bad packet (discarded)";
	case MLX5_CMD_STAT_BAD_SIZE_OUTS_CQES_ERR:
		return "bad size too many outstanding CQEs";
	default:
		return "unknown status";
	}
}