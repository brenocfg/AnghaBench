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
struct intc_irqpin_priv {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned char INTC_IRQ_SENSE_VALID ; 
 unsigned int IRQ_TYPE_SENSE_MASK ; 
 unsigned char* intc_irqpin_sense ; 
 int intc_irqpin_set_sense (struct intc_irqpin_priv*,int /*<<< orphan*/ ,unsigned char) ; 
 struct intc_irqpin_priv* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irqd_to_hwirq (struct irq_data*) ; 

__attribute__((used)) static int intc_irqpin_irq_set_type(struct irq_data *d, unsigned int type)
{
	unsigned char value = intc_irqpin_sense[type & IRQ_TYPE_SENSE_MASK];
	struct intc_irqpin_priv *p = irq_data_get_irq_chip_data(d);

	if (!(value & INTC_IRQ_SENSE_VALID))
		return -EINVAL;

	return intc_irqpin_set_sense(p, irqd_to_hwirq(d),
				     value ^ INTC_IRQ_SENSE_VALID);
}