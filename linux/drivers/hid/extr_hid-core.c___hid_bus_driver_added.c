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
struct hid_driver {scalar_t__ match; } ;
struct device_driver {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __hid_bus_reprobe_drivers ; 
 int /*<<< orphan*/  bus_for_each_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct hid_driver*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_bus_type ; 
 struct hid_driver* to_hid_driver (struct device_driver*) ; 

__attribute__((used)) static int __hid_bus_driver_added(struct device_driver *drv, void *data)
{
	struct hid_driver *hdrv = to_hid_driver(drv);

	if (hdrv->match) {
		bus_for_each_dev(&hid_bus_type, NULL, hdrv,
				 __hid_bus_reprobe_drivers);
	}

	return 0;
}