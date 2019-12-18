#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  kobj; TYPE_1__* driver; int /*<<< orphan*/  parent; } ;
struct typec_altmode {int active; int mode; TYPE_2__ dev; } ;
typedef  int /*<<< orphan*/  dir ;
struct TYPE_3__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  KOBJ_CHANGE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  is_typec_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  sysfs_notify (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

void typec_altmode_update_active(struct typec_altmode *adev, bool active)
{
	char dir[6];

	if (adev->active == active)
		return;

	if (!is_typec_port(adev->dev.parent) && adev->dev.driver) {
		if (!active)
			module_put(adev->dev.driver->owner);
		else
			WARN_ON(!try_module_get(adev->dev.driver->owner));
	}

	adev->active = active;
	snprintf(dir, sizeof(dir), "mode%d", adev->mode);
	sysfs_notify(&adev->dev.kobj, dir, "active");
	sysfs_notify(&adev->dev.kobj, NULL, "active");
	kobject_uevent(&adev->dev.kobj, KOBJ_CHANGE);
}