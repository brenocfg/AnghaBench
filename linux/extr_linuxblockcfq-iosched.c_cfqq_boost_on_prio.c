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
struct cfq_queue {scalar_t__ ioprio; scalar_t__ org_ioprio; int /*<<< orphan*/  ioprio_class; int /*<<< orphan*/  org_ioprio_class; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOPRIO_CLASS_BE ; 
 scalar_t__ IOPRIO_NORM ; 
 unsigned int REQ_PRIO ; 
 scalar_t__ cfq_class_idle (struct cfq_queue*) ; 

__attribute__((used)) static void cfqq_boost_on_prio(struct cfq_queue *cfqq, unsigned int op)
{
	/*
	 * If REQ_PRIO is set, boost class and prio level, if it's below
	 * BE/NORM. If prio is not set, restore the potentially boosted
	 * class/prio level.
	 */
	if (!(op & REQ_PRIO)) {
		cfqq->ioprio_class = cfqq->org_ioprio_class;
		cfqq->ioprio = cfqq->org_ioprio;
	} else {
		if (cfq_class_idle(cfqq))
			cfqq->ioprio_class = IOPRIO_CLASS_BE;
		if (cfqq->ioprio > IOPRIO_NORM)
			cfqq->ioprio = IOPRIO_NORM;
	}
}