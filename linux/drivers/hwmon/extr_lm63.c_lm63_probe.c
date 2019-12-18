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
struct lm63_data {int kind; int temp2_offset; int config; int /*<<< orphan*/ ** groups; int /*<<< orphan*/  update_lock; struct i2c_client* client; } ;
struct i2c_device_id {int driver_data; } ;
struct device {scalar_t__ of_node; } ;
struct i2c_client {int /*<<< orphan*/  name; struct device dev; } ;
typedef  enum chips { ____Placeholder_chips } chips ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PTR_ERR_OR_ZERO (struct device*) ; 
 struct device* devm_hwmon_device_register_with_groups (struct device*,int /*<<< orphan*/ ,struct lm63_data*,int /*<<< orphan*/ **) ; 
 struct lm63_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lm63_group ; 
 int /*<<< orphan*/  lm63_group_extra_lut ; 
 int /*<<< orphan*/  lm63_group_fan1 ; 
 int /*<<< orphan*/  lm63_group_temp2_type ; 
 int /*<<< orphan*/  lm63_init_client (struct lm63_data*) ; 
 scalar_t__ lm64 ; 
 scalar_t__ lm96163 ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ of_device_get_match_data (struct device*) ; 

__attribute__((used)) static int lm63_probe(struct i2c_client *client,
		      const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct device *hwmon_dev;
	struct lm63_data *data;
	int groups = 0;

	data = devm_kzalloc(dev, sizeof(struct lm63_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->client = client;
	mutex_init(&data->update_lock);

	/* Set the device type */
	if (client->dev.of_node)
		data->kind = (enum chips)of_device_get_match_data(&client->dev);
	else
		data->kind = id->driver_data;
	if (data->kind == lm64)
		data->temp2_offset = 16000;

	/* Initialize chip */
	lm63_init_client(data);

	/* Register sysfs hooks */
	data->groups[groups++] = &lm63_group;
	if (data->config & 0x04)	/* tachometer enabled */
		data->groups[groups++] = &lm63_group_fan1;

	if (data->kind == lm96163) {
		data->groups[groups++] = &lm63_group_temp2_type;
		data->groups[groups++] = &lm63_group_extra_lut;
	}

	hwmon_dev = devm_hwmon_device_register_with_groups(dev, client->name,
							   data, data->groups);
	return PTR_ERR_OR_ZERO(hwmon_dev);
}