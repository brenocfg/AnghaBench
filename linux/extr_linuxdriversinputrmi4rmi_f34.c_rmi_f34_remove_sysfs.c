#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct rmi_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  rmi_firmware_attr_group ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void rmi_f34_remove_sysfs(struct rmi_device *rmi_dev)
{
	sysfs_remove_group(&rmi_dev->dev.kobj, &rmi_firmware_attr_group);
}