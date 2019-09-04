#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct r5l_log {scalar_t__ max_free_space; int /*<<< orphan*/  io_mutex; scalar_t__ last_checkpoint; int /*<<< orphan*/  io_list_lock; int /*<<< orphan*/  iounit_wait; TYPE_2__* rdev; int /*<<< orphan*/  finished_ios; int /*<<< orphan*/  flushing_ios; int /*<<< orphan*/  io_end_ios; int /*<<< orphan*/  running_ios; int /*<<< orphan*/  no_space_stripes; int /*<<< orphan*/  reclaim_target; } ;
struct r5conf {int dummy; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_4__ {TYPE_1__* mddev; } ;
struct TYPE_3__ {int /*<<< orphan*/  thread; struct r5conf* private; } ;

/* Variables and functions */
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  md_wakeup_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ r5c_calculate_new_cp (struct r5conf*) ; 
 int /*<<< orphan*/  r5c_update_log_state (struct r5l_log*) ; 
 scalar_t__ r5l_reclaimable_space (struct r5l_log*) ; 
 int /*<<< orphan*/  r5l_run_no_space_stripes (struct r5l_log*) ; 
 int /*<<< orphan*/  r5l_write_super_and_discard_space (struct r5l_log*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_lock_irq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r5l_do_reclaim(struct r5l_log *log)
{
	struct r5conf *conf = log->rdev->mddev->private;
	sector_t reclaim_target = xchg(&log->reclaim_target, 0);
	sector_t reclaimable;
	sector_t next_checkpoint;
	bool write_super;

	spin_lock_irq(&log->io_list_lock);
	write_super = r5l_reclaimable_space(log) > log->max_free_space ||
		reclaim_target != 0 || !list_empty(&log->no_space_stripes);
	/*
	 * move proper io_unit to reclaim list. We should not change the order.
	 * reclaimable/unreclaimable io_unit can be mixed in the list, we
	 * shouldn't reuse space of an unreclaimable io_unit
	 */
	while (1) {
		reclaimable = r5l_reclaimable_space(log);
		if (reclaimable >= reclaim_target ||
		    (list_empty(&log->running_ios) &&
		     list_empty(&log->io_end_ios) &&
		     list_empty(&log->flushing_ios) &&
		     list_empty(&log->finished_ios)))
			break;

		md_wakeup_thread(log->rdev->mddev->thread);
		wait_event_lock_irq(log->iounit_wait,
				    r5l_reclaimable_space(log) > reclaimable,
				    log->io_list_lock);
	}

	next_checkpoint = r5c_calculate_new_cp(conf);
	spin_unlock_irq(&log->io_list_lock);

	if (reclaimable == 0 || !write_super)
		return;

	/*
	 * write_super will flush cache of each raid disk. We must write super
	 * here, because the log area might be reused soon and we don't want to
	 * confuse recovery
	 */
	r5l_write_super_and_discard_space(log, next_checkpoint);

	mutex_lock(&log->io_mutex);
	log->last_checkpoint = next_checkpoint;
	r5c_update_log_state(log);
	mutex_unlock(&log->io_mutex);

	r5l_run_no_space_stripes(log);
}