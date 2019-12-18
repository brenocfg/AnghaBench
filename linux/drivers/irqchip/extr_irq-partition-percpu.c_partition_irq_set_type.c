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
struct partition_desc {int /*<<< orphan*/  chained_desc; } ;
struct irq_data {int dummy; } ;
struct irq_chip {int (* irq_set_type ) (struct irq_data*,unsigned int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 struct partition_desc* irq_data_get_irq_chip_data (struct irq_data*) ; 
 struct irq_chip* irq_desc_get_chip (int /*<<< orphan*/ ) ; 
 struct irq_data* irq_desc_get_irq_data (int /*<<< orphan*/ ) ; 
 int stub1 (struct irq_data*,unsigned int) ; 

__attribute__((used)) static int partition_irq_set_type(struct irq_data *d, unsigned int type)
{
	struct partition_desc *part = irq_data_get_irq_chip_data(d);
	struct irq_chip *chip = irq_desc_get_chip(part->chained_desc);
	struct irq_data *data = irq_desc_get_irq_data(part->chained_desc);

	if (chip->irq_set_type)
		return chip->irq_set_type(data, type);

	return -EINVAL;
}