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
struct mcp3021_data {int /*<<< orphan*/  hwmon_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct i2c_client {TYPE_1__ dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  attr; } ;

/* Variables and functions */
 TYPE_2__ dev_attr_in0_input ; 
 int /*<<< orphan*/  hwmon_device_unregister (int /*<<< orphan*/ ) ; 
 struct mcp3021_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  sysfs_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mcp3021_remove(struct i2c_client *client)
{
	struct mcp3021_data *data = i2c_get_clientdata(client);

	hwmon_device_unregister(data->hwmon_dev);
	sysfs_remove_file(&client->dev.kobj, &dev_attr_in0_input.attr);

	return 0;
}