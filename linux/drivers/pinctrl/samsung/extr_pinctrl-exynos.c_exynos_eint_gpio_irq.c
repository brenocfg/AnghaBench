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
struct samsung_pinctrl_drv_data {struct samsung_pin_bank* pin_banks; } ;
struct samsung_pin_bank {int /*<<< orphan*/  irq_domain; scalar_t__ eint_base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 unsigned int EXYNOS_SVC_GROUP (unsigned int) ; 
 unsigned int EXYNOS_SVC_NUM_MASK ; 
 scalar_t__ EXYNOS_SVC_OFFSET ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  generic_handle_irq (unsigned int) ; 
 unsigned int irq_linear_revmap (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int readl (scalar_t__) ; 

__attribute__((used)) static irqreturn_t exynos_eint_gpio_irq(int irq, void *data)
{
	struct samsung_pinctrl_drv_data *d = data;
	struct samsung_pin_bank *bank = d->pin_banks;
	unsigned int svc, group, pin, virq;

	svc = readl(bank->eint_base + EXYNOS_SVC_OFFSET);
	group = EXYNOS_SVC_GROUP(svc);
	pin = svc & EXYNOS_SVC_NUM_MASK;

	if (!group)
		return IRQ_HANDLED;
	bank += (group - 1);

	virq = irq_linear_revmap(bank->irq_domain, pin);
	if (!virq)
		return IRQ_NONE;
	generic_handle_irq(virq);
	return IRQ_HANDLED;
}