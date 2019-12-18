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
struct device {int /*<<< orphan*/  groups; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_groups ; 
 int device_register (struct device*) ; 

int dim2_sysfs_probe(struct device *dev)
{
	dev->groups = dev_attr_groups;
	return device_register(dev);
}