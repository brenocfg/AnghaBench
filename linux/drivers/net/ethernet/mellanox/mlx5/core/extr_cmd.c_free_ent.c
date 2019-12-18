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
struct mlx5_cmd {int /*<<< orphan*/  alloc_lock; int /*<<< orphan*/  bitmask; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void free_ent(struct mlx5_cmd *cmd, int idx)
{
	unsigned long flags;

	spin_lock_irqsave(&cmd->alloc_lock, flags);
	set_bit(idx, &cmd->bitmask);
	spin_unlock_irqrestore(&cmd->alloc_lock, flags);
}