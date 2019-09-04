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
struct request_queue {int /*<<< orphan*/  queue_lock; scalar_t__ mq_ops; } ;
struct request {int /*<<< orphan*/  rq_flags; int /*<<< orphan*/ * end_io; struct gendisk* rq_disk; } ;
struct gendisk {int dummy; } ;
typedef  int /*<<< orphan*/  rq_end_io_fn ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int ELEVATOR_INSERT_BACK ; 
 int ELEVATOR_INSERT_FRONT ; 
 int /*<<< orphan*/  RQF_QUIET ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __blk_end_request_all (struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __blk_run_queue (struct request_queue*) ; 
 int /*<<< orphan*/  __elv_add_request (struct request_queue*,struct request*,int) ; 
 int /*<<< orphan*/  blk_mq_sched_insert_request (struct request*,int,int,int) ; 
 int /*<<< orphan*/  blk_queue_dying (struct request_queue*) ; 
 int /*<<< orphan*/  blk_rq_is_passthrough (struct request*) ; 
 int irqs_disabled () ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void blk_execute_rq_nowait(struct request_queue *q, struct gendisk *bd_disk,
			   struct request *rq, int at_head,
			   rq_end_io_fn *done)
{
	int where = at_head ? ELEVATOR_INSERT_FRONT : ELEVATOR_INSERT_BACK;

	WARN_ON(irqs_disabled());
	WARN_ON(!blk_rq_is_passthrough(rq));

	rq->rq_disk = bd_disk;
	rq->end_io = done;

	/*
	 * don't check dying flag for MQ because the request won't
	 * be reused after dying flag is set
	 */
	if (q->mq_ops) {
		blk_mq_sched_insert_request(rq, at_head, true, false);
		return;
	}

	spin_lock_irq(q->queue_lock);

	if (unlikely(blk_queue_dying(q))) {
		rq->rq_flags |= RQF_QUIET;
		__blk_end_request_all(rq, BLK_STS_IOERR);
		spin_unlock_irq(q->queue_lock);
		return;
	}

	__elv_add_request(q, rq, where);
	__blk_run_queue(q);
	spin_unlock_irq(q->queue_lock);
}