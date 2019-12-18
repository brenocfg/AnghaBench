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
typedef  int /*<<< orphan*/  u32 ;
struct irq_data {int hwirq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int EINVAL ; 
 int IRQS_PER_BANK ; 
#define  IRQ_TYPE_EDGE_BOTH 130 
#define  IRQ_TYPE_EDGE_FALLING 129 
#define  IRQ_TYPE_EDGE_RISING 128 

__attribute__((used)) static int stm32_exti_set_type(struct irq_data *d,
			       unsigned int type, u32 *rtsr, u32 *ftsr)
{
	u32 mask = BIT(d->hwirq % IRQS_PER_BANK);

	switch (type) {
	case IRQ_TYPE_EDGE_RISING:
		*rtsr |= mask;
		*ftsr &= ~mask;
		break;
	case IRQ_TYPE_EDGE_FALLING:
		*rtsr &= ~mask;
		*ftsr |= mask;
		break;
	case IRQ_TYPE_EDGE_BOTH:
		*rtsr |= mask;
		*ftsr |= mask;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}