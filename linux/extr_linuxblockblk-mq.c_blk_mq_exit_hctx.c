#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int dummy; } ;
struct blk_mq_tag_set {TYPE_1__* ops; } ;
struct blk_mq_hw_ctx {int flags; int /*<<< orphan*/  ctx_map; TYPE_2__* fq; int /*<<< orphan*/  srcu; } ;
struct TYPE_4__ {int /*<<< orphan*/  flush_rq; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* exit_hctx ) (struct blk_mq_hw_ctx*,unsigned int) ;int /*<<< orphan*/  (* exit_request ) (struct blk_mq_tag_set*,int /*<<< orphan*/ ,unsigned int) ;} ;

/* Variables and functions */
 int BLK_MQ_F_BLOCKING ; 
 int /*<<< orphan*/  blk_free_flush_queue (TYPE_2__*) ; 
 int /*<<< orphan*/  blk_mq_debugfs_unregister_hctx (struct blk_mq_hw_ctx*) ; 
 scalar_t__ blk_mq_hw_queue_mapped (struct blk_mq_hw_ctx*) ; 
 int /*<<< orphan*/  blk_mq_remove_cpuhp (struct blk_mq_hw_ctx*) ; 
 int /*<<< orphan*/  blk_mq_tag_idle (struct blk_mq_hw_ctx*) ; 
 int /*<<< orphan*/  cleanup_srcu_struct (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbitmap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct blk_mq_tag_set*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  stub2 (struct blk_mq_hw_ctx*,unsigned int) ; 

__attribute__((used)) static void blk_mq_exit_hctx(struct request_queue *q,
		struct blk_mq_tag_set *set,
		struct blk_mq_hw_ctx *hctx, unsigned int hctx_idx)
{
	blk_mq_debugfs_unregister_hctx(hctx);

	if (blk_mq_hw_queue_mapped(hctx))
		blk_mq_tag_idle(hctx);

	if (set->ops->exit_request)
		set->ops->exit_request(set, hctx->fq->flush_rq, hctx_idx);

	if (set->ops->exit_hctx)
		set->ops->exit_hctx(hctx, hctx_idx);

	if (hctx->flags & BLK_MQ_F_BLOCKING)
		cleanup_srcu_struct(hctx->srcu);

	blk_mq_remove_cpuhp(hctx);
	blk_free_flush_queue(hctx->fq);
	sbitmap_free(&hctx->ctx_map);
}