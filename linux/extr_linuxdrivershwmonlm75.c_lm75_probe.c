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
typedef  int u8 ;
struct lm75_data {int resolution; int sample_time; int resolution_limits; int orig_conf; struct device* regmap; struct i2c_client* client; } ;
struct i2c_device_id {int driver_data; } ;
struct device {scalar_t__ of_node; } ;
struct i2c_client {int /*<<< orphan*/  name; int /*<<< orphan*/  adapter; struct device dev; } ;
typedef  enum lm75_type { ____Placeholder_lm75_type } lm75_type ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int I2C_FUNC_SMBUS_BYTE_DATA ; 
 int I2C_FUNC_SMBUS_WORD_DATA ; 
 scalar_t__ IS_ERR (struct device*) ; 
 int /*<<< orphan*/  LM75_REG_CONF ; 
 int LM75_SHUTDOWN ; 
 int MSEC_PER_SEC ; 
 int PTR_ERR (struct device*) ; 
#define  adt75 148 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int devm_add_action_or_reset (struct device*,int /*<<< orphan*/ ,struct lm75_data*) ; 
 struct device* devm_hwmon_device_register_with_info (struct device*,int /*<<< orphan*/ ,struct lm75_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct lm75_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct device* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
#define  ds1775 147 
#define  ds75 146 
#define  ds7505 145 
#define  g751 144 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
#define  lm75 143 
 int /*<<< orphan*/  lm75_chip_info ; 
 int /*<<< orphan*/  lm75_regmap_config ; 
 int /*<<< orphan*/  lm75_remove ; 
#define  lm75a 142 
#define  lm75b 141 
#define  max6625 140 
#define  max6626 139 
#define  mcp980x 138 
 scalar_t__ of_device_get_match_data (struct device*) ; 
#define  stds75 137 
#define  tcn75 136 
#define  tmp100 135 
#define  tmp101 134 
#define  tmp105 133 
#define  tmp112 132 
#define  tmp175 131 
#define  tmp275 130 
#define  tmp75 129 
#define  tmp75c 128 

__attribute__((used)) static int
lm75_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct device *hwmon_dev;
	struct lm75_data *data;
	int status, err;
	u8 set_mask, clr_mask;
	int new;
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

	data->regmap = devm_regmap_init_i2c(client, &lm75_regmap_config);
	if (IS_ERR(data->regmap))
		return PTR_ERR(data->regmap);

	/* Set to LM75 resolution (9 bits, 1/2 degree C) and range.
	 * Then tweak to be more precise when appropriate.
	 */
	set_mask = 0;
	clr_mask = LM75_SHUTDOWN;		/* continuous conversions */

	switch (kind) {
	case adt75:
		clr_mask |= 1 << 5;		/* not one-shot mode */
		data->resolution = 12;
		data->sample_time = MSEC_PER_SEC / 8;
		break;
	case ds1775:
	case ds75:
	case stds75:
		clr_mask |= 3 << 5;
		set_mask |= 2 << 5;		/* 11-bit mode */
		data->resolution = 11;
		data->sample_time = MSEC_PER_SEC;
		break;
	case ds7505:
		set_mask |= 3 << 5;		/* 12-bit mode */
		data->resolution = 12;
		data->sample_time = MSEC_PER_SEC / 4;
		break;
	case g751:
	case lm75:
	case lm75a:
		data->resolution = 9;
		data->sample_time = MSEC_PER_SEC / 2;
		break;
	case lm75b:
		data->resolution = 11;
		data->sample_time = MSEC_PER_SEC / 4;
		break;
	case max6625:
		data->resolution = 9;
		data->sample_time = MSEC_PER_SEC / 4;
		break;
	case max6626:
		data->resolution = 12;
		data->resolution_limits = 9;
		data->sample_time = MSEC_PER_SEC / 4;
		break;
	case tcn75:
		data->resolution = 9;
		data->sample_time = MSEC_PER_SEC / 8;
		break;
	case mcp980x:
		data->resolution_limits = 9;
		/* fall through */
	case tmp100:
	case tmp101:
		set_mask |= 3 << 5;		/* 12-bit mode */
		data->resolution = 12;
		data->sample_time = MSEC_PER_SEC;
		clr_mask |= 1 << 7;		/* not one-shot mode */
		break;
	case tmp112:
		set_mask |= 3 << 5;		/* 12-bit mode */
		clr_mask |= 1 << 7;		/* not one-shot mode */
		data->resolution = 12;
		data->sample_time = MSEC_PER_SEC / 4;
		break;
	case tmp105:
	case tmp175:
	case tmp275:
	case tmp75:
		set_mask |= 3 << 5;		/* 12-bit mode */
		clr_mask |= 1 << 7;		/* not one-shot mode */
		data->resolution = 12;
		data->sample_time = MSEC_PER_SEC / 2;
		break;
	case tmp75c:
		clr_mask |= 1 << 5;		/* not one-shot mode */
		data->resolution = 12;
		data->sample_time = MSEC_PER_SEC / 4;
		break;
	}

	/* configure as specified */
	status = i2c_smbus_read_byte_data(client, LM75_REG_CONF);
	if (status < 0) {
		dev_dbg(dev, "Can't read config? %d\n", status);
		return status;
	}
	data->orig_conf = status;
	new = status & ~clr_mask;
	new |= set_mask;
	if (status != new)
		i2c_smbus_write_byte_data(client, LM75_REG_CONF, new);

	err = devm_add_action_or_reset(dev, lm75_remove, data);
	if (err)
		return err;

	dev_dbg(dev, "Config %02x\n", new);

	hwmon_dev = devm_hwmon_device_register_with_info(dev, client->name,
							 data, &lm75_chip_info,
							 NULL);
	if (IS_ERR(hwmon_dev))
		return PTR_ERR(hwmon_dev);

	dev_info(dev, "%s: sensor '%s'\n", dev_name(hwmon_dev), client->name);

	return 0;
}