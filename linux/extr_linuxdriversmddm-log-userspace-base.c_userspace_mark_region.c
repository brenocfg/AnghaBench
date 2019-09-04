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
struct log_c {int /*<<< orphan*/  flush_lock; int /*<<< orphan*/  mark_list; int /*<<< orphan*/  flush_entry_pool; } ;
struct dm_dirty_log_flush_entry {int /*<<< orphan*/  list; int /*<<< orphan*/  region; int /*<<< orphan*/  type; } ;
struct dm_dirty_log {struct log_c* context; } ;
typedef  int /*<<< orphan*/  region_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DM_ULOG_MARK_REGION ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct dm_dirty_log_flush_entry* mempool_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void userspace_mark_region(struct dm_dirty_log *log, region_t region)
{
	unsigned long flags;
	struct log_c *lc = log->context;
	struct dm_dirty_log_flush_entry *fe;

	/* Wait for an allocation, but _never_ fail */
	fe = mempool_alloc(&lc->flush_entry_pool, GFP_NOIO);
	BUG_ON(!fe);

	spin_lock_irqsave(&lc->flush_lock, flags);
	fe->type = DM_ULOG_MARK_REGION;
	fe->region = region;
	list_add(&fe->list, &lc->mark_list);
	spin_unlock_irqrestore(&lc->flush_lock, flags);

	return;
}