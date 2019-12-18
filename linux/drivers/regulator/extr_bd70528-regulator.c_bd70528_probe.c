#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct rohm_regmap_dev {int /*<<< orphan*/  regmap; } ;
struct regulator_dev {int dummy; } ;
struct regulator_config {int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 int PTR_ERR (struct regulator_dev*) ; 
 TYPE_2__* bd70528_desc ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 struct rohm_regmap_dev* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct regulator_dev* devm_regulator_register (TYPE_1__*,TYPE_2__*,struct regulator_config*) ; 

__attribute__((used)) static int bd70528_probe(struct platform_device *pdev)
{
	struct rohm_regmap_dev *bd70528;
	int i;
	struct regulator_config config = {
		.dev = pdev->dev.parent,
	};

	bd70528 = dev_get_drvdata(pdev->dev.parent);
	if (!bd70528) {
		dev_err(&pdev->dev, "No MFD driver data\n");
		return -EINVAL;
	}

	config.regmap = bd70528->regmap;

	for (i = 0; i < ARRAY_SIZE(bd70528_desc); i++) {
		struct regulator_dev *rdev;

		rdev = devm_regulator_register(&pdev->dev, &bd70528_desc[i],
					       &config);
		if (IS_ERR(rdev)) {
			dev_err(&pdev->dev,
				"failed to register %s regulator\n",
				bd70528_desc[i].name);
			return PTR_ERR(rdev);
		}
	}
	return 0;
}