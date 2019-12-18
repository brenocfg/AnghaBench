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
struct samsung_pinctrl_drv_data {int nr_banks; int /*<<< orphan*/  dev; struct samsung_pin_bank* pin_banks; } ;
struct samsung_pin_bank {scalar_t__ eint_type; int /*<<< orphan*/  name; struct exynos_irq_chip* irq_chip; } ;
struct exynos_irq_chip {int dummy; } ;

/* Variables and functions */
 scalar_t__ EINT_TYPE_GPIO ; 
 scalar_t__ EINT_TYPE_WKUP ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos_pinctrl_set_eint_wakeup_mask (struct samsung_pinctrl_drv_data*,struct exynos_irq_chip*) ; 
 int /*<<< orphan*/  exynos_pinctrl_suspend_bank (struct samsung_pinctrl_drv_data*,struct samsung_pin_bank*) ; 

void exynos_pinctrl_suspend(struct samsung_pinctrl_drv_data *drvdata)
{
	struct samsung_pin_bank *bank = drvdata->pin_banks;
	struct exynos_irq_chip *irq_chip = NULL;
	int i;

	for (i = 0; i < drvdata->nr_banks; ++i, ++bank) {
		if (bank->eint_type == EINT_TYPE_GPIO)
			exynos_pinctrl_suspend_bank(drvdata, bank);
		else if (bank->eint_type == EINT_TYPE_WKUP) {
			if (!irq_chip) {
				irq_chip = bank->irq_chip;
				exynos_pinctrl_set_eint_wakeup_mask(drvdata,
								    irq_chip);
			} else if (bank->irq_chip != irq_chip) {
				dev_warn(drvdata->dev,
					 "More than one external wakeup interrupt chip configured (bank: %s). This is not supported by hardware nor by driver.\n",
					 bank->name);
			}
		}
	}
}