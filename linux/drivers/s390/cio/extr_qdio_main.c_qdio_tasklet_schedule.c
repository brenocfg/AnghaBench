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
struct qdio_q {int /*<<< orphan*/  tasklet; TYPE_1__* irq_ptr; } ;
struct TYPE_2__ {scalar_t__ state; } ;

/* Variables and functions */
 int EPERM ; 
 scalar_t__ QDIO_IRQ_STATE_ACTIVE ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int qdio_tasklet_schedule(struct qdio_q *q)
{
	if (likely(q->irq_ptr->state == QDIO_IRQ_STATE_ACTIVE)) {
		tasklet_schedule(&q->tasklet);
		return 0;
	}
	return -EPERM;
}