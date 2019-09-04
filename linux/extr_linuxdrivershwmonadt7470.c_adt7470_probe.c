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
struct adt7470_data {int num_temp_sensors; struct device* auto_update; int /*<<< orphan*/  lock; struct i2c_client* client; int /*<<< orphan*/  auto_update_interval; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTO_UPDATE_INTERVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct device*) ; 
 int PTR_ERR (struct device*) ; 
 int /*<<< orphan*/  adt7470_groups ; 
 int /*<<< orphan*/  adt7470_init_client (struct i2c_client*) ; 
 int /*<<< orphan*/  adt7470_update_thread ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 struct device* devm_hwmon_device_register_with_groups (struct device*,int /*<<< orphan*/ ,struct adt7470_data*,int /*<<< orphan*/ ) ; 
 struct adt7470_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct adt7470_data*) ; 
 struct device* kthread_run (int /*<<< orphan*/ ,struct i2c_client*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adt7470_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct adt7470_data *data;
	struct device *hwmon_dev;

	data = devm_kzalloc(dev, sizeof(struct adt7470_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->num_temp_sensors = -1;
	data->auto_update_interval = AUTO_UPDATE_INTERVAL;

	i2c_set_clientdata(client, data);
	data->client = client;
	mutex_init(&data->lock);

	dev_info(&client->dev, "%s chip found\n", client->name);

	/* Initialize the ADT7470 chip */
	adt7470_init_client(client);

	/* Register sysfs hooks */
	hwmon_dev = devm_hwmon_device_register_with_groups(dev, client->name,
							   data,
							   adt7470_groups);

	if (IS_ERR(hwmon_dev))
		return PTR_ERR(hwmon_dev);

	data->auto_update = kthread_run(adt7470_update_thread, client, "%s",
					dev_name(hwmon_dev));
	if (IS_ERR(data->auto_update)) {
		return PTR_ERR(data->auto_update);
	}

	return 0;
}