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
struct irq_data {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  VALID_EVTCHN (int) ; 
 int /*<<< orphan*/  clear_evtchn (int) ; 
 int evtchn_from_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_move_masked_irq (struct irq_data*) ; 
 int /*<<< orphan*/  irqd_irq_disabled (struct irq_data*) ; 
 int /*<<< orphan*/  irqd_is_setaffinity_pending (struct irq_data*) ; 
 scalar_t__ likely (int) ; 
 int test_and_set_mask (int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unmask_evtchn (int) ; 

__attribute__((used)) static void ack_dynirq(struct irq_data *data)
{
	int evtchn = evtchn_from_irq(data->irq);

	if (!VALID_EVTCHN(evtchn))
		return;

	if (unlikely(irqd_is_setaffinity_pending(data)) &&
	    likely(!irqd_irq_disabled(data))) {
		int masked = test_and_set_mask(evtchn);

		clear_evtchn(evtchn);

		irq_move_masked_irq(data);

		if (!masked)
			unmask_evtchn(evtchn);
	} else
		clear_evtchn(evtchn);
}