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
struct request {int dummy; } ;
struct bfq_queue {scalar_t__ dispatched; struct request* next_rq; } ;
struct bfq_data {int /*<<< orphan*/  idle_slice_timer; struct bfq_queue* in_service_queue; } ;
typedef  enum bfqq_expiration { ____Placeholder_bfqq_expiration } bfqq_expiration ;

/* Variables and functions */
 int BFQQE_BUDGET_EXHAUSTED ; 
 int BFQQE_BUDGET_TIMEOUT ; 
 int BFQQE_NO_MORE_REQUESTS ; 
 scalar_t__ bfq_better_to_idle (struct bfq_queue*) ; 
 scalar_t__ bfq_bfqq_budget_left (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_bfqq_expire (struct bfq_data*,struct bfq_queue*,int,int) ; 
 int /*<<< orphan*/  bfq_bfqq_must_idle (struct bfq_queue*) ; 
 scalar_t__ bfq_bfqq_wait_request (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_clear_bfqq_wait_request (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_log (struct bfq_data*,char*) ; 
 int /*<<< orphan*/  bfq_log_bfqq (struct bfq_data*,struct bfq_queue*,char*) ; 
 scalar_t__ bfq_may_expire_for_budg_timeout (struct bfq_queue*) ; 
 scalar_t__ bfq_serv_to_charge (struct request*,struct bfq_queue*) ; 
 struct bfq_queue* bfq_set_in_service_queue (struct bfq_data*) ; 
 int /*<<< orphan*/  hrtimer_try_to_cancel (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct bfq_queue *bfq_select_queue(struct bfq_data *bfqd)
{
	struct bfq_queue *bfqq;
	struct request *next_rq;
	enum bfqq_expiration reason = BFQQE_BUDGET_TIMEOUT;

	bfqq = bfqd->in_service_queue;
	if (!bfqq)
		goto new_queue;

	bfq_log_bfqq(bfqd, bfqq, "select_queue: already in-service queue");

	/*
	 * Do not expire bfqq for budget timeout if bfqq may be about
	 * to enjoy device idling. The reason why, in this case, we
	 * prevent bfqq from expiring is the same as in the comments
	 * on the case where bfq_bfqq_must_idle() returns true, in
	 * bfq_completed_request().
	 */
	if (bfq_may_expire_for_budg_timeout(bfqq) &&
	    !bfq_bfqq_must_idle(bfqq))
		goto expire;

check_queue:
	/*
	 * This loop is rarely executed more than once. Even when it
	 * happens, it is much more convenient to re-execute this loop
	 * than to return NULL and trigger a new dispatch to get a
	 * request served.
	 */
	next_rq = bfqq->next_rq;
	/*
	 * If bfqq has requests queued and it has enough budget left to
	 * serve them, keep the queue, otherwise expire it.
	 */
	if (next_rq) {
		if (bfq_serv_to_charge(next_rq, bfqq) >
			bfq_bfqq_budget_left(bfqq)) {
			/*
			 * Expire the queue for budget exhaustion,
			 * which makes sure that the next budget is
			 * enough to serve the next request, even if
			 * it comes from the fifo expired path.
			 */
			reason = BFQQE_BUDGET_EXHAUSTED;
			goto expire;
		} else {
			/*
			 * The idle timer may be pending because we may
			 * not disable disk idling even when a new request
			 * arrives.
			 */
			if (bfq_bfqq_wait_request(bfqq)) {
				/*
				 * If we get here: 1) at least a new request
				 * has arrived but we have not disabled the
				 * timer because the request was too small,
				 * 2) then the block layer has unplugged
				 * the device, causing the dispatch to be
				 * invoked.
				 *
				 * Since the device is unplugged, now the
				 * requests are probably large enough to
				 * provide a reasonable throughput.
				 * So we disable idling.
				 */
				bfq_clear_bfqq_wait_request(bfqq);
				hrtimer_try_to_cancel(&bfqd->idle_slice_timer);
			}
			goto keep_queue;
		}
	}

	/*
	 * No requests pending. However, if the in-service queue is idling
	 * for a new request, or has requests waiting for a completion and
	 * may idle after their completion, then keep it anyway.
	 */
	if (bfq_bfqq_wait_request(bfqq) ||
	    (bfqq->dispatched != 0 && bfq_better_to_idle(bfqq))) {
		bfqq = NULL;
		goto keep_queue;
	}

	reason = BFQQE_NO_MORE_REQUESTS;
expire:
	bfq_bfqq_expire(bfqd, bfqq, false, reason);
new_queue:
	bfqq = bfq_set_in_service_queue(bfqd);
	if (bfqq) {
		bfq_log_bfqq(bfqd, bfqq, "select_queue: checking new queue");
		goto check_queue;
	}
keep_queue:
	if (bfqq)
		bfq_log_bfqq(bfqd, bfqq, "select_queue: returned this queue");
	else
		bfq_log(bfqd, "select_queue: no queue returned");

	return bfqq;
}