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
struct w83781d_data {int /*<<< orphan*/ * lm75; int /*<<< orphan*/  hwmon_dev; } ;
struct device {int dummy; } ;
struct i2c_client {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  hwmon_device_unregister (int /*<<< orphan*/ ) ; 
 struct w83781d_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w83781d_remove_files (struct device*) ; 

__attribute__((used)) static int
w83781d_remove(struct i2c_client *client)
{
	struct w83781d_data *data = i2c_get_clientdata(client);
	struct device *dev = &client->dev;

	hwmon_device_unregister(data->hwmon_dev);
	w83781d_remove_files(dev);

	i2c_unregister_device(data->lm75[0]);
	i2c_unregister_device(data->lm75[1]);

	return 0;
}