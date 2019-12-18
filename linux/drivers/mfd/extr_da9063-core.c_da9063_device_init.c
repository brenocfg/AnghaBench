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
struct da9063 {int irq_base; unsigned int chip_irq; int variant_code; scalar_t__ type; int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap_irq; int /*<<< orphan*/  regmap; scalar_t__ flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int DA9063_CHIP_VARIANT_SHIFT ; 
 int /*<<< orphan*/  DA9063_REG_CHIP_ID ; 
 int /*<<< orphan*/  DA9063_REG_CHIP_VARIANT ; 
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  PLATFORM_DEVID_NONE ; 
 int PMIC_CHIP_ID_DA9063 ; 
 int PMIC_DA9063_AD ; 
 int PMIC_DA9063_BB ; 
 scalar_t__ PMIC_TYPE_DA9063 ; 
 int da9063_clear_fault_log (struct da9063*) ; 
 int /*<<< orphan*/  da9063_common_devs ; 
 int /*<<< orphan*/  da9063_devs ; 
 int da9063_irq_init (struct da9063*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int,int) ; 
 int devm_mfd_add_devices (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int regmap_irq_chip_get_base (int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

int da9063_device_init(struct da9063 *da9063, unsigned int irq)
{
	int model, variant_id, variant_code;
	int ret;

	ret = da9063_clear_fault_log(da9063);
	if (ret < 0)
		dev_err(da9063->dev, "Cannot clear fault log\n");

	da9063->flags = 0;
	da9063->irq_base = -1;
	da9063->chip_irq = irq;

	ret = regmap_read(da9063->regmap, DA9063_REG_CHIP_ID, &model);
	if (ret < 0) {
		dev_err(da9063->dev, "Cannot read chip model id.\n");
		return -EIO;
	}
	if (model != PMIC_CHIP_ID_DA9063) {
		dev_err(da9063->dev, "Invalid chip model id: 0x%02x\n", model);
		return -ENODEV;
	}

	ret = regmap_read(da9063->regmap, DA9063_REG_CHIP_VARIANT, &variant_id);
	if (ret < 0) {
		dev_err(da9063->dev, "Cannot read chip variant id.\n");
		return -EIO;
	}

	variant_code = variant_id >> DA9063_CHIP_VARIANT_SHIFT;

	dev_info(da9063->dev,
		 "Device detected (chip-ID: 0x%02X, var-ID: 0x%02X)\n",
		 model, variant_id);

	if (variant_code < PMIC_DA9063_BB && variant_code != PMIC_DA9063_AD) {
		dev_err(da9063->dev,
			"Cannot support variant code: 0x%02X\n", variant_code);
		return -ENODEV;
	}

	da9063->variant_code = variant_code;

	ret = da9063_irq_init(da9063);
	if (ret) {
		dev_err(da9063->dev, "Cannot initialize interrupts.\n");
		return ret;
	}

	da9063->irq_base = regmap_irq_chip_get_base(da9063->regmap_irq);

	ret = devm_mfd_add_devices(da9063->dev, PLATFORM_DEVID_NONE,
				   da9063_common_devs,
				   ARRAY_SIZE(da9063_common_devs),
				   NULL, da9063->irq_base, NULL);
	if (ret) {
		dev_err(da9063->dev, "Failed to add child devices\n");
		return ret;
	}

	if (da9063->type == PMIC_TYPE_DA9063) {
		ret = devm_mfd_add_devices(da9063->dev, PLATFORM_DEVID_NONE,
					   da9063_devs, ARRAY_SIZE(da9063_devs),
					   NULL, da9063->irq_base, NULL);
		if (ret) {
			dev_err(da9063->dev, "Failed to add child devices\n");
			return ret;
		}
	}

	return ret;
}