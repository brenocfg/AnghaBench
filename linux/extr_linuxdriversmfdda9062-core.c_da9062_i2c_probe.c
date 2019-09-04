#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct regmap_irq_chip {int dummy; } ;
struct regmap_config {int dummy; } ;
struct of_device_id {scalar_t__ data; } ;
struct mfd_cell {int dummy; } ;
struct i2c_device_id {uintptr_t driver_data; } ;
struct TYPE_5__ {scalar_t__ of_node; } ;
struct i2c_client {int /*<<< orphan*/  irq; TYPE_1__ dev; } ;
struct da9062 {uintptr_t chip_type; int /*<<< orphan*/  regmap_irq; TYPE_1__* dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct mfd_cell*) ; 
#define  COMPAT_TYPE_DA9061 129 
#define  COMPAT_TYPE_DA9062 128 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IRQF_ONESHOT ; 
 int IRQF_SHARED ; 
 int IRQF_TRIGGER_LOW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLATFORM_DEVID_NONE ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 struct mfd_cell* da9061_devs ; 
 struct regmap_irq_chip da9061_irq_chip ; 
 struct regmap_config da9061_regmap_config ; 
 int da9062_clear_fault_log (struct da9062*) ; 
 struct mfd_cell* da9062_devs ; 
 int /*<<< orphan*/  da9062_dt_ids ; 
 int da9062_get_device_type (struct da9062*) ; 
 struct regmap_irq_chip da9062_irq_chip ; 
 struct regmap_config da9062_regmap_config ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*) ; 
 struct da9062* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,struct regmap_config const*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct da9062*) ; 
 int mfd_add_devices (TYPE_1__*,int /*<<< orphan*/ ,struct mfd_cell const*,int,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *) ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,scalar_t__) ; 
 int regmap_add_irq_chip (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct regmap_irq_chip const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_del_irq_chip (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int regmap_irq_chip_get_base (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da9062_i2c_probe(struct i2c_client *i2c,
	const struct i2c_device_id *id)
{
	struct da9062 *chip;
	const struct of_device_id *match;
	unsigned int irq_base;
	const struct mfd_cell *cell;
	const struct regmap_irq_chip *irq_chip;
	const struct regmap_config *config;
	int cell_num;
	int ret;

	chip = devm_kzalloc(&i2c->dev, sizeof(*chip), GFP_KERNEL);
	if (!chip)
		return -ENOMEM;

	if (i2c->dev.of_node) {
		match = of_match_node(da9062_dt_ids, i2c->dev.of_node);
		if (!match)
			return -EINVAL;

		chip->chip_type = (uintptr_t)match->data;
	} else {
		chip->chip_type = id->driver_data;
	}

	i2c_set_clientdata(i2c, chip);
	chip->dev = &i2c->dev;

	if (!i2c->irq) {
		dev_err(chip->dev, "No IRQ configured\n");
		return -EINVAL;
	}

	switch (chip->chip_type) {
	case COMPAT_TYPE_DA9061:
		cell = da9061_devs;
		cell_num = ARRAY_SIZE(da9061_devs);
		irq_chip = &da9061_irq_chip;
		config = &da9061_regmap_config;
		break;
	case COMPAT_TYPE_DA9062:
		cell = da9062_devs;
		cell_num = ARRAY_SIZE(da9062_devs);
		irq_chip = &da9062_irq_chip;
		config = &da9062_regmap_config;
		break;
	default:
		dev_err(chip->dev, "Unrecognised chip type\n");
		return -ENODEV;
	}

	chip->regmap = devm_regmap_init_i2c(i2c, config);
	if (IS_ERR(chip->regmap)) {
		ret = PTR_ERR(chip->regmap);
		dev_err(chip->dev, "Failed to allocate register map: %d\n",
			ret);
		return ret;
	}

	ret = da9062_clear_fault_log(chip);
	if (ret < 0)
		dev_warn(chip->dev, "Cannot clear fault log\n");

	ret = da9062_get_device_type(chip);
	if (ret)
		return ret;

	ret = regmap_add_irq_chip(chip->regmap, i2c->irq,
			IRQF_TRIGGER_LOW | IRQF_ONESHOT | IRQF_SHARED,
			-1, irq_chip,
			&chip->regmap_irq);
	if (ret) {
		dev_err(chip->dev, "Failed to request IRQ %d: %d\n",
			i2c->irq, ret);
		return ret;
	}

	irq_base = regmap_irq_chip_get_base(chip->regmap_irq);

	ret = mfd_add_devices(chip->dev, PLATFORM_DEVID_NONE, cell,
			      cell_num, NULL, irq_base,
			      NULL);
	if (ret) {
		dev_err(chip->dev, "Cannot register child devices\n");
		regmap_del_irq_chip(i2c->irq, chip->regmap_irq);
		return ret;
	}

	return ret;
}