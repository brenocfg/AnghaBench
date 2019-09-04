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
struct ina3221_data {struct device** fields; int /*<<< orphan*/ * shunt_resistors; struct device* regmap; } ;
struct i2c_device_id {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  name; struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int F_MAX_FIELDS ; 
 size_t F_RST ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int INA3221_NUM_CHANNELS ; 
 int /*<<< orphan*/  INA3221_RSHUNT_DEFAULT ; 
 scalar_t__ IS_ERR (struct device*) ; 
 int PTR_ERR (struct device*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct device* devm_hwmon_device_register_with_groups (struct device*,int /*<<< orphan*/ ,struct ina3221_data*,int /*<<< orphan*/ ) ; 
 struct ina3221_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct device* devm_regmap_field_alloc (struct device*,struct device*,int /*<<< orphan*/ ) ; 
 struct device* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ina3221_groups ; 
 int /*<<< orphan*/ * ina3221_reg_fields ; 
 int /*<<< orphan*/  ina3221_regmap_config ; 
 int regmap_field_write (struct device*,int) ; 

__attribute__((used)) static int ina3221_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct ina3221_data *ina;
	struct device *hwmon_dev;
	int i, ret;

	ina = devm_kzalloc(dev, sizeof(*ina), GFP_KERNEL);
	if (!ina)
		return -ENOMEM;

	ina->regmap = devm_regmap_init_i2c(client, &ina3221_regmap_config);
	if (IS_ERR(ina->regmap)) {
		dev_err(dev, "Unable to allocate register map\n");
		return PTR_ERR(ina->regmap);
	}

	for (i = 0; i < F_MAX_FIELDS; i++) {
		ina->fields[i] = devm_regmap_field_alloc(dev,
							 ina->regmap,
							 ina3221_reg_fields[i]);
		if (IS_ERR(ina->fields[i])) {
			dev_err(dev, "Unable to allocate regmap fields\n");
			return PTR_ERR(ina->fields[i]);
		}
	}

	for (i = 0; i < INA3221_NUM_CHANNELS; i++)
		ina->shunt_resistors[i] = INA3221_RSHUNT_DEFAULT;

	ret = regmap_field_write(ina->fields[F_RST], true);
	if (ret) {
		dev_err(dev, "Unable to reset device\n");
		return ret;
	}

	hwmon_dev = devm_hwmon_device_register_with_groups(dev,
							   client->name,
							   ina, ina3221_groups);
	if (IS_ERR(hwmon_dev)) {
		dev_err(dev, "Unable to register hwmon device\n");
		return PTR_ERR(hwmon_dev);
	}

	return 0;
}