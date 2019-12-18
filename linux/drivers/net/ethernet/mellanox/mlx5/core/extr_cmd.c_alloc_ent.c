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
struct mlx5_cmd {int max_reg_cmds; int /*<<< orphan*/  alloc_lock; int /*<<< orphan*/  bitmask; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ *) ; 
 int find_first_bit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int alloc_ent(struct mlx5_cmd *cmd)
{
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&cmd->alloc_lock, flags);
	ret = find_first_bit(&cmd->bitmask, cmd->max_reg_cmds);
	if (ret < cmd->max_reg_cmds)
		clear_bit(ret, &cmd->bitmask);
	spin_unlock_irqrestore(&cmd->alloc_lock, flags);

	return ret < cmd->max_reg_cmds ? ret : -ENOMEM;
}