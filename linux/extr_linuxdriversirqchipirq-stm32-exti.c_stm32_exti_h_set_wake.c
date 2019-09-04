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
typedef  int /*<<< orphan*/  u32 ;
struct stm32_exti_chip_data {int /*<<< orphan*/  rlock; int /*<<< orphan*/  wake_active; } ;
struct irq_data {int hwirq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int IRQS_PER_BANK ; 
 struct stm32_exti_chip_data* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int stm32_exti_h_set_wake(struct irq_data *d, unsigned int on)
{
	struct stm32_exti_chip_data *chip_data = irq_data_get_irq_chip_data(d);
	u32 mask = BIT(d->hwirq % IRQS_PER_BANK);

	raw_spin_lock(&chip_data->rlock);

	if (on)
		chip_data->wake_active |= mask;
	else
		chip_data->wake_active &= ~mask;

	raw_spin_unlock(&chip_data->rlock);

	return 0;
}