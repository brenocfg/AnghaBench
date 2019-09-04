#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct i2c_device_id {int driver_data; } ;
struct TYPE_9__ {scalar_t__ of_node; } ;
struct i2c_client {TYPE_2__ dev; } ;
struct ads1015_data {int id; int /*<<< orphan*/  hwmon_dev; TYPE_1__* channel_data; int /*<<< orphan*/  update_lock; } ;
typedef  enum ads1015_chips { ____Placeholder_ads1015_chips } ads1015_chips ;
struct TYPE_10__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_8__ {int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 unsigned int ADS1015_CHANNELS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ads1015_get_channels_config (struct i2c_client*) ; 
 TYPE_7__* ads1015_in ; 
 int device_create_file (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (TYPE_2__*,int /*<<< orphan*/ *) ; 
 struct ads1015_data* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwmon_device_register (TYPE_2__*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct ads1015_data*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ of_device_get_match_data (TYPE_2__*) ; 

__attribute__((used)) static int ads1015_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct ads1015_data *data;
	int err;
	unsigned int k;

	data = devm_kzalloc(&client->dev, sizeof(struct ads1015_data),
			    GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	if (client->dev.of_node)
		data->id = (enum ads1015_chips)
			of_device_get_match_data(&client->dev);
	else
		data->id = id->driver_data;
	i2c_set_clientdata(client, data);
	mutex_init(&data->update_lock);

	/* build sysfs attribute group */
	ads1015_get_channels_config(client);
	for (k = 0; k < ADS1015_CHANNELS; ++k) {
		if (!data->channel_data[k].enabled)
			continue;
		err = device_create_file(&client->dev, &ads1015_in[k].dev_attr);
		if (err)
			goto exit_remove;
	}

	data->hwmon_dev = hwmon_device_register(&client->dev);
	if (IS_ERR(data->hwmon_dev)) {
		err = PTR_ERR(data->hwmon_dev);
		goto exit_remove;
	}

	return 0;

exit_remove:
	for (k = 0; k < ADS1015_CHANNELS; ++k)
		device_remove_file(&client->dev, &ads1015_in[k].dev_attr);
	return err;
}