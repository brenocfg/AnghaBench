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
struct rc5t583_irq_data {size_t grp_index; int master_bit; size_t mask_reg_index; int int_en_bit; } ;
struct rc5t583 {unsigned int irq_base; int* group_irq_en; int intc_inten_reg; int* irq_en_reg; } ;
struct irq_data {unsigned int irq; } ;

/* Variables and functions */
 struct rc5t583* irq_data_get_irq_chip_data (struct irq_data*) ; 
 struct rc5t583_irq_data* rc5t583_irqs ; 

__attribute__((used)) static void rc5t583_irq_mask(struct irq_data *irq_data)
{
	struct rc5t583 *rc5t583 = irq_data_get_irq_chip_data(irq_data);
	unsigned int __irq = irq_data->irq - rc5t583->irq_base;
	const struct rc5t583_irq_data *data = &rc5t583_irqs[__irq];

	rc5t583->group_irq_en[data->grp_index] &= ~(1 << data->grp_index);
	if (!rc5t583->group_irq_en[data->grp_index])
		rc5t583->intc_inten_reg &= ~(1 << data->master_bit);

	rc5t583->irq_en_reg[data->mask_reg_index] &= ~(1 << data->int_en_bit);
}