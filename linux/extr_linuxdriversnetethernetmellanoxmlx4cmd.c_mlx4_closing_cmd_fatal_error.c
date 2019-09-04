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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;

/* Variables and functions */
 scalar_t__ CMD_STAT_REG_BOUND ; 
 scalar_t__ MLX4_CMD_2RST_QP ; 
 scalar_t__ MLX4_CMD_CLOSE_HCA ; 
 scalar_t__ MLX4_CMD_HW2SW_CQ ; 
 scalar_t__ MLX4_CMD_HW2SW_EQ ; 
 scalar_t__ MLX4_CMD_HW2SW_MPT ; 
 scalar_t__ MLX4_CMD_HW2SW_SRQ ; 
 scalar_t__ MLX4_CMD_SYNC_TPT ; 
 scalar_t__ MLX4_CMD_UNMAP_FA ; 
 scalar_t__ MLX4_CMD_UNMAP_ICM ; 
 scalar_t__ MLX4_CMD_UNMAP_ICM_AUX ; 

__attribute__((used)) static int mlx4_closing_cmd_fatal_error(u16 op, u8 fw_status)
{
	/* Any error during the closing commands below is considered fatal */
	if (op == MLX4_CMD_CLOSE_HCA ||
	    op == MLX4_CMD_HW2SW_EQ ||
	    op == MLX4_CMD_HW2SW_CQ ||
	    op == MLX4_CMD_2RST_QP ||
	    op == MLX4_CMD_HW2SW_SRQ ||
	    op == MLX4_CMD_SYNC_TPT ||
	    op == MLX4_CMD_UNMAP_ICM ||
	    op == MLX4_CMD_UNMAP_ICM_AUX ||
	    op == MLX4_CMD_UNMAP_FA)
		return 1;
	/* Error on MLX4_CMD_HW2SW_MPT is fatal except when fw status equals
	  * CMD_STAT_REG_BOUND.
	  * This status indicates that memory region has memory windows bound to it
	  * which may result from invalid user space usage and is not fatal.
	  */
	if (op == MLX4_CMD_HW2SW_MPT && fw_status != CMD_STAT_REG_BOUND)
		return 1;
	return 0;
}