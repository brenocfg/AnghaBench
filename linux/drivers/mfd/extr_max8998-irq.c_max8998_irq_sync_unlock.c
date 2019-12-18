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
struct max8998_dev {scalar_t__* irq_masks_cur; scalar_t__* irq_masks_cache; int /*<<< orphan*/  irqlock; int /*<<< orphan*/  i2c; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__ MAX8998_REG_IRQM1 ; 
 struct max8998_dev* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  max8998_write_reg (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void max8998_irq_sync_unlock(struct irq_data *data)
{
	struct max8998_dev *max8998 = irq_data_get_irq_chip_data(data);
	int i;

	for (i = 0; i < ARRAY_SIZE(max8998->irq_masks_cur); i++) {
		/*
		 * If there's been a change in the mask write it back
		 * to the hardware.
		 */
		if (max8998->irq_masks_cur[i] != max8998->irq_masks_cache[i]) {
			max8998->irq_masks_cache[i] = max8998->irq_masks_cur[i];
			max8998_write_reg(max8998->i2c, MAX8998_REG_IRQM1 + i,
					max8998->irq_masks_cur[i]);
		}
	}

	mutex_unlock(&max8998->irqlock);
}