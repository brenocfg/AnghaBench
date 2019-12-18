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
struct mlx5_cmd {int max_reg_cmds; int /*<<< orphan*/  sem; int /*<<< orphan*/  pages_sem; } ;
struct mlx5_core_dev {struct mlx5_cmd cmd; } ;

/* Variables and functions */
 scalar_t__ down_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_cmd_trigger_completions (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

void mlx5_cmd_flush(struct mlx5_core_dev *dev)
{
	struct mlx5_cmd *cmd = &dev->cmd;
	int i;

	for (i = 0; i < cmd->max_reg_cmds; i++)
		while (down_trylock(&cmd->sem))
			mlx5_cmd_trigger_completions(dev);

	while (down_trylock(&cmd->pages_sem))
		mlx5_cmd_trigger_completions(dev);

	/* Unlock cmdif */
	up(&cmd->pages_sem);
	for (i = 0; i < cmd->max_reg_cmds; i++)
		up(&cmd->sem);
}