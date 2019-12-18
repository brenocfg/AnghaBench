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
struct mapped_device {int /*<<< orphan*/  queue; int /*<<< orphan*/  io_barrier; int /*<<< orphan*/  flags; int /*<<< orphan*/  wq; int /*<<< orphan*/  suspend_lock; } ;
struct dm_table {int dummy; } ;

/* Variables and functions */
 int DMF_BLOCK_IO_FOR_SUSPEND ; 
 int DMF_NOFLUSH_SUSPENDING ; 
 unsigned int DM_SUSPEND_LOCKFS_FLAG ; 
 unsigned int DM_SUSPEND_NOFLUSH_FLAG ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_device_name (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_queue_flush (struct mapped_device*) ; 
 scalar_t__ dm_request_based (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_start_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_stop_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_table_presuspend_targets (struct dm_table*) ; 
 int /*<<< orphan*/  dm_table_presuspend_undo_targets (struct dm_table*) ; 
 int dm_wait_for_completion (struct mapped_device*,long) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int lock_fs (struct mapped_device*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_srcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_fs (struct mapped_device*) ; 

__attribute__((used)) static int __dm_suspend(struct mapped_device *md, struct dm_table *map,
			unsigned suspend_flags, long task_state,
			int dmf_suspended_flag)
{
	bool do_lockfs = suspend_flags & DM_SUSPEND_LOCKFS_FLAG;
	bool noflush = suspend_flags & DM_SUSPEND_NOFLUSH_FLAG;
	int r;

	lockdep_assert_held(&md->suspend_lock);

	/*
	 * DMF_NOFLUSH_SUSPENDING must be set before presuspend.
	 * This flag is cleared before dm_suspend returns.
	 */
	if (noflush)
		set_bit(DMF_NOFLUSH_SUSPENDING, &md->flags);
	else
		pr_debug("%s: suspending with flush\n", dm_device_name(md));

	/*
	 * This gets reverted if there's an error later and the targets
	 * provide the .presuspend_undo hook.
	 */
	dm_table_presuspend_targets(map);

	/*
	 * Flush I/O to the device.
	 * Any I/O submitted after lock_fs() may not be flushed.
	 * noflush takes precedence over do_lockfs.
	 * (lock_fs() flushes I/Os and waits for them to complete.)
	 */
	if (!noflush && do_lockfs) {
		r = lock_fs(md);
		if (r) {
			dm_table_presuspend_undo_targets(map);
			return r;
		}
	}

	/*
	 * Here we must make sure that no processes are submitting requests
	 * to target drivers i.e. no one may be executing
	 * __split_and_process_bio. This is called from dm_request and
	 * dm_wq_work.
	 *
	 * To get all processes out of __split_and_process_bio in dm_request,
	 * we take the write lock. To prevent any process from reentering
	 * __split_and_process_bio from dm_request and quiesce the thread
	 * (dm_wq_work), we set BMF_BLOCK_IO_FOR_SUSPEND and call
	 * flush_workqueue(md->wq).
	 */
	set_bit(DMF_BLOCK_IO_FOR_SUSPEND, &md->flags);
	if (map)
		synchronize_srcu(&md->io_barrier);

	/*
	 * Stop md->queue before flushing md->wq in case request-based
	 * dm defers requests to md->wq from md->queue.
	 */
	if (dm_request_based(md))
		dm_stop_queue(md->queue);

	flush_workqueue(md->wq);

	/*
	 * At this point no more requests are entering target request routines.
	 * We call dm_wait_for_completion to wait for all existing requests
	 * to finish.
	 */
	r = dm_wait_for_completion(md, task_state);
	if (!r)
		set_bit(dmf_suspended_flag, &md->flags);

	if (noflush)
		clear_bit(DMF_NOFLUSH_SUSPENDING, &md->flags);
	if (map)
		synchronize_srcu(&md->io_barrier);

	/* were we interrupted ? */
	if (r < 0) {
		dm_queue_flush(md);

		if (dm_request_based(md))
			dm_start_queue(md->queue);

		unlock_fs(md);
		dm_table_presuspend_undo_targets(map);
		/* pushback list is already flushed, so skip flush */
	}

	return r;
}