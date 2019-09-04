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
struct request_list {void* rq_pool; int /*<<< orphan*/ * wait; scalar_t__* starved; scalar_t__* count; struct request_queue* q; } ;
struct request_queue {struct request_list root_rl; int /*<<< orphan*/  node; scalar_t__ cmd_size; scalar_t__ mq_ops; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLKDEV_MIN_RQ ; 
 size_t BLK_RW_ASYNC ; 
 size_t BLK_RW_SYNC ; 
 int ENOMEM ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  alloc_request_simple ; 
 int /*<<< orphan*/  alloc_request_size ; 
 int /*<<< orphan*/  blk_get_queue (struct request_queue*) ; 
 int /*<<< orphan*/  free_request_simple ; 
 int /*<<< orphan*/  free_request_size ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 void* mempool_create_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct request_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (void*) ; 

int blk_init_rl(struct request_list *rl, struct request_queue *q,
		gfp_t gfp_mask)
{
	if (unlikely(rl->rq_pool) || q->mq_ops)
		return 0;

	rl->q = q;
	rl->count[BLK_RW_SYNC] = rl->count[BLK_RW_ASYNC] = 0;
	rl->starved[BLK_RW_SYNC] = rl->starved[BLK_RW_ASYNC] = 0;
	init_waitqueue_head(&rl->wait[BLK_RW_SYNC]);
	init_waitqueue_head(&rl->wait[BLK_RW_ASYNC]);

	if (q->cmd_size) {
		rl->rq_pool = mempool_create_node(BLKDEV_MIN_RQ,
				alloc_request_size, free_request_size,
				q, gfp_mask, q->node);
	} else {
		rl->rq_pool = mempool_create_node(BLKDEV_MIN_RQ,
				alloc_request_simple, free_request_simple,
				q, gfp_mask, q->node);
	}
	if (!rl->rq_pool)
		return -ENOMEM;

	if (rl != &q->root_rl)
		WARN_ON_ONCE(!blk_get_queue(q));

	return 0;
}