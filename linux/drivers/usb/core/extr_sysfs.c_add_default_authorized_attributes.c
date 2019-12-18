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
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_bus_attr_group ; 

__attribute__((used)) static int add_default_authorized_attributes(struct device *dev)
{
	int rc = 0;

	if (is_usb_device(dev))
		rc = sysfs_create_group(&dev->kobj, &usb_bus_attr_group);

	return rc;
}