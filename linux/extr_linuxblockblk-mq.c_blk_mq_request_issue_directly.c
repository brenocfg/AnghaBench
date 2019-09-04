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
struct request {int /*<<< orphan*/  q; struct blk_mq_ctx* mq_ctx; } ;
struct blk_mq_hw_ctx {int dummy; } ;
struct blk_mq_ctx {int /*<<< orphan*/  cpu; } ;
typedef  int /*<<< orphan*/  blk_status_t ;
typedef  int /*<<< orphan*/  blk_qc_t ;

/* Variables and functions */
 int /*<<< orphan*/  __blk_mq_try_issue_directly (struct blk_mq_hw_ctx*,struct request*,int /*<<< orphan*/ *,int) ; 
 struct blk_mq_hw_ctx* blk_mq_map_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hctx_lock (struct blk_mq_hw_ctx*,int*) ; 
 int /*<<< orphan*/  hctx_unlock (struct blk_mq_hw_ctx*,int) ; 

blk_status_t blk_mq_request_issue_directly(struct request *rq)
{
	blk_status_t ret;
	int srcu_idx;
	blk_qc_t unused_cookie;
	struct blk_mq_ctx *ctx = rq->mq_ctx;
	struct blk_mq_hw_ctx *hctx = blk_mq_map_queue(rq->q, ctx->cpu);

	hctx_lock(hctx, &srcu_idx);
	ret = __blk_mq_try_issue_directly(hctx, rq, &unused_cookie, true);
	hctx_unlock(hctx, srcu_idx);

	return ret;
}