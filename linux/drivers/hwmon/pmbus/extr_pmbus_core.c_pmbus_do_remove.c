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
struct TYPE_2__ {int /*<<< orphan*/  attrs; } ;
struct pmbus_data {TYPE_1__ group; int /*<<< orphan*/  hwmon_dev; int /*<<< orphan*/  debugfs; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwmon_device_unregister (int /*<<< orphan*/ ) ; 
 struct pmbus_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

int pmbus_do_remove(struct i2c_client *client)
{
	struct pmbus_data *data = i2c_get_clientdata(client);

	debugfs_remove_recursive(data->debugfs);

	hwmon_device_unregister(data->hwmon_dev);
	kfree(data->group.attrs);
	return 0;
}