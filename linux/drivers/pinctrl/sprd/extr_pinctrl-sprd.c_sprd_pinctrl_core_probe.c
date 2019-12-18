#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sprd_pins_info {int dummy; } ;
struct sprd_pinctrl_soc_info {int npins; TYPE_1__* pins; } ;
struct sprd_pinctrl {int /*<<< orphan*/  pctl; int /*<<< orphan*/ * dev; struct sprd_pinctrl_soc_info* info; int /*<<< orphan*/  base; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct pinctrl_pin_desc {struct sprd_pinctrl_soc_info* drv_data; int /*<<< orphan*/  name; int /*<<< orphan*/  number; } ;
struct TYPE_5__ {int npins; int /*<<< orphan*/  name; struct pinctrl_pin_desc* pins; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 struct pinctrl_pin_desc* devm_kcalloc (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 void* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pinctrl_register (TYPE_2__*,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sprd_pinctrl*) ; 
 int sprd_pinctrl_add_pins (struct sprd_pinctrl*,struct sprd_pins_info*,int) ; 
 TYPE_2__ sprd_pinctrl_desc ; 
 int sprd_pinctrl_parse_dt (struct sprd_pinctrl*) ; 

int sprd_pinctrl_core_probe(struct platform_device *pdev,
			    struct sprd_pins_info *sprd_soc_pin_info,
			    int pins_cnt)
{
	struct sprd_pinctrl *sprd_pctl;
	struct sprd_pinctrl_soc_info *pinctrl_info;
	struct pinctrl_pin_desc *pin_desc;
	int ret, i;

	sprd_pctl = devm_kzalloc(&pdev->dev, sizeof(struct sprd_pinctrl),
				 GFP_KERNEL);
	if (!sprd_pctl)
		return -ENOMEM;

	sprd_pctl->base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(sprd_pctl->base))
		return PTR_ERR(sprd_pctl->base);

	pinctrl_info = devm_kzalloc(&pdev->dev,
				    sizeof(struct sprd_pinctrl_soc_info),
				    GFP_KERNEL);
	if (!pinctrl_info)
		return -ENOMEM;

	sprd_pctl->info = pinctrl_info;
	sprd_pctl->dev = &pdev->dev;
	platform_set_drvdata(pdev, sprd_pctl);

	ret = sprd_pinctrl_add_pins(sprd_pctl, sprd_soc_pin_info, pins_cnt);
	if (ret) {
		dev_err(&pdev->dev, "fail to add pins information\n");
		return ret;
	}

	ret = sprd_pinctrl_parse_dt(sprd_pctl);
	if (ret) {
		dev_err(&pdev->dev, "fail to parse dt properties\n");
		return ret;
	}

	pin_desc = devm_kcalloc(&pdev->dev,
				pinctrl_info->npins,
				sizeof(struct pinctrl_pin_desc),
				GFP_KERNEL);
	if (!pin_desc)
		return -ENOMEM;

	for (i = 0; i < pinctrl_info->npins; i++) {
		pin_desc[i].number = pinctrl_info->pins[i].number;
		pin_desc[i].name = pinctrl_info->pins[i].name;
		pin_desc[i].drv_data = pinctrl_info;
	}

	sprd_pinctrl_desc.pins = pin_desc;
	sprd_pinctrl_desc.name = dev_name(&pdev->dev);
	sprd_pinctrl_desc.npins = pinctrl_info->npins;

	sprd_pctl->pctl = pinctrl_register(&sprd_pinctrl_desc,
					   &pdev->dev, (void *)sprd_pctl);
	if (IS_ERR(sprd_pctl->pctl)) {
		dev_err(&pdev->dev, "could not register pinctrl driver\n");
		return PTR_ERR(sprd_pctl->pctl);
	}

	return 0;
}