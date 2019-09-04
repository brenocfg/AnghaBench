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
struct irq_chip {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  __cpu_unmask_irq (unsigned int) ; 
 int /*<<< orphan*/  cpu_interrupt_type ; 
 int /*<<< orphan*/  handle_percpu_irq ; 
 int /*<<< orphan*/ * irq_get_chip (unsigned int) ; 
 scalar_t__ irq_has_action (unsigned int) ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (unsigned int,struct irq_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chip_data (unsigned int,void*) ; 

int cpu_claim_irq(unsigned int irq, struct irq_chip *type, void *data)
{
	if (irq_has_action(irq))
		return -EBUSY;
	if (irq_get_chip(irq) != &cpu_interrupt_type)
		return -EBUSY;

	/* for iosapic interrupts */
	if (type) {
		irq_set_chip_and_handler(irq, type, handle_percpu_irq);
		irq_set_chip_data(irq, data);
		__cpu_unmask_irq(irq);
	}
	return 0;
}