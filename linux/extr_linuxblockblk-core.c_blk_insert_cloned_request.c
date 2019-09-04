#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int /*<<< orphan*/  queue_lock; scalar_t__ mq_ops; } ;
struct request {int /*<<< orphan*/  cmd_flags; TYPE_1__* rq_disk; } ;
typedef  int /*<<< orphan*/  blk_status_t ;
struct TYPE_2__ {int /*<<< orphan*/  part0; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  BLK_STS_OK ; 
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int ELEVATOR_INSERT_BACK ; 
 int ELEVATOR_INSERT_FLUSH ; 
 int /*<<< orphan*/  __blk_run_queue (struct request_queue*) ; 
 int /*<<< orphan*/  add_acct_request (struct request_queue*,struct request*,int) ; 
 int /*<<< orphan*/  blk_account_io_start (struct request*,int) ; 
 scalar_t__ blk_cloned_rq_check_limits (struct request_queue*,struct request*) ; 
 int /*<<< orphan*/  blk_mq_request_issue_directly (struct request*) ; 
 int /*<<< orphan*/  blk_queue_dying (struct request_queue*) ; 
 scalar_t__ blk_queue_io_stat (struct request_queue*) ; 
 int /*<<< orphan*/  blk_queued_rq (struct request*) ; 
 int /*<<< orphan*/  blk_rq_bytes (struct request*) ; 
 scalar_t__ op_is_flush (int /*<<< orphan*/ ) ; 
 scalar_t__ should_fail_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

blk_status_t blk_insert_cloned_request(struct request_queue *q, struct request *rq)
{
	unsigned long flags;
	int where = ELEVATOR_INSERT_BACK;

	if (blk_cloned_rq_check_limits(q, rq))
		return BLK_STS_IOERR;

	if (rq->rq_disk &&
	    should_fail_request(&rq->rq_disk->part0, blk_rq_bytes(rq)))
		return BLK_STS_IOERR;

	if (q->mq_ops) {
		if (blk_queue_io_stat(q))
			blk_account_io_start(rq, true);
		/*
		 * Since we have a scheduler attached on the top device,
		 * bypass a potential scheduler on the bottom device for
		 * insert.
		 */
		return blk_mq_request_issue_directly(rq);
	}

	spin_lock_irqsave(q->queue_lock, flags);
	if (unlikely(blk_queue_dying(q))) {
		spin_unlock_irqrestore(q->queue_lock, flags);
		return BLK_STS_IOERR;
	}

	/*
	 * Submitting request must be dequeued before calling this function
	 * because it will be linked to another request_queue
	 */
	BUG_ON(blk_queued_rq(rq));

	if (op_is_flush(rq->cmd_flags))
		where = ELEVATOR_INSERT_FLUSH;

	add_acct_request(q, rq, where);
	if (where == ELEVATOR_INSERT_FLUSH)
		__blk_run_queue(q);
	spin_unlock_irqrestore(q->queue_lock, flags);

	return BLK_STS_OK;
}