#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct regulator_init_data {int dummy; } ;
struct regulator_dev {int dummy; } ;
struct regulator_config {TYPE_2__* driver_data; struct regulator_init_data* init_data; int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; } ;
struct pm80x_platform_data {unsigned int num_regulators; struct regulator_init_data** regulators; } ;
struct pm80x_chip {TYPE_1__* subchip; int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_3__ dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {TYPE_4__ desc; } ;
struct TYPE_6__ {int /*<<< orphan*/  regmap_power; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct regulator_init_data**) ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 int PM800_ID_RG_MAX ; 
 int PTR_ERR (struct regulator_dev*) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 struct pm80x_chip* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct pm80x_platform_data* dev_get_platdata (int /*<<< orphan*/ ) ; 
 struct regulator_dev* devm_regulator_register (TYPE_3__*,TYPE_4__*,struct regulator_config*) ; 
 TYPE_2__* pm800_regulator_info ; 

__attribute__((used)) static int pm800_regulator_probe(struct platform_device *pdev)
{
	struct pm80x_chip *chip = dev_get_drvdata(pdev->dev.parent);
	struct pm80x_platform_data *pdata = dev_get_platdata(pdev->dev.parent);
	struct regulator_config config = { };
	struct regulator_init_data *init_data;
	int i, ret;

	if (pdata && pdata->num_regulators) {
		unsigned int count = 0;

		/* Check whether num_regulator is valid. */
		for (i = 0; i < ARRAY_SIZE(pdata->regulators); i++) {
			if (pdata->regulators[i])
				count++;
		}
		if (count != pdata->num_regulators)
			return -EINVAL;
	}

	config.dev = chip->dev;
	config.regmap = chip->subchip->regmap_power;
	for (i = 0; i < PM800_ID_RG_MAX; i++) {
		struct regulator_dev *regulator;

		if (pdata && pdata->num_regulators) {
			init_data = pdata->regulators[i];
			if (!init_data)
				continue;

			config.init_data = init_data;
		}

		config.driver_data = &pm800_regulator_info[i];

		regulator = devm_regulator_register(&pdev->dev,
				&pm800_regulator_info[i].desc, &config);
		if (IS_ERR(regulator)) {
			ret = PTR_ERR(regulator);
			dev_err(&pdev->dev, "Failed to register %s\n",
					pm800_regulator_info[i].desc.name);
			return ret;
		}
	}

	return 0;
}