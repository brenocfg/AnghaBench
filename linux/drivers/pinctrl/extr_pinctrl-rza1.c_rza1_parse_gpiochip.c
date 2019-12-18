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
struct rza1_pinctrl {int /*<<< orphan*/  dev; int /*<<< orphan*/  pctl; int /*<<< orphan*/ * ports; } ;
struct pinctrl_gpio_range {unsigned int id; struct gpio_chip* gc; int /*<<< orphan*/  npins; int /*<<< orphan*/  base; int /*<<< orphan*/  pin_base; scalar_t__ name; } ;
struct of_phandle_args {int /*<<< orphan*/ * args; } ;
struct gpio_chip {int base; int /*<<< orphan*/  ngpio; scalar_t__ label; int /*<<< orphan*/  parent; struct device_node* of_node; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int RZA1_NPORTS ; 
 unsigned int RZA1_PIN_ID_TO_PORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int devm_gpiochip_add_data (int /*<<< orphan*/ ,struct gpio_chip*,int /*<<< orphan*/ *) ; 
 scalar_t__ devm_kasprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct device_node*) ; 
 int of_parse_phandle_with_fixed_args (struct device_node*,char const*,int,int /*<<< orphan*/ ,struct of_phandle_args*) ; 
 int /*<<< orphan*/  pinctrl_add_gpio_range (int /*<<< orphan*/ ,struct pinctrl_gpio_range*) ; 
 struct gpio_chip rza1_gpiochip_template ; 

__attribute__((used)) static int rza1_parse_gpiochip(struct rza1_pinctrl *rza1_pctl,
			       struct device_node *np,
			       struct gpio_chip *chip,
			       struct pinctrl_gpio_range *range)
{
	const char *list_name = "gpio-ranges";
	struct of_phandle_args of_args;
	unsigned int gpioport;
	u32 pinctrl_base;
	int ret;

	ret = of_parse_phandle_with_fixed_args(np, list_name, 3, 0, &of_args);
	if (ret) {
		dev_err(rza1_pctl->dev, "Unable to parse %s list property\n",
			list_name);
		return ret;
	}

	/*
	 * Find out on which port this gpio-chip maps to by inspecting the
	 * second argument of the "gpio-ranges" property.
	 */
	pinctrl_base = of_args.args[1];
	gpioport = RZA1_PIN_ID_TO_PORT(pinctrl_base);
	if (gpioport >= RZA1_NPORTS) {
		dev_err(rza1_pctl->dev,
			"Invalid values in property %s\n", list_name);
		return -EINVAL;
	}

	*chip		= rza1_gpiochip_template;
	chip->base	= -1;
	chip->label	= devm_kasprintf(rza1_pctl->dev, GFP_KERNEL, "%pOFn",
					 np);
	if (!chip->label)
		return -ENOMEM;

	chip->ngpio	= of_args.args[2];
	chip->of_node	= np;
	chip->parent	= rza1_pctl->dev;

	range->id	= gpioport;
	range->name	= chip->label;
	range->pin_base	= range->base = pinctrl_base;
	range->npins	= of_args.args[2];
	range->gc	= chip;

	ret = devm_gpiochip_add_data(rza1_pctl->dev, chip,
				     &rza1_pctl->ports[gpioport]);
	if (ret)
		return ret;

	pinctrl_add_gpio_range(rza1_pctl->pctl, range);

	dev_info(rza1_pctl->dev, "Parsed gpiochip %s with %d pins\n",
		 chip->label, chip->ngpio);

	return 0;
}