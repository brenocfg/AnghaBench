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
struct tps6586x {int /*<<< orphan*/  irq_lock; int /*<<< orphan*/ * mask_reg; int /*<<< orphan*/  dev; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ TPS6586X_INT_MASK1 ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct tps6586x* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int tps6586x_write (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tps6586x_irq_sync_unlock(struct irq_data *data)
{
	struct tps6586x *tps6586x = irq_data_get_irq_chip_data(data);
	int i;

	for (i = 0; i < ARRAY_SIZE(tps6586x->mask_reg); i++) {
		int ret;
		ret = tps6586x_write(tps6586x->dev,
					    TPS6586X_INT_MASK1 + i,
					    tps6586x->mask_reg[i]);
		WARN_ON(ret);
	}

	mutex_unlock(&tps6586x->irq_lock);
}