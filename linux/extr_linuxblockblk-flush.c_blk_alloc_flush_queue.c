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
struct request_queue {scalar_t__ mq_ops; } ;
struct request {int dummy; } ;
struct blk_flush_queue {int /*<<< orphan*/  flush_data_in_flight; int /*<<< orphan*/ * flush_queue; void* flush_rq; int /*<<< orphan*/  mq_flush_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cache_line_size () ; 
 int /*<<< orphan*/  kfree (struct blk_flush_queue*) ; 
 void* kzalloc_node (int,int /*<<< orphan*/ ,int) ; 
 int round_up (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct blk_flush_queue *blk_alloc_flush_queue(struct request_queue *q,
		int node, int cmd_size)
{
	struct blk_flush_queue *fq;
	int rq_sz = sizeof(struct request);

	fq = kzalloc_node(sizeof(*fq), GFP_KERNEL, node);
	if (!fq)
		goto fail;

	if (q->mq_ops)
		spin_lock_init(&fq->mq_flush_lock);

	rq_sz = round_up(rq_sz + cmd_size, cache_line_size());
	fq->flush_rq = kzalloc_node(rq_sz, GFP_KERNEL, node);
	if (!fq->flush_rq)
		goto fail_rq;

	INIT_LIST_HEAD(&fq->flush_queue[0]);
	INIT_LIST_HEAD(&fq->flush_queue[1]);
	INIT_LIST_HEAD(&fq->flush_data_in_flight);

	return fq;

 fail_rq:
	kfree(fq);
 fail:
	return NULL;
}