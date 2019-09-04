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
struct gl518_data {scalar_t__ type; int alarm_mask; int /*<<< orphan*/ ** groups; int /*<<< orphan*/  update_lock; struct i2c_client* client; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GL518_REG_REVISION ; 
 int PTR_ERR_OR_ZERO (struct device*) ; 
 struct device* devm_hwmon_device_register_with_groups (struct device*,int /*<<< orphan*/ ,struct gl518_data*,int /*<<< orphan*/ **) ; 
 struct gl518_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl518_group ; 
 int /*<<< orphan*/  gl518_group_r80 ; 
 int /*<<< orphan*/  gl518_init_client (struct i2c_client*) ; 
 int gl518_read_value (struct i2c_client*,int /*<<< orphan*/ ) ; 
 scalar_t__ gl518sm_r00 ; 
 scalar_t__ gl518sm_r80 ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gl518_probe(struct i2c_client *client,
		       const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct device *hwmon_dev;
	struct gl518_data *data;
	int revision;

	data = devm_kzalloc(dev, sizeof(struct gl518_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->client = client;
	revision = gl518_read_value(client, GL518_REG_REVISION);
	data->type = revision == 0x80 ? gl518sm_r80 : gl518sm_r00;
	mutex_init(&data->update_lock);

	/* Initialize the GL518SM chip */
	data->alarm_mask = 0xff;
	gl518_init_client(client);

	/* sysfs hooks */
	data->groups[0] = &gl518_group;
	if (data->type == gl518sm_r80)
		data->groups[1] = &gl518_group_r80;

	hwmon_dev = devm_hwmon_device_register_with_groups(dev, client->name,
							   data, data->groups);
	return PTR_ERR_OR_ZERO(hwmon_dev);
}