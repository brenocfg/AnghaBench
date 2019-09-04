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
struct request_queue {int /*<<< orphan*/  request_fn_active; int /*<<< orphan*/  (* request_fn ) (struct request_queue*) ;int /*<<< orphan*/  mq_ops; int /*<<< orphan*/  queue_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_dead (struct request_queue*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct request_queue*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

inline void __blk_run_queue_uncond(struct request_queue *q)
{
	lockdep_assert_held(q->queue_lock);
	WARN_ON_ONCE(q->mq_ops);

	if (unlikely(blk_queue_dead(q)))
		return;

	/*
	 * Some request_fn implementations, e.g. scsi_request_fn(), unlock
	 * the queue lock internally. As a result multiple threads may be
	 * running such a request function concurrently. Keep track of the
	 * number of active request_fn invocations such that blk_drain_queue()
	 * can wait until all these request_fn calls have finished.
	 */
	q->request_fn_active++;
	q->request_fn(q);
	q->request_fn_active--;
}