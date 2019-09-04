#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct request_queue {struct elevator_queue* elevator; } ;
struct TYPE_9__ {int /*<<< orphan*/ * icq; } ;
struct request {int /*<<< orphan*/  rq_flags; TYPE_1__ elv; } ;
struct elevator_queue {TYPE_4__* type; } ;
struct blk_mq_alloc_data {int flags; TYPE_5__* hctx; TYPE_6__* ctx; struct request_queue* q; } ;
struct bio {int dummy; } ;
struct TYPE_14__ {int /*<<< orphan*/  cpu; } ;
struct TYPE_13__ {int /*<<< orphan*/  queued; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* prepare_request ) (struct request*,struct bio*) ;int /*<<< orphan*/  (* limit_depth ) (unsigned int,struct blk_mq_alloc_data*) ;} ;
struct TYPE_11__ {TYPE_2__ mq; } ;
struct TYPE_12__ {TYPE_3__ ops; scalar_t__ icq_cache; } ;

/* Variables and functions */
 int BLK_MQ_REQ_INTERNAL ; 
 int BLK_MQ_REQ_NOWAIT ; 
 int BLK_MQ_REQ_RESERVED ; 
 unsigned int BLK_MQ_TAG_FAIL ; 
 unsigned int REQ_NOWAIT ; 
 int /*<<< orphan*/  RQF_ELVPRIV ; 
 TYPE_6__* blk_mq_get_ctx (struct request_queue*) ; 
 unsigned int blk_mq_get_tag (struct blk_mq_alloc_data*) ; 
 TYPE_5__* blk_mq_map_queue (struct request_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_put_ctx (TYPE_6__*) ; 
 struct request* blk_mq_rq_ctx_init (struct blk_mq_alloc_data*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  blk_mq_sched_assign_ioc (struct request*,struct bio*) ; 
 int /*<<< orphan*/  blk_mq_tag_busy (TYPE_5__*) ; 
 int /*<<< orphan*/  blk_queue_enter_live (struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_exit (struct request_queue*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  op_is_flush (unsigned int) ; 
 scalar_t__ rq_ioc (struct bio*) ; 
 int /*<<< orphan*/  stub1 (unsigned int,struct blk_mq_alloc_data*) ; 
 int /*<<< orphan*/  stub2 (struct request*,struct bio*) ; 

__attribute__((used)) static struct request *blk_mq_get_request(struct request_queue *q,
		struct bio *bio, unsigned int op,
		struct blk_mq_alloc_data *data)
{
	struct elevator_queue *e = q->elevator;
	struct request *rq;
	unsigned int tag;
	bool put_ctx_on_error = false;

	blk_queue_enter_live(q);
	data->q = q;
	if (likely(!data->ctx)) {
		data->ctx = blk_mq_get_ctx(q);
		put_ctx_on_error = true;
	}
	if (likely(!data->hctx))
		data->hctx = blk_mq_map_queue(q, data->ctx->cpu);
	if (op & REQ_NOWAIT)
		data->flags |= BLK_MQ_REQ_NOWAIT;

	if (e) {
		data->flags |= BLK_MQ_REQ_INTERNAL;

		/*
		 * Flush requests are special and go directly to the
		 * dispatch list. Don't include reserved tags in the
		 * limiting, as it isn't useful.
		 */
		if (!op_is_flush(op) && e->type->ops.mq.limit_depth &&
		    !(data->flags & BLK_MQ_REQ_RESERVED))
			e->type->ops.mq.limit_depth(op, data);
	} else {
		blk_mq_tag_busy(data->hctx);
	}

	tag = blk_mq_get_tag(data);
	if (tag == BLK_MQ_TAG_FAIL) {
		if (put_ctx_on_error) {
			blk_mq_put_ctx(data->ctx);
			data->ctx = NULL;
		}
		blk_queue_exit(q);
		return NULL;
	}

	rq = blk_mq_rq_ctx_init(data, tag, op);
	if (!op_is_flush(op)) {
		rq->elv.icq = NULL;
		if (e && e->type->ops.mq.prepare_request) {
			if (e->type->icq_cache && rq_ioc(bio))
				blk_mq_sched_assign_ioc(rq, bio);

			e->type->ops.mq.prepare_request(rq, bio);
			rq->rq_flags |= RQF_ELVPRIV;
		}
	}
	data->hctx->queued++;
	return rq;
}