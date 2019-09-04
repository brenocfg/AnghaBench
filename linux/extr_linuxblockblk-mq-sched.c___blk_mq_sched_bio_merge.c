#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct request_queue {struct elevator_queue* elevator; } ;
struct elevator_queue {TYPE_3__* type; } ;
struct blk_mq_hw_ctx {int flags; } ;
struct blk_mq_ctx {int /*<<< orphan*/  lock; int /*<<< orphan*/  rq_list; int /*<<< orphan*/  cpu; } ;
struct bio {int dummy; } ;
struct TYPE_4__ {int (* bio_merge ) (struct blk_mq_hw_ctx*,struct bio*) ;} ;
struct TYPE_5__ {TYPE_1__ mq; } ;
struct TYPE_6__ {TYPE_2__ ops; } ;

/* Variables and functions */
 int BLK_MQ_F_SHOULD_MERGE ; 
 int blk_mq_attempt_merge (struct request_queue*,struct blk_mq_ctx*,struct bio*) ; 
 struct blk_mq_ctx* blk_mq_get_ctx (struct request_queue*) ; 
 struct blk_mq_hw_ctx* blk_mq_map_queue (struct request_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_put_ctx (struct blk_mq_ctx*) ; 
 int /*<<< orphan*/  list_empty_careful (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct blk_mq_hw_ctx*,struct bio*) ; 

bool __blk_mq_sched_bio_merge(struct request_queue *q, struct bio *bio)
{
	struct elevator_queue *e = q->elevator;
	struct blk_mq_ctx *ctx = blk_mq_get_ctx(q);
	struct blk_mq_hw_ctx *hctx = blk_mq_map_queue(q, ctx->cpu);
	bool ret = false;

	if (e && e->type->ops.mq.bio_merge) {
		blk_mq_put_ctx(ctx);
		return e->type->ops.mq.bio_merge(hctx, bio);
	}

	if ((hctx->flags & BLK_MQ_F_SHOULD_MERGE) &&
			!list_empty_careful(&ctx->rq_list)) {
		/* default per sw-queue merge */
		spin_lock(&ctx->lock);
		ret = blk_mq_attempt_merge(q, ctx, bio);
		spin_unlock(&ctx->lock);
	}

	blk_mq_put_ctx(ctx);
	return ret;
}