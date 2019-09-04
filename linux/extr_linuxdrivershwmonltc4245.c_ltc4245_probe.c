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
struct ltc4245_data {int /*<<< orphan*/  use_extra_gpios; int /*<<< orphan*/  update_lock; struct i2c_client* client; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  name; int /*<<< orphan*/  dev; struct i2c_adapter* adapter; } ;
struct i2c_adapter {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  LTC4245_FAULT1 ; 
 int /*<<< orphan*/  LTC4245_FAULT2 ; 
 int PTR_ERR_OR_ZERO (struct device*) ; 
 struct device* devm_hwmon_device_register_with_info (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ltc4245_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ltc4245_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ltc4245_chip_info ; 
 int /*<<< orphan*/  ltc4245_use_extra_gpios (struct i2c_client*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ltc4245_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct i2c_adapter *adapter = client->adapter;
	struct ltc4245_data *data;
	struct device *hwmon_dev;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -ENODEV;

	data = devm_kzalloc(&client->dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->client = client;
	mutex_init(&data->update_lock);
	data->use_extra_gpios = ltc4245_use_extra_gpios(client);

	/* Initialize the LTC4245 chip */
	i2c_smbus_write_byte_data(client, LTC4245_FAULT1, 0x00);
	i2c_smbus_write_byte_data(client, LTC4245_FAULT2, 0x00);

	hwmon_dev = devm_hwmon_device_register_with_info(&client->dev,
							 client->name, data,
							 &ltc4245_chip_info,
							 NULL);
	return PTR_ERR_OR_ZERO(hwmon_dev);
}