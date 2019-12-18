#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct regmap_config {int dummy; } ;
struct mfd_cell {int dummy; } ;
struct max77620_chip {int irq_base; int chip_id; TYPE_2__* dev; int /*<<< orphan*/  top_irq_data; int /*<<< orphan*/  rmap; int /*<<< orphan*/  chip_irq; } ;
struct i2c_device_id {scalar_t__ driver_data; } ;
struct TYPE_8__ {int /*<<< orphan*/  of_node; } ;
struct i2c_client {TYPE_2__ dev; int /*<<< orphan*/  irq; } ;
typedef  enum max77620_chip_id { ____Placeholder_max77620_chip_id } max77620_chip_id ;
struct TYPE_7__ {struct max77620_chip* irq_drv_data; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct mfd_cell*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IRQF_ONESHOT ; 
 int IRQF_SHARED ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
#define  MAX20024 130 
#define  MAX77620 129 
#define  MAX77663 128 
 int /*<<< orphan*/  PLATFORM_DEVID_NONE ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int) ; 
 struct max77620_chip* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int devm_mfd_add_devices (TYPE_2__*,int /*<<< orphan*/ ,struct mfd_cell const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devm_regmap_add_irq_chip (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,struct regmap_config const*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct max77620_chip*) ; 
 struct mfd_cell* max20024_children ; 
 struct regmap_config max20024_regmap_config ; 
 struct mfd_cell* max77620_children ; 
 int max77620_initialise_fps (struct max77620_chip*) ; 
 scalar_t__ max77620_pm_power_off ; 
 int max77620_read_es_version (struct max77620_chip*) ; 
 struct regmap_config max77620_regmap_config ; 
 struct max77620_chip* max77620_scratch ; 
 TYPE_1__ max77620_top_irq_chip ; 
 struct mfd_cell* max77663_children ; 
 struct regmap_config max77663_regmap_config ; 
 int of_device_is_system_power_controller (int /*<<< orphan*/ ) ; 
 scalar_t__ pm_power_off ; 
 int /*<<< orphan*/  regmap_irq_get_domain (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max77620_probe(struct i2c_client *client,
			  const struct i2c_device_id *id)
{
	const struct regmap_config *rmap_config;
	struct max77620_chip *chip;
	const struct mfd_cell *mfd_cells;
	int n_mfd_cells;
	bool pm_off;
	int ret;

	chip = devm_kzalloc(&client->dev, sizeof(*chip), GFP_KERNEL);
	if (!chip)
		return -ENOMEM;

	i2c_set_clientdata(client, chip);
	chip->dev = &client->dev;
	chip->irq_base = -1;
	chip->chip_irq = client->irq;
	chip->chip_id = (enum max77620_chip_id)id->driver_data;

	switch (chip->chip_id) {
	case MAX77620:
		mfd_cells = max77620_children;
		n_mfd_cells = ARRAY_SIZE(max77620_children);
		rmap_config = &max77620_regmap_config;
		break;
	case MAX20024:
		mfd_cells = max20024_children;
		n_mfd_cells = ARRAY_SIZE(max20024_children);
		rmap_config = &max20024_regmap_config;
		break;
	case MAX77663:
		mfd_cells = max77663_children;
		n_mfd_cells = ARRAY_SIZE(max77663_children);
		rmap_config = &max77663_regmap_config;
		break;
	default:
		dev_err(chip->dev, "ChipID is invalid %d\n", chip->chip_id);
		return -EINVAL;
	}

	chip->rmap = devm_regmap_init_i2c(client, rmap_config);
	if (IS_ERR(chip->rmap)) {
		ret = PTR_ERR(chip->rmap);
		dev_err(chip->dev, "Failed to initialise regmap: %d\n", ret);
		return ret;
	}

	ret = max77620_read_es_version(chip);
	if (ret < 0)
		return ret;

	max77620_top_irq_chip.irq_drv_data = chip;
	ret = devm_regmap_add_irq_chip(chip->dev, chip->rmap, client->irq,
				       IRQF_ONESHOT | IRQF_SHARED,
				       chip->irq_base, &max77620_top_irq_chip,
				       &chip->top_irq_data);
	if (ret < 0) {
		dev_err(chip->dev, "Failed to add regmap irq: %d\n", ret);
		return ret;
	}

	ret = max77620_initialise_fps(chip);
	if (ret < 0)
		return ret;

	ret =  devm_mfd_add_devices(chip->dev, PLATFORM_DEVID_NONE,
				    mfd_cells, n_mfd_cells, NULL, 0,
				    regmap_irq_get_domain(chip->top_irq_data));
	if (ret < 0) {
		dev_err(chip->dev, "Failed to add MFD children: %d\n", ret);
		return ret;
	}

	pm_off = of_device_is_system_power_controller(client->dev.of_node);
	if (pm_off && !pm_power_off) {
		max77620_scratch = chip;
		pm_power_off = max77620_pm_power_off;
	}

	return 0;
}