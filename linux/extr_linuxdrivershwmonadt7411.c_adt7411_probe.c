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
struct adt7411_data {int /*<<< orphan*/  next_update; int /*<<< orphan*/  update_lock; int /*<<< orphan*/  device_lock; struct i2c_client* client; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PTR_ERR_OR_ZERO (struct device*) ; 
 int /*<<< orphan*/  adt7411_chip_info ; 
 int /*<<< orphan*/  adt7411_groups ; 
 int adt7411_init_device (struct adt7411_data*) ; 
 struct device* devm_hwmon_device_register_with_info (struct device*,int /*<<< orphan*/ ,struct adt7411_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct adt7411_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct adt7411_data*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adt7411_probe(struct i2c_client *client,
				   const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct adt7411_data *data;
	struct device *hwmon_dev;
	int ret;

	data = devm_kzalloc(dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	i2c_set_clientdata(client, data);
	data->client = client;
	mutex_init(&data->device_lock);
	mutex_init(&data->update_lock);

	ret = adt7411_init_device(data);
	if (ret < 0)
		return ret;

	/* force update on first occasion */
	data->next_update = jiffies;

	hwmon_dev = devm_hwmon_device_register_with_info(dev, client->name,
							 data,
							 &adt7411_chip_info,
							 adt7411_groups);
	return PTR_ERR_OR_ZERO(hwmon_dev);
}