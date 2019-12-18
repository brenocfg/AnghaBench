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
struct mlx5_cmd_layout {int dummy; } ;
struct mlx5_cmd {int log_stride; struct mlx5_cmd_layout* cmd_buf; } ;

/* Variables and functions */

__attribute__((used)) static struct mlx5_cmd_layout *get_inst(struct mlx5_cmd *cmd, int idx)
{
	return cmd->cmd_buf + (idx << cmd->log_stride);
}