#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pcf8591_data {int /*<<< orphan*/  hwmon_dev; int /*<<< orphan*/  update_lock; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct i2c_client {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_attr_in2_input ; 
 int /*<<< orphan*/  dev_attr_in3_input ; 
 int device_create_file (TYPE_1__*,int /*<<< orphan*/ *) ; 
 struct pcf8591_data* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwmon_device_register (TYPE_1__*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct pcf8591_data*) ; 
 int input_mode ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcf8591_attr_group ; 
 int /*<<< orphan*/  pcf8591_attr_group_opt ; 
 int /*<<< orphan*/  pcf8591_init_client (struct i2c_client*) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pcf8591_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct pcf8591_data *data;
	int err;

	data = devm_kzalloc(&client->dev, sizeof(struct pcf8591_data),
			    GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	i2c_set_clientdata(client, data);
	mutex_init(&data->update_lock);

	/* Initialize the PCF8591 chip */
	pcf8591_init_client(client);

	/* Register sysfs hooks */
	err = sysfs_create_group(&client->dev.kobj, &pcf8591_attr_group);
	if (err)
		return err;

	/* Register input2 if not in "two differential inputs" mode */
	if (input_mode != 3) {
		err = device_create_file(&client->dev, &dev_attr_in2_input);
		if (err)
			goto exit_sysfs_remove;
	}

	/* Register input3 only in "four single ended inputs" mode */
	if (input_mode == 0) {
		err = device_create_file(&client->dev, &dev_attr_in3_input);
		if (err)
			goto exit_sysfs_remove;
	}

	data->hwmon_dev = hwmon_device_register(&client->dev);
	if (IS_ERR(data->hwmon_dev)) {
		err = PTR_ERR(data->hwmon_dev);
		goto exit_sysfs_remove;
	}

	return 0;

exit_sysfs_remove:
	sysfs_remove_group(&client->dev.kobj, &pcf8591_attr_group_opt);
	sysfs_remove_group(&client->dev.kobj, &pcf8591_attr_group);
	return err;
}