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
struct request {TYPE_1__* q; int /*<<< orphan*/  rq_flags; int /*<<< orphan*/  io_start_time_ns; } ;
struct TYPE_2__ {int /*<<< orphan*/  queue_flags; int /*<<< orphan*/  mq_ops; int /*<<< orphan*/  queue_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QUEUE_FLAG_STATS ; 
 int /*<<< orphan*/  RQF_STATS ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_add_timer (struct request*) ; 
 int /*<<< orphan*/  blk_dequeue_request (struct request*) ; 
 int /*<<< orphan*/  blk_rq_is_complete (struct request*) ; 
 int /*<<< orphan*/  ktime_get_ns () ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rq_qos_issue (TYPE_1__*,struct request*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void blk_start_request(struct request *req)
{
	lockdep_assert_held(req->q->queue_lock);
	WARN_ON_ONCE(req->q->mq_ops);

	blk_dequeue_request(req);

	if (test_bit(QUEUE_FLAG_STATS, &req->q->queue_flags)) {
		req->io_start_time_ns = ktime_get_ns();
#ifdef CONFIG_BLK_DEV_THROTTLING_LOW
		req->throtl_size = blk_rq_sectors(req);
#endif
		req->rq_flags |= RQF_STATS;
		rq_qos_issue(req->q, req);
	}

	BUG_ON(blk_rq_is_complete(req));
	blk_add_timer(req);
}