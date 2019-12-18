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
struct w83795_data {int /*<<< orphan*/  hwmon_dev; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_remove_file_wrapper ; 
 int /*<<< orphan*/  hwmon_device_unregister (int /*<<< orphan*/ ) ; 
 struct w83795_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  w83795_handle_files (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int w83795_remove(struct i2c_client *client)
{
	struct w83795_data *data = i2c_get_clientdata(client);

	hwmon_device_unregister(data->hwmon_dev);
	w83795_handle_files(&client->dev, device_remove_file_wrapper);

	return 0;
}