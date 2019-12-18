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
struct knav_queue_inst {TYPE_1__* range; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 unsigned int KNAV_QUEUE_ACC ; 
 unsigned int KNAV_QUEUE_GP ; 
 unsigned int KNAV_QUEUE_QPEND ; 
 int RANGE_HAS_ACCUMULATOR ; 
 int RANGE_HAS_IRQ ; 

__attribute__((used)) static inline bool knav_queue_match_type(struct knav_queue_inst *inst,
						unsigned type)
{
	if ((type == KNAV_QUEUE_QPEND) &&
	    (inst->range->flags & RANGE_HAS_IRQ)) {
		return true;
	} else if ((type == KNAV_QUEUE_ACC) &&
		(inst->range->flags & RANGE_HAS_ACCUMULATOR)) {
		return true;
	} else if ((type == KNAV_QUEUE_GP) &&
		!(inst->range->flags &
			(RANGE_HAS_ACCUMULATOR | RANGE_HAS_IRQ))) {
		return true;
	}
	return false;
}