#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct regulator_dev {int dummy; } ;
struct regulator_config {int /*<<< orphan*/  regmap; struct lp87565* driver_data; TYPE_2__* dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  of_node; int /*<<< orphan*/  parent; } ;
struct platform_device {int /*<<< orphan*/  name; TYPE_2__ dev; } ;
struct lp87565 {int dev_type; TYPE_3__* dev; int /*<<< orphan*/  regmap; } ;
struct TYPE_6__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_4__ {int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 int LP87565_BUCK_0 ; 
 int LP87565_BUCK_10 ; 
 int LP87565_BUCK_23 ; 
 int LP87565_BUCK_3 ; 
 int LP87565_BUCK_3210 ; 
#define  LP87565_DEVICE_TYPE_LP87561_Q1 129 
#define  LP87565_DEVICE_TYPE_LP87565_Q1 128 
 int PTR_ERR (struct regulator_dev*) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 struct lp87565* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct regulator_dev* devm_regulator_register (TYPE_2__*,int /*<<< orphan*/ *,struct regulator_config*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct lp87565*) ; 
 TYPE_1__* regulators ; 

__attribute__((used)) static int lp87565_regulator_probe(struct platform_device *pdev)
{
	struct lp87565 *lp87565 = dev_get_drvdata(pdev->dev.parent);
	struct regulator_config config = { };
	struct regulator_dev *rdev;
	int i, min_idx, max_idx;

	platform_set_drvdata(pdev, lp87565);

	config.dev = &pdev->dev;
	config.dev->of_node = lp87565->dev->of_node;
	config.driver_data = lp87565;
	config.regmap = lp87565->regmap;

	switch (lp87565->dev_type) {
	case LP87565_DEVICE_TYPE_LP87565_Q1:
		min_idx = LP87565_BUCK_10;
		max_idx = LP87565_BUCK_23;
		break;
	case LP87565_DEVICE_TYPE_LP87561_Q1:
		min_idx = LP87565_BUCK_3210;
		max_idx = LP87565_BUCK_3210;
		break;
	default:
		min_idx = LP87565_BUCK_0;
		max_idx = LP87565_BUCK_3;
		break;
	}

	for (i = min_idx; i <= max_idx; i++) {
		rdev = devm_regulator_register(&pdev->dev, &regulators[i].desc,
					       &config);
		if (IS_ERR(rdev)) {
			dev_err(lp87565->dev, "failed to register %s regulator\n",
				pdev->name);
			return PTR_ERR(rdev);
		}
	}

	return 0;
}