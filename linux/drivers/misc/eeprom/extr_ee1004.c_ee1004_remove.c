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
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct i2c_client {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ee1004_bus_lock ; 
 scalar_t__ ee1004_dev_count ; 
 int /*<<< orphan*/ ** ee1004_set_page ; 
 int /*<<< orphan*/  eeprom_attr ; 
 int /*<<< orphan*/  i2c_unregister_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_bin_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ee1004_remove(struct i2c_client *client)
{
	int i;

	sysfs_remove_bin_file(&client->dev.kobj, &eeprom_attr);

	/* Remove page select clients if this is the last device */
	mutex_lock(&ee1004_bus_lock);
	if (--ee1004_dev_count == 0) {
		for (i = 0; i < 2; i++) {
			i2c_unregister_device(ee1004_set_page[i]);
			ee1004_set_page[i] = NULL;
		}
	}
	mutex_unlock(&ee1004_bus_lock);

	return 0;
}