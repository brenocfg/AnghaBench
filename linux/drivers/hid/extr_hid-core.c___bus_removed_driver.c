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
struct device_driver {int dummy; } ;

/* Variables and functions */
 int bus_rescan_devices (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hid_bus_type ; 

__attribute__((used)) static int __bus_removed_driver(struct device_driver *drv, void *data)
{
	return bus_rescan_devices(&hid_bus_type);
}