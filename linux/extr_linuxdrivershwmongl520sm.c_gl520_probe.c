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
struct gl520_data {int /*<<< orphan*/ ** groups; scalar_t__ two_temps; struct i2c_client* client; int /*<<< orphan*/  update_lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PTR_ERR_OR_ZERO (struct device*) ; 
 struct device* devm_hwmon_device_register_with_groups (struct device*,int /*<<< orphan*/ ,struct gl520_data*,int /*<<< orphan*/ **) ; 
 struct gl520_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl520_group ; 
 int /*<<< orphan*/  gl520_group_in4 ; 
 int /*<<< orphan*/  gl520_group_temp2 ; 
 int /*<<< orphan*/  gl520_init_client (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct gl520_data*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gl520_probe(struct i2c_client *client,
		       const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct device *hwmon_dev;
	struct gl520_data *data;

	data = devm_kzalloc(dev, sizeof(struct gl520_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	i2c_set_clientdata(client, data);
	mutex_init(&data->update_lock);
	data->client = client;

	/* Initialize the GL520SM chip */
	gl520_init_client(client);

	/* sysfs hooks */
	data->groups[0] = &gl520_group;

	if (data->two_temps)
		data->groups[1] = &gl520_group_temp2;
	else
		data->groups[1] = &gl520_group_in4;

	hwmon_dev = devm_hwmon_device_register_with_groups(dev, client->name,
							   data, data->groups);
	return PTR_ERR_OR_ZERO(hwmon_dev);
}