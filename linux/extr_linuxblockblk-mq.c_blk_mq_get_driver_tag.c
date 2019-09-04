#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct request {int tag; int /*<<< orphan*/  rq_flags; int /*<<< orphan*/  internal_tag; TYPE_1__* mq_ctx; int /*<<< orphan*/  q; } ;
struct blk_mq_alloc_data {TYPE_3__* hctx; int /*<<< orphan*/  flags; int /*<<< orphan*/  q; } ;
struct TYPE_7__ {TYPE_2__* tags; int /*<<< orphan*/  nr_active; int /*<<< orphan*/  sched_tags; } ;
struct TYPE_6__ {struct request** rqs; } ;
struct TYPE_5__ {int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_MQ_REQ_NOWAIT ; 
 int /*<<< orphan*/  BLK_MQ_REQ_RESERVED ; 
 int /*<<< orphan*/  RQF_MQ_INFLIGHT ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int blk_mq_get_tag (struct blk_mq_alloc_data*) ; 
 TYPE_3__* blk_mq_map_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int blk_mq_tag_busy (TYPE_3__*) ; 
 scalar_t__ blk_mq_tag_is_reserved (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool blk_mq_get_driver_tag(struct request *rq)
{
	struct blk_mq_alloc_data data = {
		.q = rq->q,
		.hctx = blk_mq_map_queue(rq->q, rq->mq_ctx->cpu),
		.flags = BLK_MQ_REQ_NOWAIT,
	};
	bool shared;

	if (rq->tag != -1)
		goto done;

	if (blk_mq_tag_is_reserved(data.hctx->sched_tags, rq->internal_tag))
		data.flags |= BLK_MQ_REQ_RESERVED;

	shared = blk_mq_tag_busy(data.hctx);
	rq->tag = blk_mq_get_tag(&data);
	if (rq->tag >= 0) {
		if (shared) {
			rq->rq_flags |= RQF_MQ_INFLIGHT;
			atomic_inc(&data.hctx->nr_active);
		}
		data.hctx->tags->rqs[rq->tag] = rq;
	}

done:
	return rq->tag != -1;
}