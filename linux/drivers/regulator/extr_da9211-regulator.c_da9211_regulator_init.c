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
struct regulator_config {int /*<<< orphan*/ * ena_gpiod; int /*<<< orphan*/  of_node; int /*<<< orphan*/  regmap; struct da9211* driver_data; int /*<<< orphan*/  dev; int /*<<< orphan*/  init_data; } ;
struct da9211 {int num_regulator; scalar_t__ chip_irq; int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; int /*<<< orphan*/ * rdev; TYPE_1__* pdata; } ;
struct TYPE_2__ {int num_buck; int /*<<< orphan*/ ** gpiod_ren; int /*<<< orphan*/ * reg_node; int /*<<< orphan*/ * init_data; } ;

/* Variables and functions */
 int DA9211_M_OV_CURR_A ; 
 int /*<<< orphan*/  DA9211_REG_CONFIG_E ; 
 int /*<<< orphan*/  DA9211_REG_MASK_B ; 
 unsigned int DA9211_SLAVE_SEL ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * da9211_regulators ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  devm_gpiod_unhinge (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_regulator_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct regulator_config*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da9211_regulator_init(struct da9211 *chip)
{
	struct regulator_config config = { };
	int i, ret;
	unsigned int data;

	ret = regmap_read(chip->regmap, DA9211_REG_CONFIG_E, &data);
	if (ret < 0) {
		dev_err(chip->dev, "Failed to read CONFIG_E reg: %d\n", ret);
		return ret;
	}

	data &= DA9211_SLAVE_SEL;
	/* If configuration for 1/2 bucks is different between platform data
	 * and the register, driver should exit.
	 */
	if (chip->pdata->num_buck == 1 && data == 0x00)
		chip->num_regulator = 1;
	else if (chip->pdata->num_buck == 2 && data != 0x00)
		chip->num_regulator = 2;
	else {
		dev_err(chip->dev, "Configuration is mismatched\n");
		return -EINVAL;
	}

	for (i = 0; i < chip->num_regulator; i++) {
		config.init_data = chip->pdata->init_data[i];
		config.dev = chip->dev;
		config.driver_data = chip;
		config.regmap = chip->regmap;
		config.of_node = chip->pdata->reg_node[i];

		if (chip->pdata->gpiod_ren[i])
			config.ena_gpiod = chip->pdata->gpiod_ren[i];
		else
			config.ena_gpiod = NULL;

		/*
		 * Hand the GPIO descriptor management over to the regulator
		 * core, remove it from GPIO devres management.
		 */
		if (config.ena_gpiod)
			devm_gpiod_unhinge(chip->dev, config.ena_gpiod);
		chip->rdev[i] = devm_regulator_register(chip->dev,
			&da9211_regulators[i], &config);
		if (IS_ERR(chip->rdev[i])) {
			dev_err(chip->dev,
				"Failed to register DA9211 regulator\n");
			return PTR_ERR(chip->rdev[i]);
		}

		if (chip->chip_irq != 0) {
			ret = regmap_update_bits(chip->regmap,
				DA9211_REG_MASK_B, DA9211_M_OV_CURR_A << i, 0);
			if (ret < 0) {
				dev_err(chip->dev,
					"Failed to update mask reg: %d\n", ret);
				return ret;
			}
		}
	}

	return 0;
}