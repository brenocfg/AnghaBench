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
#define  IRQF_TRIGGER_HIGH 129 
#define  IRQF_TRIGGER_RISING 128 
 unsigned int IRQ_TYPE_SENSE_MASK ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  irq_set_handler_locked (struct irq_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ti_sci_inta_set_type(struct irq_data *data, unsigned int type)
{
	/*
	 * .alloc default sets handle_edge_irq. But if the user specifies
	 * that IRQ is level MSI, then update the handle to handle_level_irq
	 */
	switch (type & IRQ_TYPE_SENSE_MASK) {
	case IRQF_TRIGGER_HIGH:
		irq_set_handler_locked(data, handle_level_irq);
		return 0;
	case IRQF_TRIGGER_RISING:
		return 0;
	default:
		return -EINVAL;
	}

	return -EINVAL;
}