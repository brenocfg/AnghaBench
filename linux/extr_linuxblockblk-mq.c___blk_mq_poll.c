#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct request_queue {TYPE_1__* mq_ops; } ;
struct request {int /*<<< orphan*/  tag; } ;
struct blk_mq_hw_ctx {int /*<<< orphan*/  poll_success; int /*<<< orphan*/  poll_invoked; int /*<<< orphan*/  poll_considered; struct request_queue* queue; } ;
struct TYPE_5__ {long state; } ;
struct TYPE_4__ {int (* poll ) (struct blk_mq_hw_ctx*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 long TASK_RUNNING ; 
 int /*<<< orphan*/  __set_current_state (long) ; 
 scalar_t__ blk_mq_poll_hybrid_sleep (struct request_queue*,struct blk_mq_hw_ctx*,struct request*) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  need_resched () ; 
 int /*<<< orphan*/  set_current_state (long) ; 
 scalar_t__ signal_pending_state (long,TYPE_2__*) ; 
 int stub1 (struct blk_mq_hw_ctx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool __blk_mq_poll(struct blk_mq_hw_ctx *hctx, struct request *rq)
{
	struct request_queue *q = hctx->queue;
	long state;

	/*
	 * If we sleep, have the caller restart the poll loop to reset
	 * the state. Like for the other success return cases, the
	 * caller is responsible for checking if the IO completed. If
	 * the IO isn't complete, we'll get called again and will go
	 * straight to the busy poll loop.
	 */
	if (blk_mq_poll_hybrid_sleep(q, hctx, rq))
		return true;

	hctx->poll_considered++;

	state = current->state;
	while (!need_resched()) {
		int ret;

		hctx->poll_invoked++;

		ret = q->mq_ops->poll(hctx, rq->tag);
		if (ret > 0) {
			hctx->poll_success++;
			set_current_state(TASK_RUNNING);
			return true;
		}

		if (signal_pending_state(state, current))
			set_current_state(TASK_RUNNING);

		if (current->state == TASK_RUNNING)
			return true;
		if (ret < 0)
			break;
		cpu_relax();
	}

	__set_current_state(TASK_RUNNING);
	return false;
}