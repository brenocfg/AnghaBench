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
struct adm1026_data {int config1; int /*<<< orphan*/ ** groups; int /*<<< orphan*/  vrm; int /*<<< orphan*/  update_lock; struct i2c_client* client; } ;

/* Variables and functions */
 int CFG1_AIN8_9 ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PTR_ERR_OR_ZERO (struct device*) ; 
 int /*<<< orphan*/  adm1026_group ; 
 int /*<<< orphan*/  adm1026_group_in8_9 ; 
 int /*<<< orphan*/  adm1026_group_temp3 ; 
 int /*<<< orphan*/  adm1026_init_client (struct i2c_client*) ; 
 struct device* devm_hwmon_device_register_with_groups (struct device*,int /*<<< orphan*/ ,struct adm1026_data*,int /*<<< orphan*/ **) ; 
 struct adm1026_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct adm1026_data*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vid_which_vrm () ; 

__attribute__((used)) static int adm1026_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct device *hwmon_dev;
	struct adm1026_data *data;

	data = devm_kzalloc(dev, sizeof(struct adm1026_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	i2c_set_clientdata(client, data);
	data->client = client;
	mutex_init(&data->update_lock);

	/* Set the VRM version */
	data->vrm = vid_which_vrm();

	/* Initialize the ADM1026 chip */
	adm1026_init_client(client);

	/* sysfs hooks */
	data->groups[0] = &adm1026_group;
	if (data->config1 & CFG1_AIN8_9)
		data->groups[1] = &adm1026_group_in8_9;
	else
		data->groups[1] = &adm1026_group_temp3;

	hwmon_dev = devm_hwmon_device_register_with_groups(dev, client->name,
							   data, data->groups);
	return PTR_ERR_OR_ZERO(hwmon_dev);
}