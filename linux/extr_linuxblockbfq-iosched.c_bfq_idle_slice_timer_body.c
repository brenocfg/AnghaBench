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
struct bfq_queue {scalar_t__* queued; struct bfq_data* bfqd; } ;
struct bfq_data {int /*<<< orphan*/  lock; struct bfq_queue* in_service_queue; } ;
typedef  enum bfqq_expiration { ____Placeholder_bfqq_expiration } bfqq_expiration ;

/* Variables and functions */
 int BFQQE_BUDGET_TIMEOUT ; 
 int BFQQE_TOO_IDLE ; 
 scalar_t__ bfq_bfqq_budget_timeout (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_bfqq_expire (struct bfq_data*,struct bfq_queue*,int,int) ; 
 int /*<<< orphan*/  bfq_clear_bfqq_wait_request (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_schedule_dispatch (struct bfq_data*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void bfq_idle_slice_timer_body(struct bfq_queue *bfqq)
{
	struct bfq_data *bfqd = bfqq->bfqd;
	enum bfqq_expiration reason;
	unsigned long flags;

	spin_lock_irqsave(&bfqd->lock, flags);
	bfq_clear_bfqq_wait_request(bfqq);

	if (bfqq != bfqd->in_service_queue) {
		spin_unlock_irqrestore(&bfqd->lock, flags);
		return;
	}

	if (bfq_bfqq_budget_timeout(bfqq))
		/*
		 * Also here the queue can be safely expired
		 * for budget timeout without wasting
		 * guarantees
		 */
		reason = BFQQE_BUDGET_TIMEOUT;
	else if (bfqq->queued[0] == 0 && bfqq->queued[1] == 0)
		/*
		 * The queue may not be empty upon timer expiration,
		 * because we may not disable the timer when the
		 * first request of the in-service queue arrives
		 * during disk idling.
		 */
		reason = BFQQE_TOO_IDLE;
	else
		goto schedule_dispatch;

	bfq_bfqq_expire(bfqd, bfqq, true, reason);

schedule_dispatch:
	spin_unlock_irqrestore(&bfqd->lock, flags);
	bfq_schedule_dispatch(bfqd);
}