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
struct request_queue {int nr_hw_queues; int /*<<< orphan*/  sysfs_lock; int /*<<< orphan*/  mq_map; struct blk_mq_hw_ctx** queue_hw_ctx; } ;
struct blk_mq_tag_set {int nr_hw_queues; } ;
struct blk_mq_hw_ctx {int numa_node; int queue_num; int /*<<< orphan*/  kobj; scalar_t__ tags; int /*<<< orphan*/  cpumask; int /*<<< orphan*/  nr_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_exit_hctx (struct request_queue*,struct blk_mq_tag_set*,struct blk_mq_hw_ctx*,int) ; 
 int /*<<< orphan*/  blk_mq_free_map_and_requests (struct blk_mq_tag_set*,int) ; 
 int /*<<< orphan*/  blk_mq_hctx_kobj_init (struct blk_mq_hw_ctx*) ; 
 int /*<<< orphan*/  blk_mq_hw_ctx_size (struct blk_mq_tag_set*) ; 
 int blk_mq_hw_queue_to_node (int /*<<< orphan*/ ,int) ; 
 scalar_t__ blk_mq_init_hctx (struct request_queue*,struct blk_mq_tag_set*,struct blk_mq_hw_ctx*,int) ; 
 int /*<<< orphan*/  blk_mq_sysfs_register (struct request_queue*) ; 
 int /*<<< orphan*/  blk_mq_sysfs_unregister (struct request_queue*) ; 
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct blk_mq_hw_ctx*) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 struct blk_mq_hw_ctx* kzalloc_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zalloc_cpumask_var_node (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void blk_mq_realloc_hw_ctxs(struct blk_mq_tag_set *set,
						struct request_queue *q)
{
	int i, j;
	struct blk_mq_hw_ctx **hctxs = q->queue_hw_ctx;

	blk_mq_sysfs_unregister(q);

	/* protect against switching io scheduler  */
	mutex_lock(&q->sysfs_lock);
	for (i = 0; i < set->nr_hw_queues; i++) {
		int node;

		if (hctxs[i])
			continue;

		node = blk_mq_hw_queue_to_node(q->mq_map, i);
		hctxs[i] = kzalloc_node(blk_mq_hw_ctx_size(set),
					GFP_KERNEL, node);
		if (!hctxs[i])
			break;

		if (!zalloc_cpumask_var_node(&hctxs[i]->cpumask, GFP_KERNEL,
						node)) {
			kfree(hctxs[i]);
			hctxs[i] = NULL;
			break;
		}

		atomic_set(&hctxs[i]->nr_active, 0);
		hctxs[i]->numa_node = node;
		hctxs[i]->queue_num = i;

		if (blk_mq_init_hctx(q, set, hctxs[i], i)) {
			free_cpumask_var(hctxs[i]->cpumask);
			kfree(hctxs[i]);
			hctxs[i] = NULL;
			break;
		}
		blk_mq_hctx_kobj_init(hctxs[i]);
	}
	for (j = i; j < q->nr_hw_queues; j++) {
		struct blk_mq_hw_ctx *hctx = hctxs[j];

		if (hctx) {
			if (hctx->tags)
				blk_mq_free_map_and_requests(set, j);
			blk_mq_exit_hctx(q, set, hctx, j);
			kobject_put(&hctx->kobj);
			hctxs[j] = NULL;

		}
	}
	q->nr_hw_queues = i;
	mutex_unlock(&q->sysfs_lock);
	blk_mq_sysfs_register(q);
}