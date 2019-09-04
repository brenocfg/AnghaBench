#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct w83l785ts_data {int /*<<< orphan*/  hwmon_dev; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev_attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hwmon_device_unregister (int /*<<< orphan*/ ) ; 
 struct w83l785ts_data* i2c_get_clientdata (struct i2c_client*) ; 
 TYPE_2__ sensor_dev_attr_temp1_input ; 
 TYPE_1__ sensor_dev_attr_temp1_max ; 

__attribute__((used)) static int w83l785ts_remove(struct i2c_client *client)
{
	struct w83l785ts_data *data = i2c_get_clientdata(client);

	hwmon_device_unregister(data->hwmon_dev);
	device_remove_file(&client->dev,
			   &sensor_dev_attr_temp1_input.dev_attr);
	device_remove_file(&client->dev,
			   &sensor_dev_attr_temp1_max.dev_attr);

	return 0;
}