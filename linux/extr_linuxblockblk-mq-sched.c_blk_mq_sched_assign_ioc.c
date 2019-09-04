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
struct request_queue {int /*<<< orphan*/  queue_lock; } ;
struct TYPE_2__ {struct io_cq* icq; } ;
struct request {TYPE_1__ elv; struct request_queue* q; } ;
struct io_cq {int /*<<< orphan*/  ioc; } ;
struct io_context {int dummy; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  get_io_context (int /*<<< orphan*/ ) ; 
 struct io_cq* ioc_create_icq (struct io_context*,struct request_queue*,int /*<<< orphan*/ ) ; 
 struct io_cq* ioc_lookup_icq (struct io_context*,struct request_queue*) ; 
 struct io_context* rq_ioc (struct bio*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

void blk_mq_sched_assign_ioc(struct request *rq, struct bio *bio)
{
	struct request_queue *q = rq->q;
	struct io_context *ioc = rq_ioc(bio);
	struct io_cq *icq;

	spin_lock_irq(q->queue_lock);
	icq = ioc_lookup_icq(ioc, q);
	spin_unlock_irq(q->queue_lock);

	if (!icq) {
		icq = ioc_create_icq(ioc, q, GFP_ATOMIC);
		if (!icq)
			return;
	}
	get_io_context(icq->ioc);
	rq->elv.icq = icq;
}