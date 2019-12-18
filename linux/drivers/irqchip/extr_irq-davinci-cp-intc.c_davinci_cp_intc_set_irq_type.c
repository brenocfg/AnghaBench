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
struct irq_data {int /*<<< orphan*/  hwirq; } ;

/* Variables and functions */
 unsigned int BIT_MASK (int /*<<< orphan*/ ) ; 
 unsigned int BIT_WORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DAVINCI_CP_INTC_SYS_POLARITY (unsigned int) ; 
 int /*<<< orphan*/  DAVINCI_CP_INTC_SYS_TYPE (unsigned int) ; 
 int EINVAL ; 
#define  IRQ_TYPE_EDGE_FALLING 131 
#define  IRQ_TYPE_EDGE_RISING 130 
#define  IRQ_TYPE_LEVEL_HIGH 129 
#define  IRQ_TYPE_LEVEL_LOW 128 
 unsigned int davinci_cp_intc_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  davinci_cp_intc_write (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int davinci_cp_intc_set_irq_type(struct irq_data *d,
					unsigned int flow_type)
{
	unsigned int reg, mask, polarity, type;

	reg = BIT_WORD(d->hwirq);
	mask = BIT_MASK(d->hwirq);
	polarity = davinci_cp_intc_read(DAVINCI_CP_INTC_SYS_POLARITY(reg));
	type = davinci_cp_intc_read(DAVINCI_CP_INTC_SYS_TYPE(reg));

	switch (flow_type) {
	case IRQ_TYPE_EDGE_RISING:
		polarity |= mask;
		type |= mask;
		break;
	case IRQ_TYPE_EDGE_FALLING:
		polarity &= ~mask;
		type |= mask;
		break;
	case IRQ_TYPE_LEVEL_HIGH:
		polarity |= mask;
		type &= ~mask;
		break;
	case IRQ_TYPE_LEVEL_LOW:
		polarity &= ~mask;
		type &= ~mask;
		break;
	default:
		return -EINVAL;
	}

	davinci_cp_intc_write(polarity, DAVINCI_CP_INTC_SYS_POLARITY(reg));
	davinci_cp_intc_write(type, DAVINCI_CP_INTC_SYS_TYPE(reg));

	return 0;
}