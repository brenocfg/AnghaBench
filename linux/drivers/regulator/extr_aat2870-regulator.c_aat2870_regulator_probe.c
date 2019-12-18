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
struct regulator_dev {int dummy; } ;
struct regulator_config {int /*<<< orphan*/  init_data; struct aat2870_regulator* driver_data; TYPE_1__* dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; int /*<<< orphan*/  id; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct aat2870_regulator {TYPE_2__ desc; int /*<<< orphan*/  aat2870; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 int PTR_ERR (struct regulator_dev*) ; 
 struct aat2870_regulator* aat2870_get_regulator (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_get_platdata (TYPE_1__*) ; 
 struct regulator_dev* devm_regulator_register (TYPE_1__*,TYPE_2__*,struct regulator_config*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct regulator_dev*) ; 

__attribute__((used)) static int aat2870_regulator_probe(struct platform_device *pdev)
{
	struct aat2870_regulator *ri;
	struct regulator_config config = { };
	struct regulator_dev *rdev;

	ri = aat2870_get_regulator(pdev->id);
	if (!ri) {
		dev_err(&pdev->dev, "Invalid device ID, %d\n", pdev->id);
		return -EINVAL;
	}
	ri->aat2870 = dev_get_drvdata(pdev->dev.parent);

	config.dev = &pdev->dev;
	config.driver_data = ri;
	config.init_data = dev_get_platdata(&pdev->dev);

	rdev = devm_regulator_register(&pdev->dev, &ri->desc, &config);
	if (IS_ERR(rdev)) {
		dev_err(&pdev->dev, "Failed to register regulator %s\n",
			ri->desc.name);
		return PTR_ERR(rdev);
	}
	platform_set_drvdata(pdev, rdev);

	return 0;
}