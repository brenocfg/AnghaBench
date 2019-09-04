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
typedef  scalar_t__ u8 ;
struct max8997_dev {int /*<<< orphan*/  irqlock; int /*<<< orphan*/ * irq_masks_cur; int /*<<< orphan*/ * irq_masks_cache; } ;
struct irq_data {int dummy; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct i2c_client*) ; 
 int MAX8997_IRQ_GROUP_NR ; 
 scalar_t__ MAX8997_REG_INVALID ; 
 struct i2c_client* get_i2c (struct max8997_dev*,int) ; 
 struct max8997_dev* irq_data_get_irq_chip_data (struct irq_data*) ; 
 scalar_t__* max8997_mask_reg ; 
 int /*<<< orphan*/  max8997_write_reg (struct i2c_client*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void max8997_irq_sync_unlock(struct irq_data *data)
{
	struct max8997_dev *max8997 = irq_data_get_irq_chip_data(data);
	int i;

	for (i = 0; i < MAX8997_IRQ_GROUP_NR; i++) {
		u8 mask_reg = max8997_mask_reg[i];
		struct i2c_client *i2c = get_i2c(max8997, i);

		if (mask_reg == MAX8997_REG_INVALID ||
				IS_ERR_OR_NULL(i2c))
			continue;
		max8997->irq_masks_cache[i] = max8997->irq_masks_cur[i];

		max8997_write_reg(i2c, max8997_mask_reg[i],
				max8997->irq_masks_cur[i]);
	}

	mutex_unlock(&max8997->irqlock);
}