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
typedef  int /*<<< orphan*/  u64 ;
struct request_queue {int /*<<< orphan*/  backing_dev_info; int /*<<< orphan*/  mq_ops; int /*<<< orphan*/  queue_lock; } ;
struct request {int rq_flags; struct request* next_rq; struct request_queue* q; int /*<<< orphan*/  (* end_io ) (struct request*,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int RQF_DONTPREP ; 
 int RQF_QUEUED ; 
 int RQF_STATS ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __blk_put_request (struct request_queue*,struct request*) ; 
 int /*<<< orphan*/  blk_account_io_done (struct request*,int /*<<< orphan*/ ) ; 
 scalar_t__ blk_bidi_rq (struct request*) ; 
 int /*<<< orphan*/  blk_delete_timer (struct request*) ; 
 int /*<<< orphan*/  blk_queue_end_tag (struct request_queue*,struct request*) ; 
 int /*<<< orphan*/  blk_queued_rq (struct request*) ; 
 int /*<<< orphan*/  blk_rq_is_passthrough (struct request*) ; 
 int /*<<< orphan*/  blk_stat_add (struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_unprep_request (struct request*) ; 
 int /*<<< orphan*/  ktime_get_ns () ; 
 int /*<<< orphan*/  laptop_io_completion (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  laptop_mode ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rq_qos_done (struct request_queue*,struct request*) ; 
 int /*<<< orphan*/  stub1 (struct request*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void blk_finish_request(struct request *req, blk_status_t error)
{
	struct request_queue *q = req->q;
	u64 now = ktime_get_ns();

	lockdep_assert_held(req->q->queue_lock);
	WARN_ON_ONCE(q->mq_ops);

	if (req->rq_flags & RQF_STATS)
		blk_stat_add(req, now);

	if (req->rq_flags & RQF_QUEUED)
		blk_queue_end_tag(q, req);

	BUG_ON(blk_queued_rq(req));

	if (unlikely(laptop_mode) && !blk_rq_is_passthrough(req))
		laptop_io_completion(req->q->backing_dev_info);

	blk_delete_timer(req);

	if (req->rq_flags & RQF_DONTPREP)
		blk_unprep_request(req);

	blk_account_io_done(req, now);

	if (req->end_io) {
		rq_qos_done(q, req);
		req->end_io(req, error);
	} else {
		if (blk_bidi_rq(req))
			__blk_put_request(req->next_rq->q, req->next_rq);

		__blk_put_request(q, req);
	}
}