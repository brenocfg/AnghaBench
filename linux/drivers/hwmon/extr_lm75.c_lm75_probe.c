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
struct lm75_data {int kind; int orig_conf; int current_conf; TYPE_1__* params; int /*<<< orphan*/  resolution; int /*<<< orphan*/  sample_time; struct device* regmap; struct i2c_client* client; } ;
struct i2c_device_id {int driver_data; } ;
struct device {scalar_t__ of_node; } ;
struct i2c_client {int /*<<< orphan*/  name; int /*<<< orphan*/  adapter; struct device dev; } ;
typedef  enum lm75_type { ____Placeholder_lm75_type } lm75_type ;
struct TYPE_2__ {int /*<<< orphan*/  clr_mask; int /*<<< orphan*/  set_mask; int /*<<< orphan*/  default_resolution; int /*<<< orphan*/  default_sample_time; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int I2C_FUNC_SMBUS_BYTE_DATA ; 
 int I2C_FUNC_SMBUS_WORD_DATA ; 
 scalar_t__ IS_ERR (struct device*) ; 
 int /*<<< orphan*/  LM75_REG_CONF ; 
 int PTR_ERR (struct device*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 TYPE_1__* device_params ; 
 int devm_add_action_or_reset (struct device*,int /*<<< orphan*/ ,struct lm75_data*) ; 
 struct device* devm_hwmon_device_register_with_info (struct device*,int /*<<< orphan*/ ,struct lm75_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct lm75_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct device* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lm75_chip_info ; 
 int /*<<< orphan*/  lm75_regmap_config ; 
 int /*<<< orphan*/  lm75_remove ; 
 int lm75_write_config (struct lm75_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ of_device_get_match_data (struct device*) ; 

__attribute__((used)) static int
lm75_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct device *hwmon_dev;
	struct lm75_data *data;
	int status, err;
	enum lm75_type kind;

	if (client->dev.of_node)
		kind = (enum lm75_type)of_device_get_match_data(&client->dev);
	else
		kind = id->driver_data;

	if (!i2c_check_functionality(client->adapter,
			I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WORD_DATA))
		return -EIO;

	data = devm_kzalloc(dev, sizeof(struct lm75_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->client = client;
	data->kind = kind;

	data->regmap = devm_regmap_init_i2c(client, &lm75_regmap_config);
	if (IS_ERR(data->regmap))
		return PTR_ERR(data->regmap);

	/* Set to LM75 resolution (9 bits, 1/2 degree C) and range.
	 * Then tweak to be more precise when appropriate.
	 */

	data->params = &device_params[data->kind];

	/* Save default sample time and resolution*/
	data->sample_time = data->params->default_sample_time;
	data->resolution = data->params->default_resolution;

	/* Cache original configuration */
	status = i2c_smbus_read_byte_data(client, LM75_REG_CONF);
	if (status < 0) {
		dev_dbg(dev, "Can't read config? %d\n", status);
		return status;
	}
	data->orig_conf = status;
	data->current_conf = status;

	err = lm75_write_config(data, data->params->set_mask,
				data->params->clr_mask);
	if (err)
		return err;

	err = devm_add_action_or_reset(dev, lm75_remove, data);
	if (err)
		return err;

	hwmon_dev = devm_hwmon_device_register_with_info(dev, client->name,
							 data, &lm75_chip_info,
							 NULL);
	if (IS_ERR(hwmon_dev))
		return PTR_ERR(hwmon_dev);

	dev_info(dev, "%s: sensor '%s'\n", dev_name(hwmon_dev), client->name);

	return 0;
}