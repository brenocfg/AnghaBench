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
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct dme1737_data {int /*<<< orphan*/  hwmon_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dme1737_remove_files (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hwmon_device_unregister (int /*<<< orphan*/ ) ; 
 struct dme1737_data* i2c_get_clientdata (struct i2c_client*) ; 

__attribute__((used)) static int dme1737_i2c_remove(struct i2c_client *client)
{
	struct dme1737_data *data = i2c_get_clientdata(client);

	hwmon_device_unregister(data->hwmon_dev);
	dme1737_remove_files(&client->dev);

	return 0;
}