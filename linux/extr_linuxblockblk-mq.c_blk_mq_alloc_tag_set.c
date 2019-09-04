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
struct blk_mq_tags {int dummy; } ;
struct blk_mq_tag_set {int nr_hw_queues; int queue_depth; int reserved_tags; int /*<<< orphan*/ * tags; int /*<<< orphan*/ * mq_map; int /*<<< orphan*/  tag_list; int /*<<< orphan*/  tag_list_lock; int /*<<< orphan*/  numa_node; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  put_budget; int /*<<< orphan*/  get_budget; int /*<<< orphan*/  queue_rq; } ;

/* Variables and functions */
 int BLK_MQ_MAX_DEPTH ; 
 int BLK_MQ_TAG_MIN ; 
 int BLK_MQ_UNIQUE_TAG_BITS ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int blk_mq_alloc_rq_maps (struct blk_mq_tag_set*) ; 
 int blk_mq_update_queue_map (struct blk_mq_tag_set*) ; 
 scalar_t__ is_kdump_kernel () ; 
 void* kcalloc_node (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int min (unsigned int,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int nr_cpu_ids ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 

int blk_mq_alloc_tag_set(struct blk_mq_tag_set *set)
{
	int ret;

	BUILD_BUG_ON(BLK_MQ_MAX_DEPTH > 1 << BLK_MQ_UNIQUE_TAG_BITS);

	if (!set->nr_hw_queues)
		return -EINVAL;
	if (!set->queue_depth)
		return -EINVAL;
	if (set->queue_depth < set->reserved_tags + BLK_MQ_TAG_MIN)
		return -EINVAL;

	if (!set->ops->queue_rq)
		return -EINVAL;

	if (!set->ops->get_budget ^ !set->ops->put_budget)
		return -EINVAL;

	if (set->queue_depth > BLK_MQ_MAX_DEPTH) {
		pr_info("blk-mq: reduced tag depth to %u\n",
			BLK_MQ_MAX_DEPTH);
		set->queue_depth = BLK_MQ_MAX_DEPTH;
	}

	/*
	 * If a crashdump is active, then we are potentially in a very
	 * memory constrained environment. Limit us to 1 queue and
	 * 64 tags to prevent using too much memory.
	 */
	if (is_kdump_kernel()) {
		set->nr_hw_queues = 1;
		set->queue_depth = min(64U, set->queue_depth);
	}
	/*
	 * There is no use for more h/w queues than cpus.
	 */
	if (set->nr_hw_queues > nr_cpu_ids)
		set->nr_hw_queues = nr_cpu_ids;

	set->tags = kcalloc_node(nr_cpu_ids, sizeof(struct blk_mq_tags *),
				 GFP_KERNEL, set->numa_node);
	if (!set->tags)
		return -ENOMEM;

	ret = -ENOMEM;
	set->mq_map = kcalloc_node(nr_cpu_ids, sizeof(*set->mq_map),
				   GFP_KERNEL, set->numa_node);
	if (!set->mq_map)
		goto out_free_tags;

	ret = blk_mq_update_queue_map(set);
	if (ret)
		goto out_free_mq_map;

	ret = blk_mq_alloc_rq_maps(set);
	if (ret)
		goto out_free_mq_map;

	mutex_init(&set->tag_list_lock);
	INIT_LIST_HEAD(&set->tag_list);

	return 0;

out_free_mq_map:
	kfree(set->mq_map);
	set->mq_map = NULL;
out_free_tags:
	kfree(set->tags);
	set->tags = NULL;
	return ret;
}