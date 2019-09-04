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
 int /*<<< orphan*/  EDAC_DEVICE_SYMLINK ; 
 int /*<<< orphan*/  edac_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  edac_device_delete_instances (struct edac_device_ctl_info*) ; 
 int /*<<< orphan*/  edac_device_remove_main_sysfs_attributes (struct edac_device_ctl_info*) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void edac_device_remove_sysfs(struct edac_device_ctl_info *edac_dev)
{
	edac_dbg(0, "\n");

	/* remove any main attributes for this device */
	edac_device_remove_main_sysfs_attributes(edac_dev);

	/* remove the device sym link */
	sysfs_remove_link(&edac_dev->kobj, EDAC_DEVICE_SYMLINK);

	/* walk the instance/block kobject tree, deconstructing it */
	edac_device_delete_instances(edac_dev);
}