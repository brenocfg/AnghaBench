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
struct samsung_pinctrl_drv_data {int nr_banks; int /*<<< orphan*/  pctl_dev; struct samsung_pin_bank* pin_banks; } ;
struct samsung_pin_bank {int /*<<< orphan*/  grange; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pinctrl_remove_gpio_range (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int samsung_pinctrl_unregister(struct platform_device *pdev,
				      struct samsung_pinctrl_drv_data *drvdata)
{
	struct samsung_pin_bank *bank = drvdata->pin_banks;
	int i;

	for (i = 0; i < drvdata->nr_banks; ++i, ++bank)
		pinctrl_remove_gpio_range(drvdata->pctl_dev, &bank->grange);

	return 0;
}