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
struct show_busy_params {scalar_t__ hctx; int /*<<< orphan*/  m; } ;
struct request {int /*<<< orphan*/  queuelist; TYPE_1__* mq_ctx; int /*<<< orphan*/  q; } ;
struct TYPE_2__ {int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 scalar_t__ MQ_RQ_IDLE ; 
 int /*<<< orphan*/  __blk_mq_debugfs_rq_show (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ blk_mq_map_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ blk_mq_rq_state (struct request*) ; 
 int /*<<< orphan*/  list_entry_rq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hctx_show_busy_rq(struct request *rq, void *data, bool reserved)
{
	const struct show_busy_params *params = data;

	if (blk_mq_map_queue(rq->q, rq->mq_ctx->cpu) == params->hctx &&
	    blk_mq_rq_state(rq) != MQ_RQ_IDLE)
		__blk_mq_debugfs_rq_show(params->m,
					 list_entry_rq(&rq->queuelist));
}