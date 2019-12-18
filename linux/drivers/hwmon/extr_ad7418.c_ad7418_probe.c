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
struct i2c_device_id {int driver_data; } ;
struct device {scalar_t__ of_node; } ;
struct i2c_client {int /*<<< orphan*/  name; struct i2c_adapter* adapter; struct device dev; } ;
struct i2c_adapter {int dummy; } ;
struct attribute_group {int dummy; } ;
struct ad7418_data {int type; int adc_max; struct i2c_client* client; int /*<<< orphan*/  lock; } ;
typedef  enum chips { ____Placeholder_chips } chips ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int I2C_FUNC_SMBUS_BYTE_DATA ; 
 int I2C_FUNC_SMBUS_WORD_DATA ; 
 int PTR_ERR_OR_ZERO (struct device*) ; 
#define  ad7416 130 
 struct attribute_group** ad7416_groups ; 
#define  ad7417 129 
 struct attribute_group** ad7417_groups ; 
#define  ad7418 128 
 struct attribute_group** ad7418_groups ; 
 int /*<<< orphan*/  ad7418_init_client (struct i2c_client*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct device* devm_hwmon_device_register_with_groups (struct device*,int /*<<< orphan*/ ,struct ad7418_data*,struct attribute_group const**) ; 
 struct ad7418_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct ad7418_data*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ of_device_get_match_data (struct device*) ; 

__attribute__((used)) static int ad7418_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct i2c_adapter *adapter = client->adapter;
	struct ad7418_data *data;
	struct device *hwmon_dev;
	const struct attribute_group **attr_groups = NULL;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA |
					I2C_FUNC_SMBUS_WORD_DATA))
		return -EOPNOTSUPP;

	data = devm_kzalloc(dev, sizeof(struct ad7418_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	i2c_set_clientdata(client, data);

	mutex_init(&data->lock);
	data->client = client;
	if (dev->of_node)
		data->type = (enum chips)of_device_get_match_data(dev);
	else
		data->type = id->driver_data;

	switch (data->type) {
	case ad7416:
		data->adc_max = 0;
		attr_groups = ad7416_groups;
		break;

	case ad7417:
		data->adc_max = 4;
		attr_groups = ad7417_groups;
		break;

	case ad7418:
		data->adc_max = 1;
		attr_groups = ad7418_groups;
		break;
	}

	dev_info(dev, "%s chip found\n", client->name);

	/* Initialize the AD7418 chip */
	ad7418_init_client(client);

	hwmon_dev = devm_hwmon_device_register_with_groups(dev,
							   client->name,
							   data, attr_groups);
	return PTR_ERR_OR_ZERO(hwmon_dev);
}