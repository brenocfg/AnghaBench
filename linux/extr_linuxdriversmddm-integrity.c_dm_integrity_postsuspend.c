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
struct dm_target {scalar_t__ private; } ;
struct dm_integrity_c {char mode; int journal_uptodate; int /*<<< orphan*/  in_progress; int /*<<< orphan*/  suspending; scalar_t__ writer_wq; int /*<<< orphan*/  writer_work; scalar_t__ meta_dev; scalar_t__ commit_wq; int /*<<< orphan*/  commit_work; scalar_t__ recalc_wq; int /*<<< orphan*/  autocommit_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  RB_EMPTY_ROOT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_integrity_flush_buffers (struct dm_integrity_c*) ; 
 int /*<<< orphan*/  drain_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  queue_work (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dm_integrity_postsuspend(struct dm_target *ti)
{
	struct dm_integrity_c *ic = (struct dm_integrity_c *)ti->private;

	del_timer_sync(&ic->autocommit_timer);

	WRITE_ONCE(ic->suspending, 1);

	if (ic->recalc_wq)
		drain_workqueue(ic->recalc_wq);

	queue_work(ic->commit_wq, &ic->commit_work);
	drain_workqueue(ic->commit_wq);

	if (ic->mode == 'J') {
		if (ic->meta_dev)
			queue_work(ic->writer_wq, &ic->writer_work);
		drain_workqueue(ic->writer_wq);
		dm_integrity_flush_buffers(ic);
	}

	WRITE_ONCE(ic->suspending, 0);

	BUG_ON(!RB_EMPTY_ROOT(&ic->in_progress));

	ic->journal_uptodate = true;
}