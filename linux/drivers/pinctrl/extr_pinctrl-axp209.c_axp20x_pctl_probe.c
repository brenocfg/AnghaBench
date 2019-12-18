#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct device {int /*<<< orphan*/  of_node; int /*<<< orphan*/  parent; } ;
struct platform_device {struct device dev; } ;
struct pinctrl_desc {int /*<<< orphan*/ * pmxops; int /*<<< orphan*/ * pctlops; int /*<<< orphan*/  npins; TYPE_1__* pins; void* owner; void* name; } ;
struct TYPE_7__ {int base; int can_sleep; int /*<<< orphan*/  ngpio; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  direction_input; int /*<<< orphan*/  set; int /*<<< orphan*/  get_direction; int /*<<< orphan*/  get; void* owner; void* label; struct device* parent; int /*<<< orphan*/  free; int /*<<< orphan*/  request; } ;
struct axp20x_pctl {TYPE_2__* desc; TYPE_3__ chip; int /*<<< orphan*/  pctl_dev; struct device* dev; int /*<<< orphan*/  regmap; } ;
struct axp20x_dev {int /*<<< orphan*/  regmap; } ;
struct TYPE_6__ {int /*<<< orphan*/  npins; TYPE_1__* pins; } ;
struct TYPE_5__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 void* THIS_MODULE ; 
 int axp20x_build_funcs_groups (struct platform_device*) ; 
 int /*<<< orphan*/  axp20x_gpio_get ; 
 int /*<<< orphan*/  axp20x_gpio_get_direction ; 
 int /*<<< orphan*/  axp20x_gpio_input ; 
 int /*<<< orphan*/  axp20x_gpio_output ; 
 int /*<<< orphan*/  axp20x_gpio_set ; 
 int /*<<< orphan*/  axp20x_pctrl_ops ; 
 int /*<<< orphan*/  axp20x_pmx_ops ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct axp20x_dev* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 void* dev_name (struct device*) ; 
 int devm_gpiochip_add_data (struct device*,TYPE_3__*,struct axp20x_pctl*) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_pinctrl_register (struct device*,struct pinctrl_desc*,struct axp20x_pctl*) ; 
 int gpiochip_add_pin_range (TYPE_3__*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiochip_generic_free ; 
 int /*<<< orphan*/  gpiochip_generic_request ; 
 TYPE_2__* of_device_get_match_data (struct device*) ; 
 int /*<<< orphan*/  of_device_is_available (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct axp20x_pctl*) ; 

__attribute__((used)) static int axp20x_pctl_probe(struct platform_device *pdev)
{
	struct axp20x_dev *axp20x = dev_get_drvdata(pdev->dev.parent);
	struct axp20x_pctl *pctl;
	struct device *dev = &pdev->dev;
	struct pinctrl_desc *pctrl_desc;
	int ret;

	if (!of_device_is_available(pdev->dev.of_node))
		return -ENODEV;

	if (!axp20x) {
		dev_err(&pdev->dev, "Parent drvdata not set\n");
		return -EINVAL;
	}

	pctl = devm_kzalloc(&pdev->dev, sizeof(*pctl), GFP_KERNEL);
	if (!pctl)
		return -ENOMEM;

	pctl->chip.base			= -1;
	pctl->chip.can_sleep		= true;
	pctl->chip.request		= gpiochip_generic_request;
	pctl->chip.free			= gpiochip_generic_free;
	pctl->chip.parent		= &pdev->dev;
	pctl->chip.label		= dev_name(&pdev->dev);
	pctl->chip.owner		= THIS_MODULE;
	pctl->chip.get			= axp20x_gpio_get;
	pctl->chip.get_direction	= axp20x_gpio_get_direction;
	pctl->chip.set			= axp20x_gpio_set;
	pctl->chip.direction_input	= axp20x_gpio_input;
	pctl->chip.direction_output	= axp20x_gpio_output;

	pctl->desc = of_device_get_match_data(dev);

	pctl->chip.ngpio		= pctl->desc->npins;

	pctl->regmap = axp20x->regmap;
	pctl->dev = &pdev->dev;

	platform_set_drvdata(pdev, pctl);

	ret = axp20x_build_funcs_groups(pdev);
	if (ret) {
		dev_err(&pdev->dev, "failed to build groups\n");
		return ret;
	}

	pctrl_desc = devm_kzalloc(&pdev->dev, sizeof(*pctrl_desc), GFP_KERNEL);
	if (!pctrl_desc)
		return -ENOMEM;

	pctrl_desc->name = dev_name(&pdev->dev);
	pctrl_desc->owner = THIS_MODULE;
	pctrl_desc->pins = pctl->desc->pins;
	pctrl_desc->npins = pctl->desc->npins;
	pctrl_desc->pctlops = &axp20x_pctrl_ops;
	pctrl_desc->pmxops = &axp20x_pmx_ops;

	pctl->pctl_dev = devm_pinctrl_register(&pdev->dev, pctrl_desc, pctl);
	if (IS_ERR(pctl->pctl_dev)) {
		dev_err(&pdev->dev, "couldn't register pinctrl driver\n");
		return PTR_ERR(pctl->pctl_dev);
	}

	ret = devm_gpiochip_add_data(&pdev->dev, &pctl->chip, pctl);
	if (ret) {
		dev_err(&pdev->dev, "Failed to register GPIO chip\n");
		return ret;
	}

	ret = gpiochip_add_pin_range(&pctl->chip, dev_name(&pdev->dev),
				     pctl->desc->pins->number,
				     pctl->desc->pins->number,
				     pctl->desc->npins);
	if (ret) {
		dev_err(&pdev->dev, "failed to add pin range\n");
		return ret;
	}

	dev_info(&pdev->dev, "AXP209 pinctrl and GPIO driver loaded\n");

	return 0;
}