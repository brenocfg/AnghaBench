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
struct request {int tag; int internal_tag; TYPE_1__* mq_ctx; int /*<<< orphan*/  q; } ;
struct blk_mq_hw_ctx {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  __blk_mq_put_driver_tag (struct blk_mq_hw_ctx*,struct request*) ; 
 struct blk_mq_hw_ctx* blk_mq_map_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void blk_mq_put_driver_tag(struct request *rq)
{
	struct blk_mq_hw_ctx *hctx;

	if (rq->tag == -1 || rq->internal_tag == -1)
		return;

	hctx = blk_mq_map_queue(rq->q, rq->mq_ctx->cpu);
	__blk_mq_put_driver_tag(hctx, rq);
}