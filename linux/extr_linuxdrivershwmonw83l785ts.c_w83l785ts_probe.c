#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct w83l785ts_data {int /*<<< orphan*/  hwmon_dev; int /*<<< orphan*/  update_lock; } ;
struct i2c_device_id {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {struct device dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev_attr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int device_create_file (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (struct device*,int /*<<< orphan*/ *) ; 
 struct w83l785ts_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwmon_device_register (struct device*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct w83l785ts_data*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 TYPE_2__ sensor_dev_attr_temp1_input ; 
 TYPE_1__ sensor_dev_attr_temp1_max ; 

__attribute__((used)) static int w83l785ts_probe(struct i2c_client *client,
			   const struct i2c_device_id *id)
{
	struct w83l785ts_data *data;
	struct device *dev = &client->dev;
	int err;

	data = devm_kzalloc(dev, sizeof(struct w83l785ts_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	i2c_set_clientdata(client, data);
	mutex_init(&data->update_lock);

	/*
	 * Initialize the W83L785TS chip
	 * Nothing yet, assume it is already started.
	 */

	err = device_create_file(dev, &sensor_dev_attr_temp1_input.dev_attr);
	if (err)
		return err;

	err = device_create_file(dev, &sensor_dev_attr_temp1_max.dev_attr);
	if (err)
		goto exit_remove;

	/* Register sysfs hooks */
	data->hwmon_dev = hwmon_device_register(dev);
	if (IS_ERR(data->hwmon_dev)) {
		err = PTR_ERR(data->hwmon_dev);
		goto exit_remove;
	}

	return 0;

exit_remove:
	device_remove_file(dev, &sensor_dev_attr_temp1_input.dev_attr);
	device_remove_file(dev, &sensor_dev_attr_temp1_max.dev_attr);
	return err;
}