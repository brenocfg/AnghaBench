#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct ina2xx_platform_data {int /*<<< orphan*/  shunt_uohms; } ;
struct ina2xx_data {int /*<<< orphan*/  rshunt; int /*<<< orphan*/ ** groups; struct device* regmap; TYPE_2__* config; int /*<<< orphan*/  config_lock; } ;
struct i2c_device_id {int driver_data; } ;
struct device {scalar_t__ of_node; } ;
struct i2c_client {int /*<<< orphan*/  name; struct device dev; } ;
typedef  enum ina2xx_ids { ____Placeholder_ina2xx_ids } ina2xx_ids ;
struct TYPE_5__ {int /*<<< orphan*/  registers; } ;
struct TYPE_4__ {int /*<<< orphan*/  max_register; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INA2XX_RSHUNT_DEFAULT ; 
 scalar_t__ IS_ERR (struct device*) ; 
 int PTR_ERR (struct device*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct ina2xx_platform_data* dev_get_platdata (struct device*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct device* devm_hwmon_device_register_with_groups (struct device*,int /*<<< orphan*/ ,struct ina2xx_data*,int /*<<< orphan*/ **) ; 
 struct ina2xx_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct device* devm_regmap_init_i2c (struct i2c_client*,TYPE_1__*) ; 
 int ina226 ; 
 int /*<<< orphan*/  ina226_group ; 
 TYPE_2__* ina2xx_config ; 
 int /*<<< orphan*/  ina2xx_group ; 
 int ina2xx_init (struct ina2xx_data*) ; 
 TYPE_1__ ina2xx_regmap_config ; 
 int /*<<< orphan*/  ina2xx_set_shunt (struct ina2xx_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ of_device_get_match_data (struct device*) ; 
 scalar_t__ of_property_read_u32 (scalar_t__,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ina2xx_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct ina2xx_data *data;
	struct device *hwmon_dev;
	u32 val;
	int ret, group = 0;
	enum ina2xx_ids chip;

	if (client->dev.of_node)
		chip = (enum ina2xx_ids)of_device_get_match_data(&client->dev);
	else
		chip = id->driver_data;

	data = devm_kzalloc(dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	/* set the device type */
	data->config = &ina2xx_config[chip];
	mutex_init(&data->config_lock);

	if (of_property_read_u32(dev->of_node, "shunt-resistor", &val) < 0) {
		struct ina2xx_platform_data *pdata = dev_get_platdata(dev);

		if (pdata)
			val = pdata->shunt_uohms;
		else
			val = INA2XX_RSHUNT_DEFAULT;
	}

	ina2xx_set_shunt(data, val);

	ina2xx_regmap_config.max_register = data->config->registers;

	data->regmap = devm_regmap_init_i2c(client, &ina2xx_regmap_config);
	if (IS_ERR(data->regmap)) {
		dev_err(dev, "failed to allocate register map\n");
		return PTR_ERR(data->regmap);
	}

	ret = ina2xx_init(data);
	if (ret < 0) {
		dev_err(dev, "error configuring the device: %d\n", ret);
		return -ENODEV;
	}

	data->groups[group++] = &ina2xx_group;
	if (chip == ina226)
		data->groups[group++] = &ina226_group;

	hwmon_dev = devm_hwmon_device_register_with_groups(dev, client->name,
							   data, data->groups);
	if (IS_ERR(hwmon_dev))
		return PTR_ERR(hwmon_dev);

	dev_info(dev, "power monitor %s (Rshunt = %li uOhm)\n",
		 client->name, data->rshunt);

	return 0;
}