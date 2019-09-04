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
struct tmp102 {unsigned int config_orig; scalar_t__ ready_time; struct device* regmap; } ;
struct i2c_device_id {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  name; int /*<<< orphan*/  adapter; struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONVERSION_TIME_MS ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_WORD_DATA ; 
 scalar_t__ IS_ERR (struct device*) ; 
 int PTR_ERR (struct device*) ; 
 unsigned int TMP102_CONFIG_CLEAR ; 
 unsigned int TMP102_CONFIG_SET ; 
 unsigned int TMP102_CONFREG_MASK ; 
 unsigned int TMP102_CONF_R0 ; 
 unsigned int TMP102_CONF_R1 ; 
 int /*<<< orphan*/  TMP102_CONF_REG ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int devm_add_action_or_reset (struct device*,int /*<<< orphan*/ ,struct tmp102*) ; 
 struct device* devm_hwmon_device_register_with_info (struct device*,int /*<<< orphan*/ ,struct tmp102*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct tmp102* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct device* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct tmp102*) ; 
 scalar_t__ jiffies ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int regmap_read (struct device*,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_write (struct device*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  tmp102_chip_info ; 
 int /*<<< orphan*/  tmp102_regmap_config ; 
 int /*<<< orphan*/  tmp102_restore_config ; 

__attribute__((used)) static int tmp102_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct device *hwmon_dev;
	struct tmp102 *tmp102;
	unsigned int regval;
	int err;

	if (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_WORD_DATA)) {
		dev_err(dev,
			"adapter doesn't support SMBus word transactions\n");
		return -ENODEV;
	}

	tmp102 = devm_kzalloc(dev, sizeof(*tmp102), GFP_KERNEL);
	if (!tmp102)
		return -ENOMEM;

	i2c_set_clientdata(client, tmp102);

	tmp102->regmap = devm_regmap_init_i2c(client, &tmp102_regmap_config);
	if (IS_ERR(tmp102->regmap))
		return PTR_ERR(tmp102->regmap);

	err = regmap_read(tmp102->regmap, TMP102_CONF_REG, &regval);
	if (err < 0) {
		dev_err(dev, "error reading config register\n");
		return err;
	}

	if ((regval & ~TMP102_CONFREG_MASK) !=
	    (TMP102_CONF_R0 | TMP102_CONF_R1)) {
		dev_err(dev, "unexpected config register value\n");
		return -ENODEV;
	}

	tmp102->config_orig = regval;

	err = devm_add_action_or_reset(dev, tmp102_restore_config, tmp102);
	if (err)
		return err;

	regval &= ~TMP102_CONFIG_CLEAR;
	regval |= TMP102_CONFIG_SET;

	err = regmap_write(tmp102->regmap, TMP102_CONF_REG, regval);
	if (err < 0) {
		dev_err(dev, "error writing config register\n");
		return err;
	}

	/*
	 * Mark that we are not ready with data until the first
	 * conversion is complete
	 */
	tmp102->ready_time = jiffies + msecs_to_jiffies(CONVERSION_TIME_MS);

	hwmon_dev = devm_hwmon_device_register_with_info(dev, client->name,
							 tmp102,
							 &tmp102_chip_info,
							 NULL);
	if (IS_ERR(hwmon_dev)) {
		dev_dbg(dev, "unable to register hwmon device\n");
		return PTR_ERR(hwmon_dev);
	}
	dev_info(dev, "initialized\n");

	return 0;
}