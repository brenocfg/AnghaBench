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
struct i2c_device_id {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  name; struct device dev; int /*<<< orphan*/  adapter; } ;
struct ad7414_data {int /*<<< orphan*/  lock; struct i2c_client* client; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD7414_REG_CONF ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int I2C_FUNC_SMBUS_BYTE_DATA ; 
 int I2C_FUNC_SMBUS_READ_WORD_DATA ; 
 int PTR_ERR_OR_ZERO (struct device*) ; 
 int /*<<< orphan*/  ad7414_groups ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 struct device* devm_hwmon_device_register_with_groups (struct device*,int /*<<< orphan*/ ,struct ad7414_data*,int /*<<< orphan*/ ) ; 
 struct ad7414_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ad7414_probe(struct i2c_client *client,
			const struct i2c_device_id *dev_id)
{
	struct device *dev = &client->dev;
	struct ad7414_data *data;
	struct device *hwmon_dev;
	int conf;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA |
				     I2C_FUNC_SMBUS_READ_WORD_DATA))
		return -EOPNOTSUPP;

	data = devm_kzalloc(dev, sizeof(struct ad7414_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->client = client;
	mutex_init(&data->lock);

	dev_info(&client->dev, "chip found\n");

	/* Make sure the chip is powered up. */
	conf = i2c_smbus_read_byte_data(client, AD7414_REG_CONF);
	if (conf < 0)
		dev_warn(dev, "ad7414_probe unable to read config register.\n");
	else {
		conf &= ~(1 << 7);
		i2c_smbus_write_byte_data(client, AD7414_REG_CONF, conf);
	}

	hwmon_dev = devm_hwmon_device_register_with_groups(dev,
							   client->name,
							   data, ad7414_groups);
	return PTR_ERR_OR_ZERO(hwmon_dev);
}