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
struct dm_clone_metadata {int read_only; int /*<<< orphan*/  lock; int /*<<< orphan*/  bm; int /*<<< orphan*/  fail_io; int /*<<< orphan*/  bitmap_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  dm_bm_set_read_only (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void dm_clone_metadata_set_read_only(struct dm_clone_metadata *cmd)
{
	unsigned long flags;

	down_write(&cmd->lock);

	spin_lock_irqsave(&cmd->bitmap_lock, flags);
	cmd->read_only = 1;
	spin_unlock_irqrestore(&cmd->bitmap_lock, flags);

	if (!cmd->fail_io)
		dm_bm_set_read_only(cmd->bm);

	up_write(&cmd->lock);
}