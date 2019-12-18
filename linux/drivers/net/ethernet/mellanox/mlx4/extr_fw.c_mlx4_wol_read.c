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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct mlx4_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX4_CMD_MOD_STAT_CFG ; 
 int /*<<< orphan*/  MLX4_CMD_NATIVE ; 
 int /*<<< orphan*/  MLX4_CMD_TIME_CLASS_A ; 
 int MLX4_WOL_SETUP_MODE ; 
 int mlx4_cmd_imm (struct mlx4_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mlx4_wol_read(struct mlx4_dev *dev, u64 *config, int port)
{
	u32 in_mod = MLX4_WOL_SETUP_MODE | port << 8;

	return mlx4_cmd_imm(dev, 0, config, in_mod, 0x3,
			    MLX4_CMD_MOD_STAT_CFG, MLX4_CMD_TIME_CLASS_A,
			    MLX4_CMD_NATIVE);
}