#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct irq_data {unsigned int irq; } ;
struct TYPE_2__ {unsigned int* base_addr; unsigned int mask; } ;

/* Variables and functions */
 scalar_t__ GPIO_MAPPED_IRQ_BASE ; 
 unsigned int GPIO_MAPPED_IRQ_GROUP ; 
 unsigned int GROUP0_IRQ_BASE ; 
 int GROUP4_IRQ_BASE ; 
 unsigned int READ_MASK (unsigned int volatile*) ; 
 int /*<<< orphan*/  WRITE_MASK (unsigned int volatile*,unsigned int) ; 
 int /*<<< orphan*/  disable_local_irq (unsigned int) ; 
 unsigned int group_to_ip (unsigned int) ; 
 TYPE_1__* intr_group ; 
 int /*<<< orphan*/  rb532_gpio_set_istat (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void rb532_disable_irq(struct irq_data *d)
{
	unsigned int group, intr_bit, mask, irq_nr = d->irq;
	int ip = irq_nr - GROUP0_IRQ_BASE;
	volatile unsigned int *addr;

	if (ip < 0) {
		disable_local_irq(irq_nr);
	} else {
		group = ip >> 5;

		ip &= (1 << 5) - 1;
		intr_bit = 1 << ip;
		addr = intr_group[group].base_addr;
		mask = READ_MASK(addr);
		mask |= intr_bit;
		WRITE_MASK(addr, mask);

		/* There is a maximum of 14 GPIO interrupts */
		if (group == GPIO_MAPPED_IRQ_GROUP && irq_nr <= (GROUP4_IRQ_BASE + 13))
			rb532_gpio_set_istat(0, irq_nr - GPIO_MAPPED_IRQ_BASE);

		/*
		 * if there are no more interrupts enabled in this
		 * group, disable corresponding IP
		 */
		if (mask == intr_group[group].mask)
			disable_local_irq(group_to_ip(group));
	}
}