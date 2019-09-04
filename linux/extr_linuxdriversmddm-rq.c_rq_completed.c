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
struct request_queue {int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  mq_ops; } ;
struct mapped_device {int /*<<< orphan*/  wait; int /*<<< orphan*/ * pending; struct request_queue* queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_run_queue_async (struct request_queue*) ; 
 int /*<<< orphan*/  dm_put (struct mapped_device*) ; 
 int /*<<< orphan*/  md_in_flight (struct mapped_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rq_completed(struct mapped_device *md, int rw, bool run_queue)
{
	struct request_queue *q = md->queue;
	unsigned long flags;

	atomic_dec(&md->pending[rw]);

	/* nudge anyone waiting on suspend queue */
	if (!md_in_flight(md))
		wake_up(&md->wait);

	/*
	 * Run this off this callpath, as drivers could invoke end_io while
	 * inside their request_fn (and holding the queue lock). Calling
	 * back into ->request_fn() could deadlock attempting to grab the
	 * queue lock again.
	 */
	if (!q->mq_ops && run_queue) {
		spin_lock_irqsave(q->queue_lock, flags);
		blk_run_queue_async(q);
		spin_unlock_irqrestore(q->queue_lock, flags);
	}

	/*
	 * dm_put() must be at the end of this function. See the comment above
	 */
	dm_put(md);
}