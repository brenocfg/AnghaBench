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
struct i2c_client {int /*<<< orphan*/  name; struct device dev; } ;
struct adm9240_data {int /*<<< orphan*/  update_lock; struct i2c_client* client; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PTR_ERR_OR_ZERO (struct device*) ; 
 int /*<<< orphan*/  adm9240_groups ; 
 int /*<<< orphan*/  adm9240_init_client (struct i2c_client*) ; 
 struct device* devm_hwmon_device_register_with_groups (struct device*,int /*<<< orphan*/ ,struct adm9240_data*,int /*<<< orphan*/ ) ; 
 struct adm9240_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct adm9240_data*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adm9240_probe(struct i2c_client *new_client,
			 const struct i2c_device_id *id)
{
	struct device *dev = &new_client->dev;
	struct device *hwmon_dev;
	struct adm9240_data *data;

	data = devm_kzalloc(dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	i2c_set_clientdata(new_client, data);
	data->client = new_client;
	mutex_init(&data->update_lock);

	adm9240_init_client(new_client);

	hwmon_dev = devm_hwmon_device_register_with_groups(dev,
							   new_client->name,
							   data,
							   adm9240_groups);
	return PTR_ERR_OR_ZERO(hwmon_dev);
}