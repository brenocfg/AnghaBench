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
struct i2c_client {int /*<<< orphan*/  name; int /*<<< orphan*/  adapter; struct device dev; } ;
struct g762_data {int /*<<< orphan*/  update_lock; struct i2c_client* client; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int PTR_ERR_OR_ZERO (struct device*) ; 
 struct device* devm_hwmon_device_register_with_groups (struct device*,int /*<<< orphan*/ ,struct g762_data*,int /*<<< orphan*/ ) ; 
 struct g762_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int g762_fan_init (struct device*) ; 
 int /*<<< orphan*/  g762_groups ; 
 int g762_of_clock_enable (struct i2c_client*) ; 
 int g762_of_prop_import (struct i2c_client*) ; 
 int g762_pdata_prop_import (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct g762_data*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int g762_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct device *hwmon_dev;
	struct g762_data *data;
	int ret;

	if (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_BYTE_DATA))
		return -ENODEV;

	data = devm_kzalloc(dev, sizeof(struct g762_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	i2c_set_clientdata(client, data);
	data->client = client;
	mutex_init(&data->update_lock);

	/* Enable fan failure detection and fan out of control protection */
	ret = g762_fan_init(dev);
	if (ret)
		return ret;

	/* Get configuration via DT ... */
	ret = g762_of_clock_enable(client);
	if (ret)
		return ret;
	ret = g762_of_prop_import(client);
	if (ret)
		return ret;
	/* ... or platform_data */
	ret = g762_pdata_prop_import(client);
	if (ret)
		return ret;

	hwmon_dev = devm_hwmon_device_register_with_groups(dev, client->name,
							    data, g762_groups);
	return PTR_ERR_OR_ZERO(hwmon_dev);
}