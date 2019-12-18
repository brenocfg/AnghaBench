#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct resource {scalar_t__ start; } ;
struct regulator_init_data {int dummy; } ;
struct regulator_dev {int dummy; } ;
struct regulator_config {struct regulator_init_data* init_data; struct max8925_regulator_info* driver_data; int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct TYPE_6__ {unsigned long long name; } ;
struct max8925_regulator_info {scalar_t__ vol_reg; TYPE_2__ desc; int /*<<< orphan*/  i2c; } ;
struct max8925_chip {int /*<<< orphan*/  dev; int /*<<< orphan*/  i2c; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct max8925_regulator_info*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  IORESOURCE_REG ; 
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 int PTR_ERR (struct regulator_dev*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 struct max8925_chip* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct regulator_init_data* dev_get_platdata (TYPE_1__*) ; 
 struct regulator_dev* devm_regulator_register (TYPE_1__*,TYPE_2__*,struct regulator_config*) ; 
 struct max8925_regulator_info* max8925_regulator_info ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct regulator_dev*) ; 

__attribute__((used)) static int max8925_regulator_probe(struct platform_device *pdev)
{
	struct max8925_chip *chip = dev_get_drvdata(pdev->dev.parent);
	struct regulator_init_data *pdata = dev_get_platdata(&pdev->dev);
	struct regulator_config config = { };
	struct max8925_regulator_info *ri;
	struct resource *res;
	struct regulator_dev *rdev;
	int i;

	res = platform_get_resource(pdev, IORESOURCE_REG, 0);
	if (!res) {
		dev_err(&pdev->dev, "No REG resource!\n");
		return -EINVAL;
	}
	for (i = 0; i < ARRAY_SIZE(max8925_regulator_info); i++) {
		ri = &max8925_regulator_info[i];
		if (ri->vol_reg == res->start)
			break;
	}

	if (i == ARRAY_SIZE(max8925_regulator_info)) {
		dev_err(&pdev->dev, "Failed to find regulator %llu\n",
			(unsigned long long)res->start);
		return -EINVAL;
	}
	ri->i2c = chip->i2c;

	config.dev = chip->dev;
	config.driver_data = ri;

	if (pdata)
		config.init_data = pdata;

	rdev = devm_regulator_register(&pdev->dev, &ri->desc, &config);
	if (IS_ERR(rdev)) {
		dev_err(&pdev->dev, "failed to register regulator %s\n",
				ri->desc.name);
		return PTR_ERR(rdev);
	}

	platform_set_drvdata(pdev, rdev);
	return 0;
}