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
struct regmap {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int devm_clk_hw_register (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_mdm9615_desc ; 
 int /*<<< orphan*/ * gcc_mdm9615_hws ; 
 struct regmap* qcom_cc_map (struct platform_device*,int /*<<< orphan*/ *) ; 
 int qcom_cc_really_probe (struct platform_device*,int /*<<< orphan*/ *,struct regmap*) ; 

__attribute__((used)) static int gcc_mdm9615_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct regmap *regmap;
	int ret;
	int i;

	regmap = qcom_cc_map(pdev, &gcc_mdm9615_desc);
	if (IS_ERR(regmap))
		return PTR_ERR(regmap);

	for (i = 0; i < ARRAY_SIZE(gcc_mdm9615_hws); i++) {
		ret = devm_clk_hw_register(dev, gcc_mdm9615_hws[i]);
		if (ret)
			return ret;
	}

	return qcom_cc_really_probe(pdev, &gcc_mdm9615_desc, regmap);
}