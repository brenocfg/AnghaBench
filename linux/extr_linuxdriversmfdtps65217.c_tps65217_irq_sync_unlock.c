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
struct tps65217 {int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  irq_mask; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TPS65217_INT_MASK ; 
 int /*<<< orphan*/  TPS65217_PROTECT_NONE ; 
 int /*<<< orphan*/  TPS65217_REG_INT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct tps65217* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int tps65217_set_bits (struct tps65217*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tps65217_irq_sync_unlock(struct irq_data *data)
{
	struct tps65217 *tps = irq_data_get_irq_chip_data(data);
	int ret;

	ret = tps65217_set_bits(tps, TPS65217_REG_INT, TPS65217_INT_MASK,
				tps->irq_mask, TPS65217_PROTECT_NONE);
	if (ret != 0)
		dev_err(tps->dev, "Failed to sync IRQ masks\n");

	mutex_unlock(&tps->irq_lock);
}