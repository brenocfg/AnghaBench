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
struct TYPE_4__ {int /*<<< orphan*/  state_in_sysfs; } ;
struct request_queue {int /*<<< orphan*/  __queue_lock; int /*<<< orphan*/ * queue_lock; int /*<<< orphan*/  q_usage_counter; scalar_t__ mq_ops; TYPE_2__ kobj; TYPE_1__* backing_dev_info; int /*<<< orphan*/  sysfs_lock; int /*<<< orphan*/  bypass_depth; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
struct TYPE_3__ {int /*<<< orphan*/  laptop_mode_wb_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_FLAG_BYPASS ; 
 int /*<<< orphan*/  QUEUE_FLAG_DEAD ; 
 int /*<<< orphan*/  QUEUE_FLAG_DYING ; 
 int /*<<< orphan*/  QUEUE_FLAG_NOMERGES ; 
 int /*<<< orphan*/  QUEUE_FLAG_NOXMERGES ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_exit_queue (struct request_queue*) ; 
 int /*<<< orphan*/  blk_flush_integrity () ; 
 int /*<<< orphan*/  blk_freeze_queue (struct request_queue*) ; 
 int /*<<< orphan*/  blk_mq_free_queue (struct request_queue*) ; 
 int /*<<< orphan*/  blk_mq_quiesce_queue (struct request_queue*) ; 
 int /*<<< orphan*/  blk_put_queue (struct request_queue*) ; 
 scalar_t__ blk_queue_init_done (struct request_queue*) ; 
 int /*<<< orphan*/  blk_set_queue_dying (struct request_queue*) ; 
 int /*<<< orphan*/  blk_sync_queue (struct request_queue*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_ref_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_flag_set (int /*<<< orphan*/ ,struct request_queue*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void blk_cleanup_queue(struct request_queue *q)
{
	spinlock_t *lock = q->queue_lock;

	/* mark @q DYING, no new request or merges will be allowed afterwards */
	mutex_lock(&q->sysfs_lock);
	blk_set_queue_dying(q);
	spin_lock_irq(lock);

	/*
	 * A dying queue is permanently in bypass mode till released.  Note
	 * that, unlike blk_queue_bypass_start(), we aren't performing
	 * synchronize_rcu() after entering bypass mode to avoid the delay
	 * as some drivers create and destroy a lot of queues while
	 * probing.  This is still safe because blk_release_queue() will be
	 * called only after the queue refcnt drops to zero and nothing,
	 * RCU or not, would be traversing the queue by then.
	 */
	q->bypass_depth++;
	queue_flag_set(QUEUE_FLAG_BYPASS, q);

	queue_flag_set(QUEUE_FLAG_NOMERGES, q);
	queue_flag_set(QUEUE_FLAG_NOXMERGES, q);
	queue_flag_set(QUEUE_FLAG_DYING, q);
	spin_unlock_irq(lock);
	mutex_unlock(&q->sysfs_lock);

	/*
	 * Drain all requests queued before DYING marking. Set DEAD flag to
	 * prevent that q->request_fn() gets invoked after draining finished.
	 */
	blk_freeze_queue(q);
	spin_lock_irq(lock);
	queue_flag_set(QUEUE_FLAG_DEAD, q);
	spin_unlock_irq(lock);

	/*
	 * make sure all in-progress dispatch are completed because
	 * blk_freeze_queue() can only complete all requests, and
	 * dispatch may still be in-progress since we dispatch requests
	 * from more than one contexts.
	 *
	 * We rely on driver to deal with the race in case that queue
	 * initialization isn't done.
	 */
	if (q->mq_ops && blk_queue_init_done(q))
		blk_mq_quiesce_queue(q);

	/* for synchronous bio-based driver finish in-flight integrity i/o */
	blk_flush_integrity();

	/* @q won't process any more request, flush async actions */
	del_timer_sync(&q->backing_dev_info->laptop_mode_wb_timer);
	blk_sync_queue(q);

	/*
	 * I/O scheduler exit is only safe after the sysfs scheduler attribute
	 * has been removed.
	 */
	WARN_ON_ONCE(q->kobj.state_in_sysfs);

	blk_exit_queue(q);

	if (q->mq_ops)
		blk_mq_free_queue(q);
	percpu_ref_exit(&q->q_usage_counter);

	spin_lock_irq(lock);
	if (q->queue_lock != &q->__queue_lock)
		q->queue_lock = &q->__queue_lock;
	spin_unlock_irq(lock);

	/* @q is and will stay empty, shutdown and put */
	blk_put_queue(q);
}