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
struct log_writes_c {int /*<<< orphan*/  logdev; int /*<<< orphan*/  dev; int /*<<< orphan*/  unflushed_blocks; int /*<<< orphan*/  logging_blocks; int /*<<< orphan*/  log_kthread; int /*<<< orphan*/  pending_blocks; int /*<<< orphan*/  io_blocks; int /*<<< orphan*/  wait; int /*<<< orphan*/  blocks_lock; } ;
struct dm_target {struct log_writes_c* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_put_device (struct dm_target*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct log_writes_c*) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_mark (struct log_writes_c*,char*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void log_writes_dtr(struct dm_target *ti)
{
	struct log_writes_c *lc = ti->private;

	spin_lock_irq(&lc->blocks_lock);
	list_splice_init(&lc->unflushed_blocks, &lc->logging_blocks);
	spin_unlock_irq(&lc->blocks_lock);

	/*
	 * This is just nice to have since it'll update the super to include the
	 * unflushed blocks, if it fails we don't really care.
	 */
	log_mark(lc, "dm-log-writes-end");
	wake_up_process(lc->log_kthread);
	wait_event(lc->wait, !atomic_read(&lc->io_blocks) &&
		   !atomic_read(&lc->pending_blocks));
	kthread_stop(lc->log_kthread);

	WARN_ON(!list_empty(&lc->logging_blocks));
	WARN_ON(!list_empty(&lc->unflushed_blocks));
	dm_put_device(ti, lc->dev);
	dm_put_device(ti, lc->logdev);
	kfree(lc);
}