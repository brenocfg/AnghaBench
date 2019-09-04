#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {scalar_t__ minor; } ;
struct fschmd_data {size_t kind; int /*<<< orphan*/  kref; scalar_t__ hwmon_dev; int /*<<< orphan*/  watchdog_lock; int /*<<< orphan*/ * client; int /*<<< orphan*/  list; scalar_t__ watchdog_is_open; TYPE_1__ watchdog_miscdev; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev_attr; } ;

/* Variables and functions */
 int* FSCHMD_NO_FAN_SENSORS ; 
 int* FSCHMD_NO_TEMP_SENSORS ; 
 int* FSCHMD_NO_VOLT_SENSORS ; 
 int /*<<< orphan*/  dev_attr_alert_led ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* fschmd_attr ; 
 TYPE_3__* fschmd_fan_attr ; 
 int /*<<< orphan*/  fschmd_release_resources ; 
 TYPE_2__* fschmd_temp_attr ; 
 int /*<<< orphan*/  hwmon_device_unregister (scalar_t__) ; 
 struct fschmd_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  misc_deregister (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watchdog_data_mutex ; 
 int /*<<< orphan*/  watchdog_stop (struct fschmd_data*) ; 

__attribute__((used)) static int fschmd_remove(struct i2c_client *client)
{
	struct fschmd_data *data = i2c_get_clientdata(client);
	int i;

	/* Unregister the watchdog (if registered) */
	if (data->watchdog_miscdev.minor) {
		misc_deregister(&data->watchdog_miscdev);
		if (data->watchdog_is_open) {
			dev_warn(&client->dev,
				"i2c client detached with watchdog open! "
				"Stopping watchdog.\n");
			watchdog_stop(data);
		}
		mutex_lock(&watchdog_data_mutex);
		list_del(&data->list);
		mutex_unlock(&watchdog_data_mutex);
		/* Tell the watchdog code the client is gone */
		mutex_lock(&data->watchdog_lock);
		data->client = NULL;
		mutex_unlock(&data->watchdog_lock);
	}

	/*
	 * Check if registered in case we're called from fschmd_detect
	 * to cleanup after an error
	 */
	if (data->hwmon_dev)
		hwmon_device_unregister(data->hwmon_dev);

	device_remove_file(&client->dev, &dev_attr_alert_led);
	for (i = 0; i < (FSCHMD_NO_VOLT_SENSORS[data->kind]); i++)
		device_remove_file(&client->dev, &fschmd_attr[i].dev_attr);
	for (i = 0; i < (FSCHMD_NO_TEMP_SENSORS[data->kind] * 4); i++)
		device_remove_file(&client->dev,
					&fschmd_temp_attr[i].dev_attr);
	for (i = 0; i < (FSCHMD_NO_FAN_SENSORS[data->kind] * 5); i++)
		device_remove_file(&client->dev,
					&fschmd_fan_attr[i].dev_attr);

	mutex_lock(&watchdog_data_mutex);
	kref_put(&data->kref, fschmd_release_resources);
	mutex_unlock(&watchdog_data_mutex);

	return 0;
}