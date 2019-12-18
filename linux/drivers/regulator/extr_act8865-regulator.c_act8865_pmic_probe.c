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
struct regulator_dev {int dummy; } ;
struct regulator_desc {int /*<<< orphan*/  name; int /*<<< orphan*/  id; } ;
struct regulator_config {int /*<<< orphan*/  of_node; int /*<<< orphan*/  init_data; struct regulator_dev* regmap; struct act8865* driver_data; struct device* dev; } ;
struct regmap_config {int dummy; } ;
struct of_device_id {scalar_t__ data; } ;
struct i2c_device_id {unsigned long driver_data; } ;
struct device {scalar_t__ of_node; } ;
struct i2c_client {struct device dev; } ;
struct act8865_regulator_data {int /*<<< orphan*/  of_node; int /*<<< orphan*/  init_data; } ;
struct act8865_platform_data {int dummy; } ;
struct act8865 {int off_reg; int off_mask; struct regulator_dev* regmap; } ;

/* Variables and functions */
#define  ACT8600 130 
#define  ACT8846 129 
 int ACT8846_GLB_OFF_CTRL ; 
 int ACT8846_OFF_SYSMASK ; 
#define  ACT8865 128 
 int ACT8865_MSTROFF ; 
 int ACT8865_SYS_CTRL ; 
 int /*<<< orphan*/  ACT8865_SYS_UNLK_REGS ; 
 int ARRAY_SIZE (struct regulator_desc*) ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 int PTR_ERR (struct regulator_dev*) ; 
 int act8600_charger_probe (struct device*,struct regulator_dev*) ; 
 struct regmap_config act8600_regmap_config ; 
 struct regulator_desc* act8600_regulators ; 
 struct regulator_desc* act8846_regulators ; 
 struct regulator_desc* act8865_alt_regulators ; 
 int /*<<< orphan*/  act8865_dt_ids ; 
 struct act8865_regulator_data* act8865_get_regulator_data (int /*<<< orphan*/ ,struct act8865_platform_data*) ; 
 struct i2c_client* act8865_i2c_client ; 
 scalar_t__ act8865_power_off ; 
 struct regmap_config act8865_regmap_config ; 
 struct regulator_desc* act8865_regulators ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct act8865_platform_data* dev_get_platdata (struct device*) ; 
 struct act8865* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct regulator_dev* devm_regmap_init_i2c (struct i2c_client*,struct regmap_config const*) ; 
 struct regulator_dev* devm_regulator_register (struct device*,struct regulator_desc const*,struct regulator_config*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct act8865*) ; 
 scalar_t__ of_device_is_system_power_controller (scalar_t__) ; 
 int /*<<< orphan*/  of_get_property (scalar_t__,char*,int /*<<< orphan*/ *) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  of_match_ptr (int /*<<< orphan*/ ) ; 
 scalar_t__ pm_power_off ; 
 int regmap_write (struct regulator_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int act8865_pmic_probe(struct i2c_client *client,
			      const struct i2c_device_id *i2c_id)
{
	const struct regulator_desc *regulators;
	struct act8865_platform_data *pdata = NULL;
	struct device *dev = &client->dev;
	int i, ret, num_regulators;
	struct act8865 *act8865;
	const struct regmap_config *regmap_config;
	unsigned long type;
	int off_reg, off_mask;
	int voltage_select = 0;

	if (dev->of_node) {
		const struct of_device_id *id;

		id = of_match_device(of_match_ptr(act8865_dt_ids), dev);
		if (!id)
			return -ENODEV;

		type = (unsigned long) id->data;

		voltage_select = !!of_get_property(dev->of_node,
						   "active-semi,vsel-high",
						   NULL);
	} else {
		type = i2c_id->driver_data;
		pdata = dev_get_platdata(dev);
	}

	switch (type) {
	case ACT8600:
		regulators = act8600_regulators;
		num_regulators = ARRAY_SIZE(act8600_regulators);
		regmap_config = &act8600_regmap_config;
		off_reg = -1;
		off_mask = -1;
		break;
	case ACT8846:
		regulators = act8846_regulators;
		num_regulators = ARRAY_SIZE(act8846_regulators);
		regmap_config = &act8865_regmap_config;
		off_reg = ACT8846_GLB_OFF_CTRL;
		off_mask = ACT8846_OFF_SYSMASK;
		break;
	case ACT8865:
		if (voltage_select) {
			regulators = act8865_alt_regulators;
			num_regulators = ARRAY_SIZE(act8865_alt_regulators);
		} else {
			regulators = act8865_regulators;
			num_regulators = ARRAY_SIZE(act8865_regulators);
		}
		regmap_config = &act8865_regmap_config;
		off_reg = ACT8865_SYS_CTRL;
		off_mask = ACT8865_MSTROFF;
		break;
	default:
		dev_err(dev, "invalid device id %lu\n", type);
		return -EINVAL;
	}

	act8865 = devm_kzalloc(dev, sizeof(struct act8865), GFP_KERNEL);
	if (!act8865)
		return -ENOMEM;

	act8865->regmap = devm_regmap_init_i2c(client, regmap_config);
	if (IS_ERR(act8865->regmap)) {
		ret = PTR_ERR(act8865->regmap);
		dev_err(dev, "Failed to allocate register map: %d\n", ret);
		return ret;
	}

	if (of_device_is_system_power_controller(dev->of_node)) {
		if (!pm_power_off && (off_reg > 0)) {
			act8865_i2c_client = client;
			act8865->off_reg = off_reg;
			act8865->off_mask = off_mask;
			pm_power_off = act8865_power_off;
		} else {
			dev_err(dev, "Failed to set poweroff capability, already defined\n");
		}
	}

	/* Finally register devices */
	for (i = 0; i < num_regulators; i++) {
		const struct regulator_desc *desc = &regulators[i];
		struct regulator_config config = { };
		struct regulator_dev *rdev;

		config.dev = dev;
		config.driver_data = act8865;
		config.regmap = act8865->regmap;

		if (pdata) {
			struct act8865_regulator_data *rdata;

			rdata = act8865_get_regulator_data(desc->id, pdata);
			if (rdata) {
				config.init_data = rdata->init_data;
				config.of_node = rdata->of_node;
			}
		}

		rdev = devm_regulator_register(dev, desc, &config);
		if (IS_ERR(rdev)) {
			dev_err(dev, "failed to register %s\n", desc->name);
			return PTR_ERR(rdev);
		}
	}

	if (type == ACT8600) {
		ret = act8600_charger_probe(dev, act8865->regmap);
		if (ret < 0) {
			if (ret != -EPROBE_DEFER)
				dev_err(dev, "Failed to probe charger");
			return ret;
		}
	}

	i2c_set_clientdata(client, act8865);

	/* Unlock expert registers for ACT8865. */
	return type != ACT8865 ? 0 : regmap_write(act8865->regmap,
						  ACT8865_SYS_UNLK_REGS, 0xef);
}