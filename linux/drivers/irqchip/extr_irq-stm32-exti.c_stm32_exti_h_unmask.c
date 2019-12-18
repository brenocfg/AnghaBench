#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stm32_exti_chip_data {int /*<<< orphan*/  rlock; int /*<<< orphan*/  mask_cache; struct stm32_exti_bank* reg_bank; } ;
struct stm32_exti_bank {int /*<<< orphan*/  imr_ofst; } ;
struct irq_data {TYPE_1__* parent_data; } ;
struct TYPE_2__ {scalar_t__ chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  irq_chip_unmask_parent (struct irq_data*) ; 
 struct stm32_exti_chip_data* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stm32_exti_set_bit (struct irq_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stm32_exti_h_unmask(struct irq_data *d)
{
	struct stm32_exti_chip_data *chip_data = irq_data_get_irq_chip_data(d);
	const struct stm32_exti_bank *stm32_bank = chip_data->reg_bank;

	raw_spin_lock(&chip_data->rlock);
	chip_data->mask_cache = stm32_exti_set_bit(d, stm32_bank->imr_ofst);
	raw_spin_unlock(&chip_data->rlock);

	if (d->parent_data->chip)
		irq_chip_unmask_parent(d);
}