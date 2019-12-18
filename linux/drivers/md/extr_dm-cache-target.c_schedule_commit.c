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
struct batcher {int commit_scheduled; int /*<<< orphan*/  lock; int /*<<< orphan*/  bios; int /*<<< orphan*/  work_items; } ;

/* Variables and functions */
 int /*<<< orphan*/  async_commit (struct batcher*) ; 
 int /*<<< orphan*/  bio_list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void schedule_commit(struct batcher *b)
{
	bool immediate;
	unsigned long flags;

	spin_lock_irqsave(&b->lock, flags);
	immediate = !list_empty(&b->work_items) || !bio_list_empty(&b->bios);
	b->commit_scheduled = true;
	spin_unlock_irqrestore(&b->lock, flags);

	if (immediate)
		async_commit(b);
}