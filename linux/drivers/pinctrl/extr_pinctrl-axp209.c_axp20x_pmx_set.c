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
struct pinctrl_dev {int dummy; } ;
struct axp20x_pctl {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXP20X_GPIO_FUNCTIONS ; 
 int axp20x_gpio_get_reg (unsigned int) ; 
 struct axp20x_pctl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int axp20x_pmx_set(struct pinctrl_dev *pctldev, unsigned int offset,
			  u8 config)
{
	struct axp20x_pctl *pctl = pinctrl_dev_get_drvdata(pctldev);
	int reg;

	reg = axp20x_gpio_get_reg(offset);
	if (reg < 0)
		return reg;

	return regmap_update_bits(pctl->regmap, reg, AXP20X_GPIO_FUNCTIONS,
				  config);
}