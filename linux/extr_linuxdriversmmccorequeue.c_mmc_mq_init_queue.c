#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct mmc_queue_req {int dummy; } ;
struct TYPE_8__ {int queue_depth; int flags; int nr_hw_queues; int cmd_size; struct mmc_queue* driver_data; int /*<<< orphan*/  numa_node; struct blk_mq_ops const* ops; } ;
struct mmc_queue {TYPE_1__ tag_set; TYPE_2__* queue; } ;
struct blk_mq_ops {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
struct TYPE_9__ {struct mmc_queue* queuedata; int /*<<< orphan*/ * queue_lock; } ;

/* Variables and functions */
 int BLK_MQ_F_BLOCKING ; 
 int BLK_MQ_F_SG_MERGE ; 
 int BLK_MQ_F_SHOULD_MERGE ; 
 scalar_t__ IS_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  NUMA_NO_NODE ; 
 int PTR_ERR (TYPE_2__*) ; 
 int blk_mq_alloc_tag_set (TYPE_1__*) ; 
 int /*<<< orphan*/  blk_mq_free_tag_set (TYPE_1__*) ; 
 TYPE_2__* blk_mq_init_queue (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mmc_mq_init_queue(struct mmc_queue *mq, int q_depth,
			     const struct blk_mq_ops *mq_ops, spinlock_t *lock)
{
	int ret;

	memset(&mq->tag_set, 0, sizeof(mq->tag_set));
	mq->tag_set.ops = mq_ops;
	mq->tag_set.queue_depth = q_depth;
	mq->tag_set.numa_node = NUMA_NO_NODE;
	mq->tag_set.flags = BLK_MQ_F_SHOULD_MERGE | BLK_MQ_F_SG_MERGE |
			    BLK_MQ_F_BLOCKING;
	mq->tag_set.nr_hw_queues = 1;
	mq->tag_set.cmd_size = sizeof(struct mmc_queue_req);
	mq->tag_set.driver_data = mq;

	ret = blk_mq_alloc_tag_set(&mq->tag_set);
	if (ret)
		return ret;

	mq->queue = blk_mq_init_queue(&mq->tag_set);
	if (IS_ERR(mq->queue)) {
		ret = PTR_ERR(mq->queue);
		goto free_tag_set;
	}

	mq->queue->queue_lock = lock;
	mq->queue->queuedata = mq;

	return 0;

free_tag_set:
	blk_mq_free_tag_set(&mq->tag_set);

	return ret;
}