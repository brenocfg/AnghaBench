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
struct request {TYPE_1__* q; int /*<<< orphan*/  queuelist; } ;
struct TYPE_2__ {int /*<<< orphan*/  queue_head; scalar_t__ mq_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_add_to_requeue_list (struct request*,int,int) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool blk_flush_queue_rq(struct request *rq, bool add_front)
{
	if (rq->q->mq_ops) {
		blk_mq_add_to_requeue_list(rq, add_front, true);
		return false;
	} else {
		if (add_front)
			list_add(&rq->queuelist, &rq->q->queue_head);
		else
			list_add_tail(&rq->queuelist, &rq->q->queue_head);
		return true;
	}
}