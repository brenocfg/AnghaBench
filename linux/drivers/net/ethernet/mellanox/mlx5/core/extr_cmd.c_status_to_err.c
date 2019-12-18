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
 int EBADR ; 
 int EFAULT ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMSG ; 
#define  MLX5_CMD_DELIVERY_STAT_BAD_BLK_NUM_ERR 139 
#define  MLX5_CMD_DELIVERY_STAT_CMD_DESCR_ERR 138 
#define  MLX5_CMD_DELIVERY_STAT_FW_ERR 137 
#define  MLX5_CMD_DELIVERY_STAT_IN_LENGTH_ERR 136 
#define  MLX5_CMD_DELIVERY_STAT_IN_PTR_ALIGN_ERR 135 
#define  MLX5_CMD_DELIVERY_STAT_OK 134 
#define  MLX5_CMD_DELIVERY_STAT_OUT_LENGTH_ERR 133 
#define  MLX5_CMD_DELIVERY_STAT_OUT_PTR_ALIGN_ERR 132 
#define  MLX5_CMD_DELIVERY_STAT_RES_FLD_NOT_CLR_ERR 131 
#define  MLX5_CMD_DELIVERY_STAT_SIGNAT_ERR 130 
#define  MLX5_CMD_DELIVERY_STAT_TOK_ERR 129 
#define  MLX5_DRIVER_STATUS_ABORTED 128 

__attribute__((used)) static int status_to_err(u8 status)
{
	switch (status) {
	case MLX5_CMD_DELIVERY_STAT_OK:
	case MLX5_DRIVER_STATUS_ABORTED:
		return 0;
	case MLX5_CMD_DELIVERY_STAT_SIGNAT_ERR:
	case MLX5_CMD_DELIVERY_STAT_TOK_ERR:
		return -EBADR;
	case MLX5_CMD_DELIVERY_STAT_BAD_BLK_NUM_ERR:
	case MLX5_CMD_DELIVERY_STAT_OUT_PTR_ALIGN_ERR:
	case MLX5_CMD_DELIVERY_STAT_IN_PTR_ALIGN_ERR:
		return -EFAULT; /* Bad address */
	case MLX5_CMD_DELIVERY_STAT_IN_LENGTH_ERR:
	case MLX5_CMD_DELIVERY_STAT_OUT_LENGTH_ERR:
	case MLX5_CMD_DELIVERY_STAT_CMD_DESCR_ERR:
	case MLX5_CMD_DELIVERY_STAT_RES_FLD_NOT_CLR_ERR:
		return -ENOMSG;
	case MLX5_CMD_DELIVERY_STAT_FW_ERR:
		return -EIO;
	default:
		return -EINVAL;
	}
}