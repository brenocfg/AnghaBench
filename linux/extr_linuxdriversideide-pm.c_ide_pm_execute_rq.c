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
struct request_queue {int /*<<< orphan*/  queue_lock; } ;
struct request {int /*<<< orphan*/  rq_flags; int /*<<< orphan*/  end_io; int /*<<< orphan*/ * end_io_data; struct request_queue* q; } ;
struct TYPE_2__ {int result; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_OK ; 
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int EIO ; 
 int /*<<< orphan*/  ELEVATOR_INSERT_FRONT ; 
 int ENXIO ; 
 int /*<<< orphan*/  RQF_QUIET ; 
 int /*<<< orphan*/  __blk_end_request_all (struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __blk_run_queue_uncond (struct request_queue*) ; 
 int /*<<< orphan*/  __elv_add_request (struct request_queue*,struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_dying (struct request_queue*) ; 
 int /*<<< orphan*/  ide_end_sync_rq ; 
 TYPE_1__* scsi_req (struct request*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait ; 
 int /*<<< orphan*/  wait_for_completion_io (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ide_pm_execute_rq(struct request *rq)
{
	struct request_queue *q = rq->q;
	DECLARE_COMPLETION_ONSTACK(wait);

	rq->end_io_data = &wait;
	rq->end_io = ide_end_sync_rq;

	spin_lock_irq(q->queue_lock);
	if (unlikely(blk_queue_dying(q))) {
		rq->rq_flags |= RQF_QUIET;
		scsi_req(rq)->result = -ENXIO;
		__blk_end_request_all(rq, BLK_STS_OK);
		spin_unlock_irq(q->queue_lock);
		return -ENXIO;
	}
	__elv_add_request(q, rq, ELEVATOR_INSERT_FRONT);
	__blk_run_queue_uncond(q);
	spin_unlock_irq(q->queue_lock);

	wait_for_completion_io(&wait);

	return scsi_req(rq)->result ? -EIO : 0;
}