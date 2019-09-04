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
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int dummy; } ;
struct blk_mq_tag_set {int numa_node; int flags; TYPE_1__* ops; int /*<<< orphan*/  cmd_size; int /*<<< orphan*/  driver_data; int /*<<< orphan*/ * tags; } ;
struct TYPE_8__ {int /*<<< orphan*/  entry; } ;
struct blk_mq_hw_ctx {int numa_node; int flags; TYPE_2__* ctxs; int /*<<< orphan*/  ctx_map; TYPE_2__* fq; int /*<<< orphan*/  srcu; TYPE_4__ dispatch_wait; int /*<<< orphan*/  dispatch_wait_lock; scalar_t__ nr_ctx; int /*<<< orphan*/  tags; int /*<<< orphan*/  cpuhp_dead; struct request_queue* queue; int /*<<< orphan*/  dispatch; int /*<<< orphan*/  lock; int /*<<< orphan*/  run_work; } ;
struct TYPE_7__ {int /*<<< orphan*/  flush_rq; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* exit_hctx ) (struct blk_mq_hw_ctx*,unsigned int) ;scalar_t__ (* init_hctx ) (struct blk_mq_hw_ctx*,int /*<<< orphan*/ ,unsigned int) ;} ;

/* Variables and functions */
 int BLK_MQ_F_BLOCKING ; 
 int BLK_MQ_F_TAG_SHARED ; 
 int /*<<< orphan*/  CPUHP_BLK_MQ_DEAD ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int NUMA_NO_NODE ; 
 TYPE_2__* blk_alloc_flush_queue (struct request_queue*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_debugfs_register_hctx (struct request_queue*,struct blk_mq_hw_ctx*) ; 
 int /*<<< orphan*/  blk_mq_dispatch_wake ; 
 scalar_t__ blk_mq_init_request (struct blk_mq_tag_set*,int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  blk_mq_remove_cpuhp (struct blk_mq_hw_ctx*) ; 
 int /*<<< orphan*/  blk_mq_run_work_fn ; 
 int /*<<< orphan*/  cpuhp_state_add_instance_nocalls (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ilog2 (int) ; 
 int /*<<< orphan*/  init_srcu_struct (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_func_entry (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 TYPE_2__* kmalloc_array_node (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nr_cpu_ids ; 
 int /*<<< orphan*/  sbitmap_free (int /*<<< orphan*/ *) ; 
 scalar_t__ sbitmap_init_node (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct blk_mq_hw_ctx*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  stub2 (struct blk_mq_hw_ctx*,unsigned int) ; 

__attribute__((used)) static int blk_mq_init_hctx(struct request_queue *q,
		struct blk_mq_tag_set *set,
		struct blk_mq_hw_ctx *hctx, unsigned hctx_idx)
{
	int node;

	node = hctx->numa_node;
	if (node == NUMA_NO_NODE)
		node = hctx->numa_node = set->numa_node;

	INIT_DELAYED_WORK(&hctx->run_work, blk_mq_run_work_fn);
	spin_lock_init(&hctx->lock);
	INIT_LIST_HEAD(&hctx->dispatch);
	hctx->queue = q;
	hctx->flags = set->flags & ~BLK_MQ_F_TAG_SHARED;

	cpuhp_state_add_instance_nocalls(CPUHP_BLK_MQ_DEAD, &hctx->cpuhp_dead);

	hctx->tags = set->tags[hctx_idx];

	/*
	 * Allocate space for all possible cpus to avoid allocation at
	 * runtime
	 */
	hctx->ctxs = kmalloc_array_node(nr_cpu_ids, sizeof(void *),
					GFP_KERNEL, node);
	if (!hctx->ctxs)
		goto unregister_cpu_notifier;

	if (sbitmap_init_node(&hctx->ctx_map, nr_cpu_ids, ilog2(8), GFP_KERNEL,
			      node))
		goto free_ctxs;

	hctx->nr_ctx = 0;

	spin_lock_init(&hctx->dispatch_wait_lock);
	init_waitqueue_func_entry(&hctx->dispatch_wait, blk_mq_dispatch_wake);
	INIT_LIST_HEAD(&hctx->dispatch_wait.entry);

	if (set->ops->init_hctx &&
	    set->ops->init_hctx(hctx, set->driver_data, hctx_idx))
		goto free_bitmap;

	hctx->fq = blk_alloc_flush_queue(q, hctx->numa_node, set->cmd_size);
	if (!hctx->fq)
		goto exit_hctx;

	if (blk_mq_init_request(set, hctx->fq->flush_rq, hctx_idx, node))
		goto free_fq;

	if (hctx->flags & BLK_MQ_F_BLOCKING)
		init_srcu_struct(hctx->srcu);

	blk_mq_debugfs_register_hctx(q, hctx);

	return 0;

 free_fq:
	kfree(hctx->fq);
 exit_hctx:
	if (set->ops->exit_hctx)
		set->ops->exit_hctx(hctx, hctx_idx);
 free_bitmap:
	sbitmap_free(&hctx->ctx_map);
 free_ctxs:
	kfree(hctx->ctxs);
 unregister_cpu_notifier:
	blk_mq_remove_cpuhp(hctx);
	return -1;
}