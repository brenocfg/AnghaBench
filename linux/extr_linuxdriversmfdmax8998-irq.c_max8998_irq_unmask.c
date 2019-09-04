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
struct max8998_irq_data {int reg; int /*<<< orphan*/  mask; } ;
struct max8998_dev {int /*<<< orphan*/ * irq_masks_cur; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 struct max8998_dev* irq_data_get_irq_chip_data (struct irq_data*) ; 
 struct max8998_irq_data* irq_to_max8998_irq (struct max8998_dev*,struct irq_data*) ; 

__attribute__((used)) static void max8998_irq_unmask(struct irq_data *data)
{
	struct max8998_dev *max8998 = irq_data_get_irq_chip_data(data);
	struct max8998_irq_data *irq_data = irq_to_max8998_irq(max8998, data);

	max8998->irq_masks_cur[irq_data->reg - 1] &= ~irq_data->mask;
}