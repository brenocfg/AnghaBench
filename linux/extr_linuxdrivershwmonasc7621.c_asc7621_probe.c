#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; } ;
struct asc7621_data {int /*<<< orphan*/  class_dev; int /*<<< orphan*/  update_lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_5__ {TYPE_1__ sda; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asc7621_init_client (struct i2c_client*) ; 
 TYPE_2__* asc7621_params ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct asc7621_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwmon_device_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct asc7621_data*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
asc7621_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	struct asc7621_data *data;
	int i, err;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -EIO;

	data = devm_kzalloc(&client->dev, sizeof(struct asc7621_data),
			    GFP_KERNEL);
	if (data == NULL)
		return -ENOMEM;

	i2c_set_clientdata(client, data);
	mutex_init(&data->update_lock);

	/* Initialize the asc7621 chip */
	asc7621_init_client(client);

	/* Create the sysfs entries */
	for (i = 0; i < ARRAY_SIZE(asc7621_params); i++) {
		err =
		    device_create_file(&client->dev,
				       &(asc7621_params[i].sda.dev_attr));
		if (err)
			goto exit_remove;
	}

	data->class_dev = hwmon_device_register(&client->dev);
	if (IS_ERR(data->class_dev)) {
		err = PTR_ERR(data->class_dev);
		goto exit_remove;
	}

	return 0;

exit_remove:
	for (i = 0; i < ARRAY_SIZE(asc7621_params); i++) {
		device_remove_file(&client->dev,
				   &(asc7621_params[i].sda.dev_attr));
	}

	return err;
}