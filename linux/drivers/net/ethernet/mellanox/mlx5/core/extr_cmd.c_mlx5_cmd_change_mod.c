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
struct mlx5_cmd {int max_reg_cmds; int mode; int /*<<< orphan*/  sem; int /*<<< orphan*/  pages_sem; } ;
struct mlx5_core_dev {struct mlx5_cmd cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlx5_cmd_change_mod(struct mlx5_core_dev *dev, int mode)
{
	struct mlx5_cmd *cmd = &dev->cmd;
	int i;

	for (i = 0; i < cmd->max_reg_cmds; i++)
		down(&cmd->sem);
	down(&cmd->pages_sem);

	cmd->mode = mode;

	up(&cmd->pages_sem);
	for (i = 0; i < cmd->max_reg_cmds; i++)
		up(&cmd->sem);
}