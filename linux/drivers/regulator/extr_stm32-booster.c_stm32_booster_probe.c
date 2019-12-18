#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct regulator_dev {int dummy; } ;
struct regulator_desc {int dummy; } ;
struct regulator_config {int /*<<< orphan*/  init_data; struct device_node* of_node; struct device* dev; struct regulator_dev* regmap; } ;
typedef  struct regulator_dev regmap ;
struct device {TYPE_1__* driver; struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct device_node {int dummy; } ;
struct TYPE_4__ {scalar_t__ data; } ;
struct TYPE_3__ {int /*<<< orphan*/  of_match_table; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 int PTR_ERR (struct regulator_dev*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct regulator_dev* devm_regulator_register (struct device*,struct regulator_desc const*,struct regulator_config*) ; 
 int /*<<< orphan*/  of_get_regulator_init_data (struct device*,struct device_node*,struct regulator_desc const*) ; 
 TYPE_2__* of_match_device (int /*<<< orphan*/ ,struct device*) ; 
 struct regulator_dev* syscon_regmap_lookup_by_phandle (struct device_node*,char*) ; 

__attribute__((used)) static int stm32_booster_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = pdev->dev.of_node;
	struct regulator_config config = { };
	const struct regulator_desc *desc;
	struct regulator_dev *rdev;
	struct regmap *regmap;
	int ret;

	regmap = syscon_regmap_lookup_by_phandle(np, "st,syscfg");
	if (IS_ERR(regmap))
		return PTR_ERR(regmap);

	desc = (const struct regulator_desc *)
		of_match_device(dev->driver->of_match_table, dev)->data;

	config.regmap = regmap;
	config.dev = dev;
	config.of_node = np;
	config.init_data = of_get_regulator_init_data(dev, np, desc);

	rdev = devm_regulator_register(dev, desc, &config);
	if (IS_ERR(rdev)) {
		ret = PTR_ERR(rdev);
		dev_err(dev, "register failed with error %d\n", ret);
		return ret;
	}

	return 0;
}