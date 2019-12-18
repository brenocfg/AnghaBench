#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_8__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct pinctrl_desc {scalar_t__ npins; scalar_t__ pins; int /*<<< orphan*/  name; } ;
struct imx1_pinctrl_soc_info {TYPE_1__* dev; scalar_t__ npins; scalar_t__ pins; } ;
struct imx1_pinctrl {int /*<<< orphan*/  pctl; TYPE_1__* dev; struct imx1_pinctrl_soc_info* info; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 int /*<<< orphan*/  devm_ioremap_nocache (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct imx1_pinctrl* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_pinctrl_register (TYPE_1__*,struct pinctrl_desc*,struct imx1_pinctrl*) ; 
 struct pinctrl_desc imx1_pinctrl_desc ; 
 int imx1_pinctrl_parse_dt (struct platform_device*,struct imx1_pinctrl*,struct imx1_pinctrl_soc_info*) ; 
 int of_platform_populate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  pinctrl_unregister (int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct imx1_pinctrl*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

int imx1_pinctrl_core_probe(struct platform_device *pdev,
		      struct imx1_pinctrl_soc_info *info)
{
	struct imx1_pinctrl *ipctl;
	struct resource *res;
	struct pinctrl_desc *pctl_desc;
	int ret;

	if (!info || !info->pins || !info->npins) {
		dev_err(&pdev->dev, "wrong pinctrl info\n");
		return -EINVAL;
	}
	info->dev = &pdev->dev;

	/* Create state holders etc for this driver */
	ipctl = devm_kzalloc(&pdev->dev, sizeof(*ipctl), GFP_KERNEL);
	if (!ipctl)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res)
		return -ENOENT;

	ipctl->base = devm_ioremap_nocache(&pdev->dev, res->start,
			resource_size(res));
	if (!ipctl->base)
		return -ENOMEM;

	pctl_desc = &imx1_pinctrl_desc;
	pctl_desc->name = dev_name(&pdev->dev);
	pctl_desc->pins = info->pins;
	pctl_desc->npins = info->npins;

	ret = imx1_pinctrl_parse_dt(pdev, ipctl, info);
	if (ret) {
		dev_err(&pdev->dev, "fail to probe dt properties\n");
		return ret;
	}

	ipctl->info = info;
	ipctl->dev = info->dev;
	platform_set_drvdata(pdev, ipctl);
	ipctl->pctl = devm_pinctrl_register(&pdev->dev, pctl_desc, ipctl);
	if (IS_ERR(ipctl->pctl)) {
		dev_err(&pdev->dev, "could not register IMX pinctrl driver\n");
		return PTR_ERR(ipctl->pctl);
	}

	ret = of_platform_populate(pdev->dev.of_node, NULL, NULL, &pdev->dev);
	if (ret) {
		pinctrl_unregister(ipctl->pctl);
		dev_err(&pdev->dev, "Failed to populate subdevices\n");
		return ret;
	}

	dev_info(&pdev->dev, "initialized IMX pinctrl driver\n");

	return 0;
}