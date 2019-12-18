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
struct pinctrl_pin_desc {int number; int /*<<< orphan*/  name; } ;
struct pinctrl_desc {int npins; int /*<<< orphan*/ * confops; struct pinctrl_pin_desc* pins; int /*<<< orphan*/ * pctlops; int /*<<< orphan*/  name; } ;
struct gpio_chip {int ngpio; } ;
struct iproc_gpio {int /*<<< orphan*/  pctl; int /*<<< orphan*/  dev; struct gpio_chip gc; struct pinctrl_desc pctldesc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_kasprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 struct pinctrl_pin_desc* devm_kcalloc (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_pinctrl_register (int /*<<< orphan*/ ,struct pinctrl_desc*,struct iproc_gpio*) ; 
 int /*<<< orphan*/  iproc_pconf_ops ; 
 int /*<<< orphan*/  iproc_pctrl_ops ; 

__attribute__((used)) static int iproc_gpio_register_pinconf(struct iproc_gpio *chip)
{
	struct pinctrl_desc *pctldesc = &chip->pctldesc;
	struct pinctrl_pin_desc *pins;
	struct gpio_chip *gc = &chip->gc;
	int i;

	pins = devm_kcalloc(chip->dev, gc->ngpio, sizeof(*pins), GFP_KERNEL);
	if (!pins)
		return -ENOMEM;

	for (i = 0; i < gc->ngpio; i++) {
		pins[i].number = i;
		pins[i].name = devm_kasprintf(chip->dev, GFP_KERNEL,
					      "gpio-%d", i);
		if (!pins[i].name)
			return -ENOMEM;
	}

	pctldesc->name = dev_name(chip->dev);
	pctldesc->pctlops = &iproc_pctrl_ops;
	pctldesc->pins = pins;
	pctldesc->npins = gc->ngpio;
	pctldesc->confops = &iproc_pconf_ops;

	chip->pctl = devm_pinctrl_register(chip->dev, pctldesc, chip);
	if (IS_ERR(chip->pctl)) {
		dev_err(chip->dev, "unable to register pinctrl device\n");
		return PTR_ERR(chip->pctl);
	}

	return 0;
}