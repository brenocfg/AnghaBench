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
struct edac_device_ctl_info {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  edac_dbg (int,char*,...) ; 
 int /*<<< orphan*/  kobject_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 

void edac_device_unregister_sysfs_main_kobj(struct edac_device_ctl_info *dev)
{
	edac_dbg(0, "\n");
	edac_dbg(4, "name of kobject is: %s\n", kobject_name(&dev->kobj));

	/*
	 * Unregister the edac device's kobject and
	 * allow for reference count to reach 0 at which point
	 * the callback will be called to:
	 *   a) module_put() this module
	 *   b) 'kfree' the memory
	 */
	kobject_put(&dev->kobj);
}