#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pinctrl_desc {char* name; int /*<<< orphan*/  npins; struct pinctrl_pin_desc* pins; int /*<<< orphan*/ * confops; int /*<<< orphan*/ * pmxops; int /*<<< orphan*/ * pctlops; int /*<<< orphan*/  owner; } ;
struct rockchip_pinctrl {int /*<<< orphan*/  pctl_dev; TYPE_1__* ctrl; struct pinctrl_desc pctl; } ;
struct TYPE_6__ {int id; TYPE_2__* gc; int /*<<< orphan*/  npins; int /*<<< orphan*/  base; int /*<<< orphan*/  pin_base; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  ngpio; int /*<<< orphan*/  base; } ;
struct rockchip_pin_bank {int nr_pins; TYPE_3__ grange; TYPE_2__ gpio_chip; int /*<<< orphan*/  pin_base; int /*<<< orphan*/  name; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct pinctrl_pin_desc {int number; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int nr_banks; struct rockchip_pin_bank* pin_banks; int /*<<< orphan*/  nr_pins; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct pinctrl_pin_desc* devm_kcalloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_pinctrl_register (int /*<<< orphan*/ *,struct pinctrl_desc*,struct rockchip_pinctrl*) ; 
 int /*<<< orphan*/  kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pinctrl_add_gpio_range (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  rockchip_pctrl_ops ; 
 int /*<<< orphan*/  rockchip_pinconf_ops ; 
 int rockchip_pinctrl_parse_dt (struct platform_device*,struct rockchip_pinctrl*) ; 
 int /*<<< orphan*/  rockchip_pmx_ops ; 

__attribute__((used)) static int rockchip_pinctrl_register(struct platform_device *pdev,
					struct rockchip_pinctrl *info)
{
	struct pinctrl_desc *ctrldesc = &info->pctl;
	struct pinctrl_pin_desc *pindesc, *pdesc;
	struct rockchip_pin_bank *pin_bank;
	int pin, bank, ret;
	int k;

	ctrldesc->name = "rockchip-pinctrl";
	ctrldesc->owner = THIS_MODULE;
	ctrldesc->pctlops = &rockchip_pctrl_ops;
	ctrldesc->pmxops = &rockchip_pmx_ops;
	ctrldesc->confops = &rockchip_pinconf_ops;

	pindesc = devm_kcalloc(&pdev->dev,
			       info->ctrl->nr_pins, sizeof(*pindesc),
			       GFP_KERNEL);
	if (!pindesc)
		return -ENOMEM;

	ctrldesc->pins = pindesc;
	ctrldesc->npins = info->ctrl->nr_pins;

	pdesc = pindesc;
	for (bank = 0 , k = 0; bank < info->ctrl->nr_banks; bank++) {
		pin_bank = &info->ctrl->pin_banks[bank];
		for (pin = 0; pin < pin_bank->nr_pins; pin++, k++) {
			pdesc->number = k;
			pdesc->name = kasprintf(GFP_KERNEL, "%s-%d",
						pin_bank->name, pin);
			pdesc++;
		}
	}

	ret = rockchip_pinctrl_parse_dt(pdev, info);
	if (ret)
		return ret;

	info->pctl_dev = devm_pinctrl_register(&pdev->dev, ctrldesc, info);
	if (IS_ERR(info->pctl_dev)) {
		dev_err(&pdev->dev, "could not register pinctrl driver\n");
		return PTR_ERR(info->pctl_dev);
	}

	for (bank = 0; bank < info->ctrl->nr_banks; ++bank) {
		pin_bank = &info->ctrl->pin_banks[bank];
		pin_bank->grange.name = pin_bank->name;
		pin_bank->grange.id = bank;
		pin_bank->grange.pin_base = pin_bank->pin_base;
		pin_bank->grange.base = pin_bank->gpio_chip.base;
		pin_bank->grange.npins = pin_bank->gpio_chip.ngpio;
		pin_bank->grange.gc = &pin_bank->gpio_chip;
		pinctrl_add_gpio_range(info->pctl_dev, &pin_bank->grange);
	}

	return 0;
}