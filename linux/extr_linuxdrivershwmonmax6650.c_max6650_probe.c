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
struct of_device_id {scalar_t__ data; } ;
struct max6650_data {int nr_fans; int /*<<< orphan*/ ** groups; int /*<<< orphan*/  update_lock; struct i2c_client* client; } ;
struct i2c_device_id {int driver_data; } ;
struct device {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  name; struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PTR_ERR_OR_ZERO (struct device*) ; 
 struct device* devm_hwmon_device_register_with_groups (struct device*,int /*<<< orphan*/ ,struct max6650_data*,int /*<<< orphan*/ **) ; 
 struct max6650_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max6650_dt_match ; 
 int /*<<< orphan*/  max6650_group ; 
 int max6650_init_client (struct max6650_data*,struct i2c_client*) ; 
 int /*<<< orphan*/  max6651_group ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  of_match_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max6650_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	const struct of_device_id *of_id =
		of_match_device(of_match_ptr(max6650_dt_match), dev);
	struct max6650_data *data;
	struct device *hwmon_dev;
	int err;

	data = devm_kzalloc(dev, sizeof(struct max6650_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->client = client;
	mutex_init(&data->update_lock);
	data->nr_fans = of_id ? (int)(uintptr_t)of_id->data : id->driver_data;

	/*
	 * Initialize the max6650 chip
	 */
	err = max6650_init_client(data, client);
	if (err)
		return err;

	data->groups[0] = &max6650_group;
	/* 3 additional fan inputs for the MAX6651 */
	if (data->nr_fans == 4)
		data->groups[1] = &max6651_group;

	hwmon_dev = devm_hwmon_device_register_with_groups(dev,
							   client->name, data,
							   data->groups);
	return PTR_ERR_OR_ZERO(hwmon_dev);
}