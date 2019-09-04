#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int dummy; } ;
struct list_head {int dummy; } ;
struct elevator_queue {TYPE_3__* type; } ;
struct blk_mq_hw_ctx {int /*<<< orphan*/  dispatch_busy; TYPE_4__* queue; } ;
struct blk_mq_ctx {int /*<<< orphan*/  cpu; } ;
struct TYPE_8__ {struct elevator_queue* elevator; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* insert_requests ) (struct blk_mq_hw_ctx*,struct list_head*,int) ;} ;
struct TYPE_6__ {TYPE_1__ mq; } ;
struct TYPE_7__ {TYPE_2__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_insert_requests (struct blk_mq_hw_ctx*,struct blk_mq_ctx*,struct list_head*) ; 
 struct blk_mq_hw_ctx* blk_mq_map_queue (struct request_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_run_hw_queue (struct blk_mq_hw_ctx*,int) ; 
 int /*<<< orphan*/  blk_mq_try_issue_list_directly (struct blk_mq_hw_ctx*,struct list_head*) ; 
 scalar_t__ list_empty (struct list_head*) ; 
 int /*<<< orphan*/  stub1 (struct blk_mq_hw_ctx*,struct list_head*,int) ; 

void blk_mq_sched_insert_requests(struct request_queue *q,
				  struct blk_mq_ctx *ctx,
				  struct list_head *list, bool run_queue_async)
{
	struct blk_mq_hw_ctx *hctx = blk_mq_map_queue(q, ctx->cpu);
	struct elevator_queue *e = hctx->queue->elevator;

	if (e && e->type->ops.mq.insert_requests)
		e->type->ops.mq.insert_requests(hctx, list, false);
	else {
		/*
		 * try to issue requests directly if the hw queue isn't
		 * busy in case of 'none' scheduler, and this way may save
		 * us one extra enqueue & dequeue to sw queue.
		 */
		if (!hctx->dispatch_busy && !e && !run_queue_async) {
			blk_mq_try_issue_list_directly(hctx, list);
			if (list_empty(list))
				return;
		}
		blk_mq_insert_requests(hctx, ctx, list);
	}

	blk_mq_run_hw_queue(hctx, run_queue_async);
}