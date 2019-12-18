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
typedef  int u8 ;
struct w83l786ng_data {int* fan_div; void** fan_min; int /*<<< orphan*/  update_lock; struct i2c_client* client; } ;
struct i2c_device_id {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  name; struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PTR_ERR_OR_ZERO (struct device*) ; 
 int /*<<< orphan*/  W83L786NG_REG_FAN_DIV ; 
 int /*<<< orphan*/  W83L786NG_REG_FAN_MIN (int) ; 
 struct device* devm_hwmon_device_register_with_groups (struct device*,int /*<<< orphan*/ ,struct w83l786ng_data*,int /*<<< orphan*/ ) ; 
 struct w83l786ng_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  w83l786ng_groups ; 
 int /*<<< orphan*/  w83l786ng_init_client (struct i2c_client*) ; 
 void* w83l786ng_read_value (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
w83l786ng_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct w83l786ng_data *data;
	struct device *hwmon_dev;
	int i;
	u8 reg_tmp;

	data = devm_kzalloc(dev, sizeof(struct w83l786ng_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->client = client;
	mutex_init(&data->update_lock);

	/* Initialize the chip */
	w83l786ng_init_client(client);

	/* A few vars need to be filled upon startup */
	for (i = 0; i < 2; i++) {
		data->fan_min[i] = w83l786ng_read_value(client,
		    W83L786NG_REG_FAN_MIN(i));
	}

	/* Update the fan divisor */
	reg_tmp = w83l786ng_read_value(client, W83L786NG_REG_FAN_DIV);
	data->fan_div[0] = reg_tmp & 0x07;
	data->fan_div[1] = (reg_tmp >> 4) & 0x07;

	hwmon_dev = devm_hwmon_device_register_with_groups(dev, client->name,
							   data,
							   w83l786ng_groups);
	return PTR_ERR_OR_ZERO(hwmon_dev);
}