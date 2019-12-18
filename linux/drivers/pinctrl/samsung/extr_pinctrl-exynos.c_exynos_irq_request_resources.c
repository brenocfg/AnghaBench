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
struct samsung_pin_bank_type {unsigned long* reg_offset; unsigned int* fld_width; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct samsung_pin_bank {unsigned long pctl_offset; int /*<<< orphan*/  slock; scalar_t__ pctl_base; int /*<<< orphan*/  name; TYPE_1__ gpio_chip; struct samsung_pin_bank_type* type; } ;
struct irq_data {unsigned int hwirq; } ;

/* Variables and functions */
 unsigned int EXYNOS_PIN_FUNC_EINT ; 
 size_t PINCFG_TYPE_FUNC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int) ; 
 int gpiochip_lock_as_irq (TYPE_1__*,unsigned int) ; 
 struct samsung_pin_bank* irq_data_get_irq_chip_data (struct irq_data*) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int exynos_irq_request_resources(struct irq_data *irqd)
{
	struct samsung_pin_bank *bank = irq_data_get_irq_chip_data(irqd);
	const struct samsung_pin_bank_type *bank_type = bank->type;
	unsigned long reg_con, flags;
	unsigned int shift, mask, con;
	int ret;

	ret = gpiochip_lock_as_irq(&bank->gpio_chip, irqd->hwirq);
	if (ret) {
		dev_err(bank->gpio_chip.parent,
			"unable to lock pin %s-%lu IRQ\n",
			bank->name, irqd->hwirq);
		return ret;
	}

	reg_con = bank->pctl_offset + bank_type->reg_offset[PINCFG_TYPE_FUNC];
	shift = irqd->hwirq * bank_type->fld_width[PINCFG_TYPE_FUNC];
	mask = (1 << bank_type->fld_width[PINCFG_TYPE_FUNC]) - 1;

	spin_lock_irqsave(&bank->slock, flags);

	con = readl(bank->pctl_base + reg_con);
	con &= ~(mask << shift);
	con |= EXYNOS_PIN_FUNC_EINT << shift;
	writel(con, bank->pctl_base + reg_con);

	spin_unlock_irqrestore(&bank->slock, flags);

	return 0;
}