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
struct cx18_in_work_order {int /*<<< orphan*/  pending; } ;
struct cx18 {struct cx18_in_work_order* in_work_order; } ;

/* Variables and functions */
 int CX18_MAX_IN_WORK_ORDERS ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline
struct cx18_in_work_order *alloc_in_work_order_irq(struct cx18 *cx)
{
	int i;
	struct cx18_in_work_order *order = NULL;

	for (i = 0; i < CX18_MAX_IN_WORK_ORDERS; i++) {
		/*
		 * We only need "pending" atomic to inspect its contents,
		 * and need not do a check and set because:
		 * 1. Any work handler thread only clears "pending" and only
		 * on one, particular work order at a time, per handler thread.
		 * 2. "pending" is only set here, and we're serialized because
		 * we're called in an IRQ handler context.
		 */
		if (atomic_read(&cx->in_work_order[i].pending) == 0) {
			order = &cx->in_work_order[i];
			atomic_set(&order->pending, 1);
			break;
		}
	}
	return order;
}