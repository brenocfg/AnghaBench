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
typedef  int u32 ;
struct request_queue {scalar_t__ mq_ops; } ;
struct request {int tag; TYPE_1__* mq_ctx; struct request_queue* q; } ;
struct blk_mq_hw_ctx {int queue_num; } ;
struct TYPE_2__ {int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 int BLK_MQ_UNIQUE_TAG_BITS ; 
 int BLK_MQ_UNIQUE_TAG_MASK ; 
 struct blk_mq_hw_ctx* blk_mq_map_queue (struct request_queue*,int /*<<< orphan*/ ) ; 

u32 blk_mq_unique_tag(struct request *rq)
{
	struct request_queue *q = rq->q;
	struct blk_mq_hw_ctx *hctx;
	int hwq = 0;

	if (q->mq_ops) {
		hctx = blk_mq_map_queue(q, rq->mq_ctx->cpu);
		hwq = hctx->queue_num;
	}

	return (hwq << BLK_MQ_UNIQUE_TAG_BITS) |
		(rq->tag & BLK_MQ_UNIQUE_TAG_MASK);
}