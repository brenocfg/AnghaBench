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
struct drm_minor {TYPE_1__* kdev; scalar_t__ index; } ;
struct drm_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct TYPE_3__ {TYPE_2__ kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_MODESET ; 
 int /*<<< orphan*/  DRM_MINOR_PRIMARY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 struct drm_minor** drm_minor_get_slot (struct drm_device*,int /*<<< orphan*/ ) ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int sysfs_create_link (int /*<<< orphan*/ ,TYPE_2__*,char*) ; 

__attribute__((used)) static int create_compat_control_link(struct drm_device *dev)
{
	struct drm_minor *minor;
	char *name;
	int ret;

	if (!drm_core_check_feature(dev, DRIVER_MODESET))
		return 0;

	minor = *drm_minor_get_slot(dev, DRM_MINOR_PRIMARY);
	if (!minor)
		return 0;

	/*
	 * Some existing userspace out there uses the existing of the controlD*
	 * sysfs files to figure out whether it's a modeset driver. It only does
	 * readdir, hence a symlink is sufficient (and the least confusing
	 * option). Otherwise controlD* is entirely unused.
	 *
	 * Old controlD chardev have been allocated in the range
	 * 64-127.
	 */
	name = kasprintf(GFP_KERNEL, "controlD%d", minor->index + 64);
	if (!name)
		return -ENOMEM;

	ret = sysfs_create_link(minor->kdev->kobj.parent,
				&minor->kdev->kobj,
				name);

	kfree(name);

	return ret;
}