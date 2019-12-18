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
struct sdw_bus {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_for_each_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdw_bus_debugfs_exit (struct sdw_bus*) ; 
 int /*<<< orphan*/  sdw_delete_slave ; 

void sdw_delete_bus_master(struct sdw_bus *bus)
{
	device_for_each_child(bus->dev, NULL, sdw_delete_slave);

	sdw_bus_debugfs_exit(bus);
}