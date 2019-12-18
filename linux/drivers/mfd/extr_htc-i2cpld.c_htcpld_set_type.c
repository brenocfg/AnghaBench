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
struct htcpld_chip {unsigned int flow_type; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int IRQ_TYPE_LEVEL_HIGH ; 
 unsigned int IRQ_TYPE_LEVEL_LOW ; 
 unsigned int IRQ_TYPE_SENSE_MASK ; 
 struct htcpld_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 

__attribute__((used)) static int htcpld_set_type(struct irq_data *data, unsigned int flags)
{
	struct htcpld_chip *chip = irq_data_get_irq_chip_data(data);

	if (flags & ~IRQ_TYPE_SENSE_MASK)
		return -EINVAL;

	/* We only allow edge triggering */
	if (flags & (IRQ_TYPE_LEVEL_LOW|IRQ_TYPE_LEVEL_HIGH))
		return -EINVAL;

	chip->flow_type = flags;
	return 0;
}