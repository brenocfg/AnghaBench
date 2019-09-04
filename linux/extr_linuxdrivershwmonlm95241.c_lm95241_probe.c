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
struct lm95241_data {int /*<<< orphan*/  update_lock; struct i2c_client* client; } ;
struct i2c_device_id {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  name; struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PTR_ERR_OR_ZERO (struct device*) ; 
 struct device* devm_hwmon_device_register_with_info (struct device*,int /*<<< orphan*/ ,struct lm95241_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct lm95241_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lm95241_chip_info ; 
 int /*<<< orphan*/  lm95241_init_client (struct i2c_client*,struct lm95241_data*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lm95241_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct lm95241_data *data;
	struct device *hwmon_dev;

	data = devm_kzalloc(dev, sizeof(struct lm95241_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->client = client;
	mutex_init(&data->update_lock);

	/* Initialize the LM95241 chip */
	lm95241_init_client(client, data);

	hwmon_dev = devm_hwmon_device_register_with_info(dev, client->name,
							   data,
							   &lm95241_chip_info,
							   NULL);
	return PTR_ERR_OR_ZERO(hwmon_dev);
}