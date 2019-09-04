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
struct lm80_data {int** fan; int /*<<< orphan*/  update_lock; struct i2c_client* client; } ;
struct i2c_device_id {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  name; struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LM80_REG_FAN_MIN (int) ; 
 int PTR_ERR_OR_ZERO (struct device*) ; 
 struct device* devm_hwmon_device_register_with_groups (struct device*,int /*<<< orphan*/ ,struct lm80_data*,int /*<<< orphan*/ ) ; 
 struct lm80_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 size_t f_min ; 
 int /*<<< orphan*/  lm80_groups ; 
 int /*<<< orphan*/  lm80_init_client (struct i2c_client*) ; 
 int lm80_read_value (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lm80_probe(struct i2c_client *client,
		      const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct device *hwmon_dev;
	struct lm80_data *data;
	int rv;

	data = devm_kzalloc(dev, sizeof(struct lm80_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->client = client;
	mutex_init(&data->update_lock);

	/* Initialize the LM80 chip */
	lm80_init_client(client);

	/* A few vars need to be filled upon startup */
	rv = lm80_read_value(client, LM80_REG_FAN_MIN(1));
	if (rv < 0)
		return rv;
	data->fan[f_min][0] = rv;
	rv = lm80_read_value(client, LM80_REG_FAN_MIN(2));
	if (rv < 0)
		return rv;
	data->fan[f_min][1] = rv;

	hwmon_dev = devm_hwmon_device_register_with_groups(dev, client->name,
							   data, lm80_groups);

	return PTR_ERR_OR_ZERO(hwmon_dev);
}