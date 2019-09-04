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
struct tc654_data {int config; int /*<<< orphan*/  update_lock; struct i2c_client* client; } ;
struct i2c_device_id {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  name; int /*<<< orphan*/  adapter; struct device dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int PTR_ERR_OR_ZERO (struct device*) ; 
 int /*<<< orphan*/  TC654_REG_CONFIG ; 
 struct device* devm_hwmon_device_register_with_groups (struct device*,int /*<<< orphan*/ ,struct tc654_data*,int /*<<< orphan*/ ) ; 
 struct tc654_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tc654_groups ; 

__attribute__((used)) static int tc654_probe(struct i2c_client *client,
		       const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct tc654_data *data;
	struct device *hwmon_dev;
	int ret;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -ENODEV;

	data = devm_kzalloc(dev, sizeof(struct tc654_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->client = client;
	mutex_init(&data->update_lock);

	ret = i2c_smbus_read_byte_data(client, TC654_REG_CONFIG);
	if (ret < 0)
		return ret;

	data->config = ret;

	hwmon_dev =
	    devm_hwmon_device_register_with_groups(dev, client->name, data,
						   tc654_groups);
	return PTR_ERR_OR_ZERO(hwmon_dev);
}