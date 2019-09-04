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
struct request_queue {int dummy; } ;
struct request {int /*<<< orphan*/  mq_ctx; int /*<<< orphan*/  queuelist; } ;
struct blk_mq_hw_ctx {int /*<<< orphan*/  dispatch_from; int /*<<< orphan*/  ctx_map; struct request_queue* queue; } ;
struct blk_mq_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 struct blk_mq_ctx* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,struct blk_mq_ctx*) ; 
 struct request* blk_mq_dequeue_from_ctx (struct blk_mq_hw_ctx*,struct blk_mq_ctx*) ; 
 scalar_t__ blk_mq_dispatch_rq_list (struct request_queue*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  blk_mq_get_dispatch_budget (struct blk_mq_hw_ctx*) ; 
 struct blk_mq_ctx* blk_mq_next_ctx (struct blk_mq_hw_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_put_dispatch_budget (struct blk_mq_hw_ctx*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rq_list ; 
 int /*<<< orphan*/  sbitmap_any_bit_set (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void blk_mq_do_dispatch_ctx(struct blk_mq_hw_ctx *hctx)
{
	struct request_queue *q = hctx->queue;
	LIST_HEAD(rq_list);
	struct blk_mq_ctx *ctx = READ_ONCE(hctx->dispatch_from);

	do {
		struct request *rq;

		if (!sbitmap_any_bit_set(&hctx->ctx_map))
			break;

		if (!blk_mq_get_dispatch_budget(hctx))
			break;

		rq = blk_mq_dequeue_from_ctx(hctx, ctx);
		if (!rq) {
			blk_mq_put_dispatch_budget(hctx);
			break;
		}

		/*
		 * Now this rq owns the budget which has to be released
		 * if this rq won't be queued to driver via .queue_rq()
		 * in blk_mq_dispatch_rq_list().
		 */
		list_add(&rq->queuelist, &rq_list);

		/* round robin for fair dispatch */
		ctx = blk_mq_next_ctx(hctx, rq->mq_ctx);

	} while (blk_mq_dispatch_rq_list(q, &rq_list, true));

	WRITE_ONCE(hctx->dispatch_from, ctx);
}