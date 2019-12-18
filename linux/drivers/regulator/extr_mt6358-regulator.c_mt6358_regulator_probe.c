#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct regulator_dev {int dummy; } ;
struct regulator_config {int /*<<< orphan*/  regmap; TYPE_1__* driver_data; TYPE_2__* dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_2__ dev; } ;
struct mt6397_chip {int /*<<< orphan*/  regmap; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {TYPE_3__ desc; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 int MT6358_MAX_REGULATOR ; 
 int PTR_ERR (struct regulator_dev*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 struct mt6397_chip* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct regulator_dev* devm_regulator_register (TYPE_2__*,TYPE_3__*,struct regulator_config*) ; 
 TYPE_1__* mt6358_regulators ; 

__attribute__((used)) static int mt6358_regulator_probe(struct platform_device *pdev)
{
	struct mt6397_chip *mt6397 = dev_get_drvdata(pdev->dev.parent);
	struct regulator_config config = {};
	struct regulator_dev *rdev;
	int i;

	for (i = 0; i < MT6358_MAX_REGULATOR; i++) {
		config.dev = &pdev->dev;
		config.driver_data = &mt6358_regulators[i];
		config.regmap = mt6397->regmap;

		rdev = devm_regulator_register(&pdev->dev,
					       &mt6358_regulators[i].desc,
					       &config);
		if (IS_ERR(rdev)) {
			dev_err(&pdev->dev, "failed to register %s\n",
				mt6358_regulators[i].desc.name);
			return PTR_ERR(rdev);
		}
	}

	return 0;
}