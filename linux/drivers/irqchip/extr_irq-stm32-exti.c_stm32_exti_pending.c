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
struct stm32_exti_chip_data {struct stm32_exti_bank* reg_bank; } ;
struct stm32_exti_bank {scalar_t__ rpr_ofst; scalar_t__ fpr_ofst; } ;
struct irq_chip_generic {struct stm32_exti_chip_data* private; } ;

/* Variables and functions */
 scalar_t__ UNDEF_REG ; 
 unsigned long irq_reg_readl (struct irq_chip_generic*,scalar_t__) ; 

__attribute__((used)) static unsigned long stm32_exti_pending(struct irq_chip_generic *gc)
{
	struct stm32_exti_chip_data *chip_data = gc->private;
	const struct stm32_exti_bank *stm32_bank = chip_data->reg_bank;
	unsigned long pending;

	pending = irq_reg_readl(gc, stm32_bank->rpr_ofst);
	if (stm32_bank->fpr_ofst != UNDEF_REG)
		pending |= irq_reg_readl(gc, stm32_bank->fpr_ofst);

	return pending;
}