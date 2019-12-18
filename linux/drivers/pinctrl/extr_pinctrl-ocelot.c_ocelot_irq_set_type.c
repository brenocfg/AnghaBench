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

/* Variables and functions */
 int EINVAL ; 
 unsigned int IRQ_TYPE_EDGE_BOTH ; 
 unsigned int IRQ_TYPE_LEVEL_HIGH ; 
 unsigned int IRQ_TYPE_SENSE_MASK ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  handle_fasteoi_irq ; 
 int /*<<< orphan*/  irq_set_chip_handler_name_locked (struct irq_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocelot_eoi_irqchip ; 
 int /*<<< orphan*/  ocelot_irqchip ; 

__attribute__((used)) static int ocelot_irq_set_type(struct irq_data *data, unsigned int type)
{
	type &= IRQ_TYPE_SENSE_MASK;

	if (!(type & (IRQ_TYPE_EDGE_BOTH | IRQ_TYPE_LEVEL_HIGH)))
		return -EINVAL;

	if (type & IRQ_TYPE_LEVEL_HIGH)
		irq_set_chip_handler_name_locked(data, &ocelot_eoi_irqchip,
						 handle_fasteoi_irq, NULL);
	if (type & IRQ_TYPE_EDGE_BOTH)
		irq_set_chip_handler_name_locked(data, &ocelot_irqchip,
						 handle_edge_irq, NULL);

	return 0;
}