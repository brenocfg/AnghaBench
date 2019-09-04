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
struct regmap {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw; struct regmap* regmap; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 TYPE_1__ cec_32k_ao ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int devm_clk_hw_register (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_get_parent (int /*<<< orphan*/ ) ; 
 struct regmap* syscon_node_to_regmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gxbb_register_cec_ao_32k(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct regmap *regmap;
	int ret;

	regmap = syscon_node_to_regmap(of_get_parent(dev->of_node));
	if (IS_ERR(regmap)) {
		dev_err(dev, "failed to get regmap\n");
		return PTR_ERR(regmap);
	}

	/* Specific clocks */
	cec_32k_ao.regmap = regmap;
	ret = devm_clk_hw_register(dev, &cec_32k_ao.hw);
	if (ret) {
		dev_err(&pdev->dev, "clk cec_32k_ao register failed.\n");
		return ret;
	}

	return 0;
}