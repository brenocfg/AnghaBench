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
struct rc5t583_irq_data {int int_type; int int_en_bit; } ;
struct rc5t583 {unsigned int irq_base; int* gpedge_reg; } ;
struct irq_data {unsigned int irq; } ;

/* Variables and functions */
 int EINVAL ; 
 int GPIO_INT ; 
 unsigned int IRQ_TYPE_EDGE_BOTH ; 
 unsigned int IRQ_TYPE_EDGE_FALLING ; 
 unsigned int IRQ_TYPE_EDGE_RISING ; 
 struct rc5t583* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  rc5t583_irq_unmask (struct irq_data*) ; 
 struct rc5t583_irq_data* rc5t583_irqs ; 

__attribute__((used)) static int rc5t583_irq_set_type(struct irq_data *irq_data, unsigned int type)
{
	struct rc5t583 *rc5t583 = irq_data_get_irq_chip_data(irq_data);
	unsigned int __irq = irq_data->irq - rc5t583->irq_base;
	const struct rc5t583_irq_data *data = &rc5t583_irqs[__irq];
	int val = 0;
	int gpedge_index;
	int gpedge_bit_pos;

	/* Supporting only trigger level inetrrupt */
	if ((data->int_type & GPIO_INT) && (type & IRQ_TYPE_EDGE_BOTH)) {
		gpedge_index = data->int_en_bit / 4;
		gpedge_bit_pos = data->int_en_bit % 4;

		if (type & IRQ_TYPE_EDGE_FALLING)
			val |= 0x2;

		if (type & IRQ_TYPE_EDGE_RISING)
			val |= 0x1;

		rc5t583->gpedge_reg[gpedge_index] &= ~(3 << gpedge_bit_pos);
		rc5t583->gpedge_reg[gpedge_index] |= (val << gpedge_bit_pos);
		rc5t583_irq_unmask(irq_data);
		return 0;
	}
	return -EINVAL;
}