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
struct knav_queue_inst {unsigned int id; TYPE_2__* qmgr; int /*<<< orphan*/  desc_count; } ;
struct knav_queue {struct knav_queue_inst* inst; } ;
struct TYPE_4__ {unsigned int start_queue; TYPE_1__* reg_push; } ;
struct TYPE_3__ {int /*<<< orphan*/  ptr_size_thresh; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int knav_queue_flush(struct knav_queue *qh)
{
	struct knav_queue_inst *inst = qh->inst;
	unsigned id = inst->id - inst->qmgr->start_queue;

	atomic_set(&inst->desc_count, 0);
	writel_relaxed(0, &inst->qmgr->reg_push[id].ptr_size_thresh);
	return 0;
}