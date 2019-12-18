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
struct TYPE_5__ {struct device* parent; } ;
struct platform_device {TYPE_2__ dev; } ;
struct pinctrl_dev {int dummy; } ;
struct pinctrl_desc {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct TYPE_4__ {struct pinctrl_dev** maps; } ;
struct aspeed_pinctrl_data {struct pinctrl_dev* scu; TYPE_1__ pinmux; } ;

/* Variables and functions */
 size_t ASPEED_IP_SCU ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (struct pinctrl_dev*) ; 
 int PTR_ERR (struct pinctrl_dev*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 struct pinctrl_dev* pinctrl_register (struct pinctrl_desc*,TYPE_2__*,struct aspeed_pinctrl_data*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct aspeed_pinctrl_data*) ; 
 struct pinctrl_dev* syscon_node_to_regmap (int /*<<< orphan*/ ) ; 

int aspeed_pinctrl_probe(struct platform_device *pdev,
			 struct pinctrl_desc *pdesc,
			 struct aspeed_pinctrl_data *pdata)
{
	struct device *parent;
	struct pinctrl_dev *pctl;

	parent = pdev->dev.parent;
	if (!parent) {
		dev_err(&pdev->dev, "No parent for syscon pincontroller\n");
		return -ENODEV;
	}

	pdata->scu = syscon_node_to_regmap(parent->of_node);
	if (IS_ERR(pdata->scu)) {
		dev_err(&pdev->dev, "No regmap for syscon pincontroller parent\n");
		return PTR_ERR(pdata->scu);
	}

	pdata->pinmux.maps[ASPEED_IP_SCU] = pdata->scu;

	pctl = pinctrl_register(pdesc, &pdev->dev, pdata);

	if (IS_ERR(pctl)) {
		dev_err(&pdev->dev, "Failed to register pinctrl\n");
		return PTR_ERR(pctl);
	}

	platform_set_drvdata(pdev, pdata);

	return 0;
}