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
struct stm32_exti_chip_data {struct stm32_exti_bank* reg_bank; } ;
struct stm32_exti_bank {int /*<<< orphan*/  ftsr_ofst; int /*<<< orphan*/  rtsr_ofst; } ;
struct irq_data {int dummy; } ;
struct irq_chip_generic {struct stm32_exti_chip_data* private; } ;

/* Variables and functions */
 struct irq_chip_generic* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irq_gc_lock (struct irq_chip_generic*) ; 
 int /*<<< orphan*/  irq_gc_unlock (struct irq_chip_generic*) ; 
 int /*<<< orphan*/  irq_reg_readl (struct irq_chip_generic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_reg_writel (struct irq_chip_generic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stm32_exti_hwspin_lock (struct stm32_exti_chip_data*) ; 
 int /*<<< orphan*/  stm32_exti_hwspin_unlock (struct stm32_exti_chip_data*) ; 
 int stm32_exti_set_type (struct irq_data*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int stm32_irq_set_type(struct irq_data *d, unsigned int type)
{
	struct irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	struct stm32_exti_chip_data *chip_data = gc->private;
	const struct stm32_exti_bank *stm32_bank = chip_data->reg_bank;
	u32 rtsr, ftsr;
	int err;

	irq_gc_lock(gc);

	err = stm32_exti_hwspin_lock(chip_data);
	if (err)
		goto unlock;

	rtsr = irq_reg_readl(gc, stm32_bank->rtsr_ofst);
	ftsr = irq_reg_readl(gc, stm32_bank->ftsr_ofst);

	err = stm32_exti_set_type(d, type, &rtsr, &ftsr);
	if (err)
		goto unspinlock;

	irq_reg_writel(gc, rtsr, stm32_bank->rtsr_ofst);
	irq_reg_writel(gc, ftsr, stm32_bank->ftsr_ofst);

unspinlock:
	stm32_exti_hwspin_unlock(chip_data);
unlock:
	irq_gc_unlock(gc);

	return err;
}