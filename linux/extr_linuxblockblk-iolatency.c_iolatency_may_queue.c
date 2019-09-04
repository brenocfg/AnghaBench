#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  entry; } ;
typedef  TYPE_3__ wait_queue_entry_t ;
struct TYPE_6__ {int /*<<< orphan*/ * next; } ;
struct TYPE_9__ {TYPE_1__ head; } ;
struct rq_wait {TYPE_4__ wait; } ;
struct TYPE_7__ {int /*<<< orphan*/  max_depth; } ;
struct iolatency_grp {TYPE_2__ rq_depth; struct rq_wait rq_wait; } ;

/* Variables and functions */
 int rq_wait_inc_below (struct rq_wait*,int /*<<< orphan*/ ) ; 
 scalar_t__ waitqueue_active (TYPE_4__*) ; 

__attribute__((used)) static inline bool iolatency_may_queue(struct iolatency_grp *iolat,
				       wait_queue_entry_t *wait,
				       bool first_block)
{
	struct rq_wait *rqw = &iolat->rq_wait;

	if (first_block && waitqueue_active(&rqw->wait) &&
	    rqw->wait.head.next != &wait->entry)
		return false;
	return rq_wait_inc_below(rqw, iolat->rq_depth.max_depth);
}