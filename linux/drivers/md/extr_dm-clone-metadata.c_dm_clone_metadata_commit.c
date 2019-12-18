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
struct dm_clone_metadata {int /*<<< orphan*/  lock; int /*<<< orphan*/  bitmap_lock; struct dirty_map* current_dmap; struct dirty_map* dmap; int /*<<< orphan*/  bm; scalar_t__ fail_io; } ;
struct dirty_map {int /*<<< orphan*/  changed; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int __flush_dmap (struct dm_clone_metadata*,struct dirty_map*) ; 
 scalar_t__ dm_bm_is_read_only (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int dm_clone_metadata_commit(struct dm_clone_metadata *cmd)
{
	int r = -EPERM;
	unsigned long flags;
	struct dirty_map *dmap, *next_dmap;

	down_write(&cmd->lock);

	if (cmd->fail_io || dm_bm_is_read_only(cmd->bm))
		goto out;

	/* Get current dirty bitmap */
	dmap = cmd->current_dmap;

	/* Get next dirty bitmap */
	next_dmap = (dmap == &cmd->dmap[0]) ? &cmd->dmap[1] : &cmd->dmap[0];

	/*
	 * The last commit failed, so we don't have a clean dirty-bitmap to
	 * use.
	 */
	if (WARN_ON(next_dmap->changed)) {
		r = -EINVAL;
		goto out;
	}

	/* Swap dirty bitmaps */
	spin_lock_irqsave(&cmd->bitmap_lock, flags);
	cmd->current_dmap = next_dmap;
	spin_unlock_irqrestore(&cmd->bitmap_lock, flags);

	/*
	 * No one is accessing the old dirty bitmap anymore, so we can flush
	 * it.
	 */
	r = __flush_dmap(cmd, dmap);
out:
	up_write(&cmd->lock);

	return r;
}