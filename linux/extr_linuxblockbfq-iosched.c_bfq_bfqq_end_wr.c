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
struct TYPE_4__ {int prio_changed; } ;
struct bfq_queue {int wr_coeff; TYPE_2__ entity; int /*<<< orphan*/  last_wr_start_finish; scalar_t__ wr_cur_max_time; TYPE_1__* bfqd; } ;
struct TYPE_3__ {int /*<<< orphan*/  wr_busy_queues; } ;

/* Variables and functions */
 scalar_t__ bfq_bfqq_busy (struct bfq_queue*) ; 
 int /*<<< orphan*/  jiffies ; 

__attribute__((used)) static void bfq_bfqq_end_wr(struct bfq_queue *bfqq)
{
	if (bfq_bfqq_busy(bfqq))
		bfqq->bfqd->wr_busy_queues--;
	bfqq->wr_coeff = 1;
	bfqq->wr_cur_max_time = 0;
	bfqq->last_wr_start_finish = jiffies;
	/*
	 * Trigger a weight change on the next invocation of
	 * __bfq_entity_update_weight_prio.
	 */
	bfqq->entity.prio_changed = 1;
}