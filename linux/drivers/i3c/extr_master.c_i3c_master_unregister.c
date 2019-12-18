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
struct i3c_master_controller {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i3c_master_bus_cleanup (struct i3c_master_controller*) ; 
 int /*<<< orphan*/  i3c_master_i2c_adapter_cleanup (struct i3c_master_controller*) ; 
 int /*<<< orphan*/  i3c_master_unregister_i3c_devs (struct i3c_master_controller*) ; 

int i3c_master_unregister(struct i3c_master_controller *master)
{
	i3c_master_i2c_adapter_cleanup(master);
	i3c_master_unregister_i3c_devs(master);
	i3c_master_bus_cleanup(master);
	device_unregister(&master->dev);

	return 0;
}