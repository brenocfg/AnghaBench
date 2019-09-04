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
struct request_queue {scalar_t__ dma_drain_size; int /*<<< orphan*/  queue_flags; } ;
struct request {int /*<<< orphan*/  nr_phys_segments; int /*<<< orphan*/  state; int /*<<< orphan*/  rq_flags; int /*<<< orphan*/  io_start_time_ns; struct request_queue* q; } ;

/* Variables and functions */
 scalar_t__ MQ_RQ_IDLE ; 
 int /*<<< orphan*/  MQ_RQ_IN_FLIGHT ; 
 int /*<<< orphan*/  QUEUE_FLAG_STATS ; 
 int /*<<< orphan*/  RQF_STATS ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_add_timer (struct request*) ; 
 scalar_t__ blk_mq_rq_state (struct request*) ; 
 int /*<<< orphan*/  blk_mq_sched_started_request (struct request*) ; 
 scalar_t__ blk_rq_bytes (struct request*) ; 
 int /*<<< orphan*/  ktime_get_ns () ; 
 int /*<<< orphan*/  rq_qos_issue (struct request_queue*,struct request*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_block_rq_issue (struct request_queue*,struct request*) ; 

void blk_mq_start_request(struct request *rq)
{
	struct request_queue *q = rq->q;

	blk_mq_sched_started_request(rq);

	trace_block_rq_issue(q, rq);

	if (test_bit(QUEUE_FLAG_STATS, &q->queue_flags)) {
		rq->io_start_time_ns = ktime_get_ns();
#ifdef CONFIG_BLK_DEV_THROTTLING_LOW
		rq->throtl_size = blk_rq_sectors(rq);
#endif
		rq->rq_flags |= RQF_STATS;
		rq_qos_issue(q, rq);
	}

	WARN_ON_ONCE(blk_mq_rq_state(rq) != MQ_RQ_IDLE);

	blk_add_timer(rq);
	WRITE_ONCE(rq->state, MQ_RQ_IN_FLIGHT);

	if (q->dma_drain_size && blk_rq_bytes(rq)) {
		/*
		 * Make sure space for the drain appears.  We know we can do
		 * this because max_hw_segments has been adjusted to be one
		 * fewer than the device can handle.
		 */
		rq->nr_phys_segments++;
	}
}