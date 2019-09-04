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
#define  MLX5_CMD_DELIVERY_STAT_BAD_BLK_NUM_ERR 138 
#define  MLX5_CMD_DELIVERY_STAT_CMD_DESCR_ERR 137 
#define  MLX5_CMD_DELIVERY_STAT_FW_ERR 136 
#define  MLX5_CMD_DELIVERY_STAT_IN_LENGTH_ERR 135 
#define  MLX5_CMD_DELIVERY_STAT_IN_PTR_ALIGN_ERR 134 
#define  MLX5_CMD_DELIVERY_STAT_OK 133 
#define  MLX5_CMD_DELIVERY_STAT_OUT_LENGTH_ERR 132 
#define  MLX5_CMD_DELIVERY_STAT_OUT_PTR_ALIGN_ERR 131 
#define  MLX5_CMD_DELIVERY_STAT_RES_FLD_NOT_CLR_ERR 130 
#define  MLX5_CMD_DELIVERY_STAT_SIGNAT_ERR 129 
#define  MLX5_CMD_DELIVERY_STAT_TOK_ERR 128 

__attribute__((used)) static const char *deliv_status_to_str(u8 status)
{
	switch (status) {
	case MLX5_CMD_DELIVERY_STAT_OK:
		return "no errors";
	case MLX5_CMD_DELIVERY_STAT_SIGNAT_ERR:
		return "signature error";
	case MLX5_CMD_DELIVERY_STAT_TOK_ERR:
		return "token error";
	case MLX5_CMD_DELIVERY_STAT_BAD_BLK_NUM_ERR:
		return "bad block number";
	case MLX5_CMD_DELIVERY_STAT_OUT_PTR_ALIGN_ERR:
		return "output pointer not aligned to block size";
	case MLX5_CMD_DELIVERY_STAT_IN_PTR_ALIGN_ERR:
		return "input pointer not aligned to block size";
	case MLX5_CMD_DELIVERY_STAT_FW_ERR:
		return "firmware internal error";
	case MLX5_CMD_DELIVERY_STAT_IN_LENGTH_ERR:
		return "command input length error";
	case MLX5_CMD_DELIVERY_STAT_OUT_LENGTH_ERR:
		return "command output length error";
	case MLX5_CMD_DELIVERY_STAT_RES_FLD_NOT_CLR_ERR:
		return "reserved fields not cleared";
	case MLX5_CMD_DELIVERY_STAT_CMD_DESCR_ERR:
		return "bad command descriptor type";
	default:
		return "unknown status code";
	}
}