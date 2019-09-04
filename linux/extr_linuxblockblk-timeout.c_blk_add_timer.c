#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned long expires; } ;
struct request_queue {TYPE_1__ timeout; int /*<<< orphan*/  timeout_list; int /*<<< orphan*/  mq_ops; scalar_t__ rq_timeout; int /*<<< orphan*/  rq_timed_out_fn; int /*<<< orphan*/  queue_lock; } ;
struct request {struct request_queue* q; int /*<<< orphan*/  timeout_list; scalar_t__ timeout; int /*<<< orphan*/  rq_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int HZ ; 
 int /*<<< orphan*/  RQF_TIMED_OUT ; 
 int /*<<< orphan*/  blk_rq_deadline (struct request*) ; 
 int /*<<< orphan*/  blk_rq_set_deadline (struct request*,scalar_t__) ; 
 unsigned long blk_rq_timeout (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (TYPE_1__*,unsigned long) ; 
 int /*<<< orphan*/  round_jiffies_up (int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  timer_pending (TYPE_1__*) ; 

void blk_add_timer(struct request *req)
{
	struct request_queue *q = req->q;
	unsigned long expiry;

	if (!q->mq_ops)
		lockdep_assert_held(q->queue_lock);

	/* blk-mq has its own handler, so we don't need ->rq_timed_out_fn */
	if (!q->mq_ops && !q->rq_timed_out_fn)
		return;

	BUG_ON(!list_empty(&req->timeout_list));

	/*
	 * Some LLDs, like scsi, peek at the timeout to prevent a
	 * command from being retried forever.
	 */
	if (!req->timeout)
		req->timeout = q->rq_timeout;

	req->rq_flags &= ~RQF_TIMED_OUT;
	blk_rq_set_deadline(req, jiffies + req->timeout);

	/*
	 * Only the non-mq case needs to add the request to a protected list.
	 * For the mq case we simply scan the tag map.
	 */
	if (!q->mq_ops)
		list_add_tail(&req->timeout_list, &req->q->timeout_list);

	/*
	 * If the timer isn't already pending or this timeout is earlier
	 * than an existing one, modify the timer. Round up to next nearest
	 * second.
	 */
	expiry = blk_rq_timeout(round_jiffies_up(blk_rq_deadline(req)));

	if (!timer_pending(&q->timeout) ||
	    time_before(expiry, q->timeout.expires)) {
		unsigned long diff = q->timeout.expires - expiry;

		/*
		 * Due to added timer slack to group timers, the timer
		 * will often be a little in front of what we asked for.
		 * So apply some tolerance here too, otherwise we keep
		 * modifying the timer because expires for value X
		 * will be X + something.
		 */
		if (!timer_pending(&q->timeout) || (diff >= HZ / 2))
			mod_timer(&q->timeout, expiry);
	}

}