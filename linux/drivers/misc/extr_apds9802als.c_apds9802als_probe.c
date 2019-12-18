#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct i2c_device_id {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  kobj; } ;
struct i2c_client {TYPE_1__ dev; } ;
struct als_data {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  als_set_default_config (struct i2c_client*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct als_data*) ; 
 int /*<<< orphan*/  kfree (struct als_data*) ; 
 struct als_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_als_gr ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (TYPE_1__*) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int apds9802als_probe(struct i2c_client *client,
			     const struct i2c_device_id *id)
{
	int res;
	struct als_data *data;

	data = kzalloc(sizeof(struct als_data), GFP_KERNEL);
	if (data == NULL) {
		dev_err(&client->dev, "Memory allocation failed\n");
		return -ENOMEM;
	}
	i2c_set_clientdata(client, data);
	res = sysfs_create_group(&client->dev.kobj, &m_als_gr);
	if (res) {
		dev_err(&client->dev, "device create file failed\n");
		goto als_error1;
	}
	dev_info(&client->dev, "ALS chip found\n");
	als_set_default_config(client);
	mutex_init(&data->mutex);

	pm_runtime_set_active(&client->dev);
	pm_runtime_enable(&client->dev);

	return res;
als_error1:
	kfree(data);
	return res;
}