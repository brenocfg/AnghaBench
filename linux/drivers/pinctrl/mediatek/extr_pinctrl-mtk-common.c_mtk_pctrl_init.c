#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct regmap {int dummy; } ;
struct property {int dummy; } ;
struct TYPE_14__ {struct device_node* of_node; } ;
struct platform_device {TYPE_6__ dev; } ;
struct pinctrl_pin_desc {int dummy; } ;
struct mtk_pinctrl_devdata {int npins; TYPE_1__* pins; } ;
struct TYPE_15__ {int npins; int /*<<< orphan*/ * pmxops; int /*<<< orphan*/ * pctlops; int /*<<< orphan*/ * confops; struct pinctrl_pin_desc* pins; int /*<<< orphan*/  owner; void* name; } ;
struct mtk_pinctrl {TYPE_2__* chip; struct mtk_pinctrl_devdata const* devdata; struct regmap* pctl_dev; TYPE_7__ pctl_desc; TYPE_6__* dev; struct regmap* regmap2; struct regmap* regmap1; } ;
struct device_node {int dummy; } ;
struct TYPE_13__ {int ngpio; int base; TYPE_6__* parent; void* label; } ;
struct TYPE_12__ {struct pinctrl_pin_desc pin; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (TYPE_6__*,char*,...) ; 
 void* dev_name (TYPE_6__*) ; 
 struct pinctrl_pin_desc* devm_kcalloc (TYPE_6__*,int,int,int /*<<< orphan*/ ) ; 
 void* devm_kzalloc (TYPE_6__*,int,int /*<<< orphan*/ ) ; 
 struct regmap* devm_pinctrl_register (TYPE_6__*,TYPE_7__*,struct mtk_pinctrl*) ; 
 int gpiochip_add_data (TYPE_2__*,struct mtk_pinctrl*) ; 
 int gpiochip_add_pin_range (TYPE_2__*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpiochip_remove (TYPE_2__*) ; 
 int mtk_eint_init (struct mtk_pinctrl*,struct platform_device*) ; 
 TYPE_2__ mtk_gpio_chip ; 
 int /*<<< orphan*/  mtk_pconf_ops ; 
 int mtk_pctrl_build_state (struct platform_device*) ; 
 int /*<<< orphan*/  mtk_pctrl_ops ; 
 int /*<<< orphan*/  mtk_pmx_ops ; 
 struct property* of_find_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mtk_pinctrl*) ; 
 void* syscon_node_to_regmap (struct device_node*) ; 

int mtk_pctrl_init(struct platform_device *pdev,
		const struct mtk_pinctrl_devdata *data,
		struct regmap *regmap)
{
	struct pinctrl_pin_desc *pins;
	struct mtk_pinctrl *pctl;
	struct device_node *np = pdev->dev.of_node, *node;
	struct property *prop;
	int ret, i;

	pctl = devm_kzalloc(&pdev->dev, sizeof(*pctl), GFP_KERNEL);
	if (!pctl)
		return -ENOMEM;

	platform_set_drvdata(pdev, pctl);

	prop = of_find_property(np, "pins-are-numbered", NULL);
	if (!prop) {
		dev_err(&pdev->dev, "only support pins-are-numbered format\n");
		return -EINVAL;
	}

	node = of_parse_phandle(np, "mediatek,pctl-regmap", 0);
	if (node) {
		pctl->regmap1 = syscon_node_to_regmap(node);
		if (IS_ERR(pctl->regmap1))
			return PTR_ERR(pctl->regmap1);
	} else if (regmap) {
		pctl->regmap1  = regmap;
	} else {
		dev_err(&pdev->dev, "Pinctrl node has not register regmap.\n");
		return -EINVAL;
	}

	/* Only 8135 has two base addr, other SoCs have only one. */
	node = of_parse_phandle(np, "mediatek,pctl-regmap", 1);
	if (node) {
		pctl->regmap2 = syscon_node_to_regmap(node);
		if (IS_ERR(pctl->regmap2))
			return PTR_ERR(pctl->regmap2);
	}

	pctl->devdata = data;
	ret = mtk_pctrl_build_state(pdev);
	if (ret) {
		dev_err(&pdev->dev, "build state failed: %d\n", ret);
		return -EINVAL;
	}

	pins = devm_kcalloc(&pdev->dev, pctl->devdata->npins, sizeof(*pins),
			    GFP_KERNEL);
	if (!pins)
		return -ENOMEM;

	for (i = 0; i < pctl->devdata->npins; i++)
		pins[i] = pctl->devdata->pins[i].pin;

	pctl->pctl_desc.name = dev_name(&pdev->dev);
	pctl->pctl_desc.owner = THIS_MODULE;
	pctl->pctl_desc.pins = pins;
	pctl->pctl_desc.npins = pctl->devdata->npins;
	pctl->pctl_desc.confops = &mtk_pconf_ops;
	pctl->pctl_desc.pctlops = &mtk_pctrl_ops;
	pctl->pctl_desc.pmxops = &mtk_pmx_ops;
	pctl->dev = &pdev->dev;

	pctl->pctl_dev = devm_pinctrl_register(&pdev->dev, &pctl->pctl_desc,
					       pctl);
	if (IS_ERR(pctl->pctl_dev)) {
		dev_err(&pdev->dev, "couldn't register pinctrl driver\n");
		return PTR_ERR(pctl->pctl_dev);
	}

	pctl->chip = devm_kzalloc(&pdev->dev, sizeof(*pctl->chip), GFP_KERNEL);
	if (!pctl->chip)
		return -ENOMEM;

	*pctl->chip = mtk_gpio_chip;
	pctl->chip->ngpio = pctl->devdata->npins;
	pctl->chip->label = dev_name(&pdev->dev);
	pctl->chip->parent = &pdev->dev;
	pctl->chip->base = -1;

	ret = gpiochip_add_data(pctl->chip, pctl);
	if (ret)
		return -EINVAL;

	/* Register the GPIO to pin mappings. */
	ret = gpiochip_add_pin_range(pctl->chip, dev_name(&pdev->dev),
			0, 0, pctl->devdata->npins);
	if (ret) {
		ret = -EINVAL;
		goto chip_error;
	}

	ret = mtk_eint_init(pctl, pdev);
	if (ret)
		goto chip_error;

	return 0;

chip_error:
	gpiochip_remove(pctl->chip);
	return ret;
}