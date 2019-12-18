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
 int /*<<< orphan*/  qeth_l2_only_attr_groups ; 
 int sysfs_create_groups (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int qeth_l2_create_device_attributes(struct device *dev)
{
	return sysfs_create_groups(&dev->kobj, qeth_l2_only_attr_groups);
}