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
struct max8997_irq_data {size_t group; int /*<<< orphan*/  mask; } ;
struct max8997_dev {int /*<<< orphan*/ * irq_masks_cur; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 struct max8997_dev* irq_data_get_irq_chip_data (struct irq_data*) ; 
 struct max8997_irq_data* irq_to_max8997_irq (struct max8997_dev*,struct irq_data*) ; 

__attribute__((used)) static void max8997_irq_unmask(struct irq_data *data)
{
	struct max8997_dev *max8997 = irq_data_get_irq_chip_data(data);
	const struct max8997_irq_data *irq_data = irq_to_max8997_irq(max8997,
								     data);

	max8997->irq_masks_cur[irq_data->group] &= ~irq_data->mask;
}