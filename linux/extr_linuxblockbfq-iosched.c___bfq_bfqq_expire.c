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
struct bfq_queue {scalar_t__ dispatched; int /*<<< orphan*/  budget_timeout; int /*<<< orphan*/  sort_list; } ;
struct bfq_data {int dummy; } ;

/* Variables and functions */
 scalar_t__ BFQQ_SEEKY (struct bfq_queue*) ; 
 scalar_t__ RB_EMPTY_ROOT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __bfq_bfqd_reset_in_service (struct bfq_data*) ; 
 scalar_t__ bfq_bfqq_coop (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_del_bfqq_busy (struct bfq_data*,struct bfq_queue*,int) ; 
 int /*<<< orphan*/  bfq_mark_bfqq_split_coop (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_pos_tree_add_move (struct bfq_data*,struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_requeue_bfqq (struct bfq_data*,struct bfq_queue*,int) ; 
 int /*<<< orphan*/  jiffies ; 

__attribute__((used)) static void __bfq_bfqq_expire(struct bfq_data *bfqd, struct bfq_queue *bfqq)
{
	/*
	 * If this bfqq is shared between multiple processes, check
	 * to make sure that those processes are still issuing I/Os
	 * within the mean seek distance. If not, it may be time to
	 * break the queues apart again.
	 */
	if (bfq_bfqq_coop(bfqq) && BFQQ_SEEKY(bfqq))
		bfq_mark_bfqq_split_coop(bfqq);

	if (RB_EMPTY_ROOT(&bfqq->sort_list)) {
		if (bfqq->dispatched == 0)
			/*
			 * Overloading budget_timeout field to store
			 * the time at which the queue remains with no
			 * backlog and no outstanding request; used by
			 * the weight-raising mechanism.
			 */
			bfqq->budget_timeout = jiffies;

		bfq_del_bfqq_busy(bfqd, bfqq, true);
	} else {
		bfq_requeue_bfqq(bfqd, bfqq, true);
		/*
		 * Resort priority tree of potential close cooperators.
		 */
		bfq_pos_tree_add_move(bfqd, bfqq);
	}

	/*
	 * All in-service entities must have been properly deactivated
	 * or requeued before executing the next function, which
	 * resets all in-service entites as no more in service.
	 */
	__bfq_bfqd_reset_in_service(bfqd);
}