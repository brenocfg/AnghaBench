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
struct irq_data {scalar_t__ hwirq; } ;

/* Variables and functions */
 unsigned int IRQ_TYPE_EDGE_BOTH ; 
#define  IRQ_TYPE_EDGE_FALLING 129 
 unsigned int IRQ_TYPE_EDGE_RISING ; 
 unsigned int IRQ_TYPE_LEVEL_HIGH ; 
#define  IRQ_TYPE_LEVEL_LOW 128 
 unsigned int IRQ_TYPE_LEVEL_MASK ; 
 scalar_t__ SYS_NIRQ1_EXT_SYS_IRQ_1 ; 
 scalar_t__ SYS_NIRQ2_EXT_SYS_IRQ_2 ; 
 int irq_chip_set_type_parent (struct irq_data*,unsigned int) ; 
 int /*<<< orphan*/  pr_warn (char*,scalar_t__) ; 

__attribute__((used)) static int wakeupgen_irq_set_type(struct irq_data *d, unsigned int type)
{
	bool inverted = false;

	switch (type) {
	case IRQ_TYPE_LEVEL_LOW:
		type &= ~IRQ_TYPE_LEVEL_MASK;
		type |= IRQ_TYPE_LEVEL_HIGH;
		inverted = true;
		break;
	case IRQ_TYPE_EDGE_FALLING:
		type &= ~IRQ_TYPE_EDGE_BOTH;
		type |= IRQ_TYPE_EDGE_RISING;
		inverted = true;
		break;
	default:
		break;
	}

	if (inverted && d->hwirq != SYS_NIRQ1_EXT_SYS_IRQ_1 &&
	    d->hwirq != SYS_NIRQ2_EXT_SYS_IRQ_2)
		pr_warn("wakeupgen: irq%li polarity inverted in dts\n",
			d->hwirq);

	return irq_chip_set_type_parent(d, type);
}