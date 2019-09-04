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
struct request_queue {TYPE_1__* elevator; } ;
struct request {int dummy; } ;
struct blk_mq_hw_ctx {struct request_queue* queue; } ;
struct bio {int /*<<< orphan*/  bi_opf; } ;
struct bfq_io_cq {int dummy; } ;
struct bfq_data {int /*<<< orphan*/  lock; struct bfq_io_cq* bio_bic; int /*<<< orphan*/ * bio_bfqq; } ;
struct TYPE_4__ {int /*<<< orphan*/  io_context; } ;
struct TYPE_3__ {struct bfq_data* elevator_data; } ;

/* Variables and functions */
 struct bfq_io_cq* bfq_bic_lookup (struct bfq_data*,int /*<<< orphan*/ ,struct request_queue*) ; 
 int /*<<< orphan*/ * bic_to_bfqq (struct bfq_io_cq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_free_request (struct request*) ; 
 int blk_mq_sched_try_merge (struct request_queue*,struct bio*,struct request**) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  op_is_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool bfq_bio_merge(struct blk_mq_hw_ctx *hctx, struct bio *bio)
{
	struct request_queue *q = hctx->queue;
	struct bfq_data *bfqd = q->elevator->elevator_data;
	struct request *free = NULL;
	/*
	 * bfq_bic_lookup grabs the queue_lock: invoke it now and
	 * store its return value for later use, to avoid nesting
	 * queue_lock inside the bfqd->lock. We assume that the bic
	 * returned by bfq_bic_lookup does not go away before
	 * bfqd->lock is taken.
	 */
	struct bfq_io_cq *bic = bfq_bic_lookup(bfqd, current->io_context, q);
	bool ret;

	spin_lock_irq(&bfqd->lock);

	if (bic)
		bfqd->bio_bfqq = bic_to_bfqq(bic, op_is_sync(bio->bi_opf));
	else
		bfqd->bio_bfqq = NULL;
	bfqd->bio_bic = bic;

	ret = blk_mq_sched_try_merge(q, bio, &free);

	if (free)
		blk_mq_free_request(free);
	spin_unlock_irq(&bfqd->lock);

	return ret;
}