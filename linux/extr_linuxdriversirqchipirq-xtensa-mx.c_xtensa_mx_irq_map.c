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
struct irq_domain {struct irq_chip* host_data; } ;
struct irq_chip {int dummy; } ;
typedef  scalar_t__ irq_hw_number_t ;

/* Variables and functions */
 scalar_t__ HW_IRQ_IPI_COUNT ; 
 int /*<<< orphan*/  IRQ_LEVEL ; 
 int /*<<< orphan*/  handle_percpu_irq ; 
 int /*<<< orphan*/  irq_desc_get_irq_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chip_and_handler_name (unsigned int,struct irq_chip*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  irq_set_status_flags (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_to_desc (unsigned int) ; 
 int /*<<< orphan*/  irqd_set_single_target (int /*<<< orphan*/ ) ; 
 int xtensa_irq_map (struct irq_domain*,unsigned int,scalar_t__) ; 

__attribute__((used)) static int xtensa_mx_irq_map(struct irq_domain *d, unsigned int irq,
		irq_hw_number_t hw)
{
	if (hw < HW_IRQ_IPI_COUNT) {
		struct irq_chip *irq_chip = d->host_data;
		irq_set_chip_and_handler_name(irq, irq_chip,
				handle_percpu_irq, "ipi");
		irq_set_status_flags(irq, IRQ_LEVEL);
		return 0;
	}
	irqd_set_single_target(irq_desc_get_irq_data(irq_to_desc(irq)));
	return xtensa_irq_map(d, irq, hw);
}