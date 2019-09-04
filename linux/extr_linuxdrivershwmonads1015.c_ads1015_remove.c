#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct ads1015_data {int /*<<< orphan*/  hwmon_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_attr; } ;

/* Variables and functions */
 int ADS1015_CHANNELS ; 
 TYPE_1__* ads1015_in ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hwmon_device_unregister (int /*<<< orphan*/ ) ; 
 struct ads1015_data* i2c_get_clientdata (struct i2c_client*) ; 

__attribute__((used)) static int ads1015_remove(struct i2c_client *client)
{
	struct ads1015_data *data = i2c_get_clientdata(client);
	int k;

	hwmon_device_unregister(data->hwmon_dev);
	for (k = 0; k < ADS1015_CHANNELS; ++k)
		device_remove_file(&client->dev, &ads1015_in[k].dev_attr);
	return 0;
}