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

/* Variables and functions */
 int /*<<< orphan*/  bus_device_info_init (int /*<<< orphan*/ *,char*,char*) ; 
 int bus_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  chipset_driverinfo ; 
 int /*<<< orphan*/  clientbus_driverinfo ; 
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ *) ; 
 int initialized ; 
 int /*<<< orphan*/  visorbus_debugfs_dir ; 
 int /*<<< orphan*/  visorbus_type ; 

int visorbus_init(void)
{
	int err;

	visorbus_debugfs_dir = debugfs_create_dir("visorbus", NULL);
	bus_device_info_init(&clientbus_driverinfo, "clientbus", "visorbus");
	err = bus_register(&visorbus_type);
	if (err < 0)
		return err;
	initialized = true;
	bus_device_info_init(&chipset_driverinfo, "chipset", "visorchipset");
	return 0;
}