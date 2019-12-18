#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct i2c_device_id {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct i2c_client {TYPE_1__ dev; } ;
struct asb100_data {int /*<<< orphan*/ * lm75; int /*<<< orphan*/  hwmon_dev; void** fan_min; int /*<<< orphan*/  update_lock; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASB100_REG_FAN_MIN (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int asb100_detect_subclients (struct i2c_client*) ; 
 int /*<<< orphan*/  asb100_group ; 
 int /*<<< orphan*/  asb100_init_client (struct i2c_client*) ; 
 void* asb100_read_value (struct i2c_client*,int /*<<< orphan*/ ) ; 
 struct asb100_data* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwmon_device_register (TYPE_1__*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct asb100_data*) ; 
 int /*<<< orphan*/  i2c_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int asb100_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	int err;
	struct asb100_data *data;

	data = devm_kzalloc(&client->dev, sizeof(struct asb100_data),
			    GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	i2c_set_clientdata(client, data);
	mutex_init(&data->lock);
	mutex_init(&data->update_lock);

	/* Attach secondary lm75 clients */
	err = asb100_detect_subclients(client);
	if (err)
		return err;

	/* Initialize the chip */
	asb100_init_client(client);

	/* A few vars need to be filled upon startup */
	data->fan_min[0] = asb100_read_value(client, ASB100_REG_FAN_MIN(0));
	data->fan_min[1] = asb100_read_value(client, ASB100_REG_FAN_MIN(1));
	data->fan_min[2] = asb100_read_value(client, ASB100_REG_FAN_MIN(2));

	/* Register sysfs hooks */
	err = sysfs_create_group(&client->dev.kobj, &asb100_group);
	if (err)
		goto ERROR3;

	data->hwmon_dev = hwmon_device_register(&client->dev);
	if (IS_ERR(data->hwmon_dev)) {
		err = PTR_ERR(data->hwmon_dev);
		goto ERROR4;
	}

	return 0;

ERROR4:
	sysfs_remove_group(&client->dev.kobj, &asb100_group);
ERROR3:
	i2c_unregister_device(data->lm75[1]);
	i2c_unregister_device(data->lm75[0]);
	return err;
}