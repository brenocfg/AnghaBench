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
typedef  int /*<<< orphan*/  u8 ;
struct msic_gpio {int trig_type; int /*<<< orphan*/  buslock; scalar_t__ trig_change_mask; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 int IRQ_TYPE_EDGE_FALLING ; 
 int IRQ_TYPE_EDGE_RISING ; 
 int /*<<< orphan*/  MSIC_GPIO_INTCNT_MASK ; 
 int /*<<< orphan*/  MSIC_GPIO_TRIG_FALL ; 
 int /*<<< orphan*/  MSIC_GPIO_TRIG_RISE ; 
 int __ffs (scalar_t__) ; 
 int /*<<< orphan*/  intel_msic_reg_update (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct msic_gpio* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int msic_gpio_to_ireg (int) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void msic_bus_sync_unlock(struct irq_data *data)
{
	struct msic_gpio *mg = irq_data_get_irq_chip_data(data);
	int offset;
	int reg;
	u8 trig = 0;

	/* We can only get one change at a time as the buslock covers the
	   entire transaction. The irq_desc->lock is dropped before we are
	   called but that is fine */
	if (mg->trig_change_mask) {
		offset = __ffs(mg->trig_change_mask);

		reg = msic_gpio_to_ireg(offset);
		if (reg < 0)
			goto out;

		if (mg->trig_type & IRQ_TYPE_EDGE_RISING)
			trig |= MSIC_GPIO_TRIG_RISE;
		if (mg->trig_type & IRQ_TYPE_EDGE_FALLING)
			trig |= MSIC_GPIO_TRIG_FALL;

		intel_msic_reg_update(reg, trig, MSIC_GPIO_INTCNT_MASK);
		mg->trig_change_mask = 0;
	}
out:
	mutex_unlock(&mg->buslock);
}