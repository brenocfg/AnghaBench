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
struct request_queue {int /*<<< orphan*/  queue_flags; } ;
struct request {int /*<<< orphan*/  mq_hctx; int /*<<< orphan*/ * end_io_data; int /*<<< orphan*/  cmd_flags; } ;
struct gendisk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QUEUE_FLAG_POLL ; 
 int /*<<< orphan*/  REQ_HIPRI ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  blk_execute_rq_nowait (struct request_queue*,struct gendisk*,struct request*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_poll (struct request_queue*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  completion_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  nvme_end_sync_rq ; 
 int /*<<< orphan*/  request_to_qc_t (int /*<<< orphan*/ ,struct request*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static void nvme_execute_rq_polled(struct request_queue *q,
		struct gendisk *bd_disk, struct request *rq, int at_head)
{
	DECLARE_COMPLETION_ONSTACK(wait);

	WARN_ON_ONCE(!test_bit(QUEUE_FLAG_POLL, &q->queue_flags));

	rq->cmd_flags |= REQ_HIPRI;
	rq->end_io_data = &wait;
	blk_execute_rq_nowait(q, bd_disk, rq, at_head, nvme_end_sync_rq);

	while (!completion_done(&wait)) {
		blk_poll(q, request_to_qc_t(rq->mq_hctx, rq), true);
		cond_resched();
	}
}