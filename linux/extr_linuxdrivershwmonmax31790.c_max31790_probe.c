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
struct max31790_data {int /*<<< orphan*/  update_lock; struct i2c_client* client; } ;
struct i2c_device_id {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  name; struct device dev; struct i2c_adapter* adapter; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int I2C_FUNC_SMBUS_BYTE_DATA ; 
 int I2C_FUNC_SMBUS_WORD_DATA ; 
 int PTR_ERR_OR_ZERO (struct device*) ; 
 struct device* devm_hwmon_device_register_with_info (struct device*,int /*<<< orphan*/ ,struct max31790_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct max31790_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int) ; 
 int /*<<< orphan*/  max31790_chip_info ; 
 int max31790_init_client (struct i2c_client*,struct max31790_data*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int max31790_probe(struct i2c_client *client,
			  const struct i2c_device_id *id)
{
	struct i2c_adapter *adapter = client->adapter;
	struct device *dev = &client->dev;
	struct max31790_data *data;
	struct device *hwmon_dev;
	int err;

	if (!i2c_check_functionality(adapter,
			I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WORD_DATA))
		return -ENODEV;

	data = devm_kzalloc(dev, sizeof(struct max31790_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->client = client;
	mutex_init(&data->update_lock);

	/*
	 * Initialize the max31790 chip
	 */
	err = max31790_init_client(client, data);
	if (err)
		return err;

	hwmon_dev = devm_hwmon_device_register_with_info(dev, client->name,
							 data,
							 &max31790_chip_info,
							 NULL);

	return PTR_ERR_OR_ZERO(hwmon_dev);
}