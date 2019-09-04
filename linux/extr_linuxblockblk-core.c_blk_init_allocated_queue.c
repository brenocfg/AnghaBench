#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct request_queue {TYPE_1__* fq; int /*<<< orphan*/  (* exit_rq_fn ) (struct request_queue*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  sg_reserved_size; int /*<<< orphan*/  queue_flags; int /*<<< orphan*/  timeout_work; int /*<<< orphan*/  root_rl; scalar_t__ (* init_rq_fn ) (struct request_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  cmd_size; int /*<<< orphan*/  mq_ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  flush_rq; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  NUMA_NO_NODE ; 
 int /*<<< orphan*/  QUEUE_FLAG_DEFAULT ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 TYPE_1__* blk_alloc_flush_queue (struct request_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_free_flush_queue (TYPE_1__*) ; 
 scalar_t__ blk_init_rl (int /*<<< orphan*/ *,struct request_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_bio ; 
 int /*<<< orphan*/  blk_queue_make_request (struct request_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_timeout_work ; 
 scalar_t__ elevator_init (struct request_queue*) ; 
 scalar_t__ stub1 (struct request_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct request_queue*,int /*<<< orphan*/ ) ; 

int blk_init_allocated_queue(struct request_queue *q)
{
	WARN_ON_ONCE(q->mq_ops);

	q->fq = blk_alloc_flush_queue(q, NUMA_NO_NODE, q->cmd_size);
	if (!q->fq)
		return -ENOMEM;

	if (q->init_rq_fn && q->init_rq_fn(q, q->fq->flush_rq, GFP_KERNEL))
		goto out_free_flush_queue;

	if (blk_init_rl(&q->root_rl, q, GFP_KERNEL))
		goto out_exit_flush_rq;

	INIT_WORK(&q->timeout_work, blk_timeout_work);
	q->queue_flags		|= QUEUE_FLAG_DEFAULT;

	/*
	 * This also sets hw/phys segments, boundary and size
	 */
	blk_queue_make_request(q, blk_queue_bio);

	q->sg_reserved_size = INT_MAX;

	if (elevator_init(q))
		goto out_exit_flush_rq;
	return 0;

out_exit_flush_rq:
	if (q->exit_rq_fn)
		q->exit_rq_fn(q, q->fq->flush_rq);
out_free_flush_queue:
	blk_free_flush_queue(q->fq);
	q->fq = NULL;
	return -ENOMEM;
}