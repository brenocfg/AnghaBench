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
struct pinctrl_gpio_range {int dummy; } ;
struct pinctrl_dev {int dummy; } ;
struct as3722_pctrl_info {int /*<<< orphan*/  dev; TYPE_1__* gpio_control; struct as3722* as3722; } ;
struct as3722 {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mode_prop; } ;

/* Variables and functions */
 int /*<<< orphan*/  AS3722_GPIO_MODE_MASK ; 
 int /*<<< orphan*/  AS3722_GPIOn_CONTROL_REG (unsigned int) ; 
 int as3722_pinctrl_gpio_get_mode (int /*<<< orphan*/ ,int) ; 
 int as3722_update_bits (struct as3722*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char*,unsigned int) ; 
 struct as3722_pctrl_info* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int as3722_pinctrl_gpio_set_direction(struct pinctrl_dev *pctldev,
		struct pinctrl_gpio_range *range, unsigned offset, bool input)
{
	struct as3722_pctrl_info *as_pci = pinctrl_dev_get_drvdata(pctldev);
	struct as3722 *as3722 = as_pci->as3722;
	int mode;

	mode = as3722_pinctrl_gpio_get_mode(
			as_pci->gpio_control[offset].mode_prop, input);
	if (mode < 0) {
		dev_err(as_pci->dev, "%s direction for GPIO %d not supported\n",
			(input) ? "Input" : "Output", offset);
		return mode;
	}

	return as3722_update_bits(as3722, AS3722_GPIOn_CONTROL_REG(offset),
				AS3722_GPIO_MODE_MASK, mode);
}