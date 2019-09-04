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
struct TYPE_2__ {int /*<<< orphan*/  budget; } ;
struct bfq_queue {int wr_coeff; scalar_t__ wr_cur_max_time; TYPE_1__ entity; scalar_t__ last_wr_start_finish; scalar_t__ budget_timeout; } ;
struct bfq_data {int budgets_assigned; scalar_t__ bfq_wr_rt_max_time; struct bfq_queue* in_service_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfq_clear_bfqq_fifo_expire (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_log_bfqq (struct bfq_data*,struct bfq_queue*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfq_set_budget_timeout (struct bfq_data*,struct bfq_queue*) ; 
 scalar_t__ jiffies ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 scalar_t__ time_is_before_jiffies (scalar_t__) ; 

__attribute__((used)) static void __bfq_set_in_service_queue(struct bfq_data *bfqd,
				       struct bfq_queue *bfqq)
{
	if (bfqq) {
		bfq_clear_bfqq_fifo_expire(bfqq);

		bfqd->budgets_assigned = (bfqd->budgets_assigned * 7 + 256) / 8;

		if (time_is_before_jiffies(bfqq->last_wr_start_finish) &&
		    bfqq->wr_coeff > 1 &&
		    bfqq->wr_cur_max_time == bfqd->bfq_wr_rt_max_time &&
		    time_is_before_jiffies(bfqq->budget_timeout)) {
			/*
			 * For soft real-time queues, move the start
			 * of the weight-raising period forward by the
			 * time the queue has not received any
			 * service. Otherwise, a relatively long
			 * service delay is likely to cause the
			 * weight-raising period of the queue to end,
			 * because of the short duration of the
			 * weight-raising period of a soft real-time
			 * queue.  It is worth noting that this move
			 * is not so dangerous for the other queues,
			 * because soft real-time queues are not
			 * greedy.
			 *
			 * To not add a further variable, we use the
			 * overloaded field budget_timeout to
			 * determine for how long the queue has not
			 * received service, i.e., how much time has
			 * elapsed since the queue expired. However,
			 * this is a little imprecise, because
			 * budget_timeout is set to jiffies if bfqq
			 * not only expires, but also remains with no
			 * request.
			 */
			if (time_after(bfqq->budget_timeout,
				       bfqq->last_wr_start_finish))
				bfqq->last_wr_start_finish +=
					jiffies - bfqq->budget_timeout;
			else
				bfqq->last_wr_start_finish = jiffies;
		}

		bfq_set_budget_timeout(bfqd, bfqq);
		bfq_log_bfqq(bfqd, bfqq,
			     "set_in_service_queue, cur-budget = %d",
			     bfqq->entity.budget);
	}

	bfqd->in_service_queue = bfqq;
}