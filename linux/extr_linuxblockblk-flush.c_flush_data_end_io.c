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
struct request_queue {int /*<<< orphan*/  queue_lock; } ;
struct request {int /*<<< orphan*/  rq_flags; struct request_queue* q; } ;
struct blk_flush_queue {int dummy; } ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  REQ_FSEQ_DATA ; 
 int /*<<< orphan*/  RQF_STARTED ; 
 scalar_t__ blk_flush_complete_seq (struct request*,struct blk_flush_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct blk_flush_queue* blk_get_flush_queue (struct request_queue*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_run_queue_async (struct request_queue*) ; 
 int /*<<< orphan*/  elv_completed_request (struct request_queue*,struct request*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void flush_data_end_io(struct request *rq, blk_status_t error)
{
	struct request_queue *q = rq->q;
	struct blk_flush_queue *fq = blk_get_flush_queue(q, NULL);

	lockdep_assert_held(q->queue_lock);

	/*
	 * Updating q->in_flight[] here for making this tag usable
	 * early. Because in blk_queue_start_tag(),
	 * q->in_flight[BLK_RW_ASYNC] is used to limit async I/O and
	 * reserve tags for sync I/O.
	 *
	 * More importantly this way can avoid the following I/O
	 * deadlock:
	 *
	 * - suppose there are 40 fua requests comming to flush queue
	 *   and queue depth is 31
	 * - 30 rqs are scheduled then blk_queue_start_tag() can't alloc
	 *   tag for async I/O any more
	 * - all the 30 rqs are completed before FLUSH_PENDING_TIMEOUT
	 *   and flush_data_end_io() is called
	 * - the other rqs still can't go ahead if not updating
	 *   q->in_flight[BLK_RW_ASYNC] here, meantime these rqs
	 *   are held in flush data queue and make no progress of
	 *   handling post flush rq
	 * - only after the post flush rq is handled, all these rqs
	 *   can be completed
	 */

	elv_completed_request(q, rq);

	/* for avoiding double accounting */
	rq->rq_flags &= ~RQF_STARTED;

	/*
	 * After populating an empty queue, kick it to avoid stall.  Read
	 * the comment in flush_end_io().
	 */
	if (blk_flush_complete_seq(rq, fq, REQ_FSEQ_DATA, error))
		blk_run_queue_async(q);
}