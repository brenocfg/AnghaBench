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
struct regulator_init_data {int dummy; } ;
struct regulator_dev {int dummy; } ;
struct regulator_config {int /*<<< orphan*/  regmap; int /*<<< orphan*/  of_node; struct regulator_init_data const* init_data; int /*<<< orphan*/  dev; } ;
struct device {int /*<<< orphan*/  parent; int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 int PTR_ERR (struct regulator_dev*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct regulator_init_data* dev_get_platdata (struct device*) ; 
 struct regulator_dev* devm_regulator_register (struct device*,int /*<<< orphan*/ *,struct regulator_config*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct regulator_dev*) ; 
 int /*<<< orphan*/  sky81452_reg ; 

__attribute__((used)) static int sky81452_reg_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	const struct regulator_init_data *init_data = dev_get_platdata(dev);
	struct regulator_config config = { };
	struct regulator_dev *rdev;

	config.dev = dev->parent;
	config.init_data = init_data;
	config.of_node = dev->of_node;
	config.regmap = dev_get_drvdata(dev->parent);

	rdev = devm_regulator_register(dev, &sky81452_reg, &config);
	if (IS_ERR(rdev)) {
		dev_err(dev, "failed to register. err=%ld\n", PTR_ERR(rdev));
		return PTR_ERR(rdev);
	}

	platform_set_drvdata(pdev, rdev);

	return 0;
}