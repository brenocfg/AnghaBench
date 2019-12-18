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
struct device {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 scalar_t__ is_usb_device (struct device*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_bus_attr_group ; 

__attribute__((used)) static void remove_default_authorized_attributes(struct device *dev)
{
	if (is_usb_device(dev)) {
		sysfs_remove_group(&dev->kobj, &usb_bus_attr_group);
	}
}