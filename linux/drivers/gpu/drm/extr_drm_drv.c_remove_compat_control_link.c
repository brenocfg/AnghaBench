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
struct drm_minor {TYPE_2__* kdev; scalar_t__ index; } ;
struct drm_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {TYPE_1__ kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_MODESET ; 
 int /*<<< orphan*/  DRM_MINOR_PRIMARY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 struct drm_minor** drm_minor_get_slot (struct drm_device*,int /*<<< orphan*/ ) ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void remove_compat_control_link(struct drm_device *dev)
{
	struct drm_minor *minor;
	char *name;

	if (!drm_core_check_feature(dev, DRIVER_MODESET))
		return;

	minor = *drm_minor_get_slot(dev, DRM_MINOR_PRIMARY);
	if (!minor)
		return;

	name = kasprintf(GFP_KERNEL, "controlD%d", minor->index + 64);
	if (!name)
		return;

	sysfs_remove_link(minor->kdev->kobj.parent, name);

	kfree(name);
}