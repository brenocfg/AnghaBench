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
struct irq_data {int dummy; } ;
typedef  enum irqchip_irq_state { ____Placeholder_irqchip_irq_state } irqchip_irq_state ;

/* Variables and functions */
 int EINVAL ; 
 int IRQCHIP_STATE_PENDING ; 
 int /*<<< orphan*/  mvebu_sei_ack_irq (struct irq_data*) ; 

__attribute__((used)) static int mvebu_sei_set_irqchip_state(struct irq_data *d,
				       enum irqchip_irq_state which,
				       bool state)
{
	/* We can only clear the pending state by acking the interrupt */
	if (which != IRQCHIP_STATE_PENDING || state)
		return -EINVAL;

	mvebu_sei_ack_irq(d);
	return 0;
}