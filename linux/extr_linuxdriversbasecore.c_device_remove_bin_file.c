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
struct bin_attribute {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sysfs_remove_bin_file (int /*<<< orphan*/ *,struct bin_attribute const*) ; 

void device_remove_bin_file(struct device *dev,
			    const struct bin_attribute *attr)
{
	if (dev)
		sysfs_remove_bin_file(&dev->kobj, attr);
}