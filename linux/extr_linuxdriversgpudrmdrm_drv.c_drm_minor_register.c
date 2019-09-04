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
struct drm_minor {int /*<<< orphan*/  index; int /*<<< orphan*/  kdev; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,...) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int device_add (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_debugfs_cleanup (struct drm_minor*) ; 
 int drm_debugfs_init (struct drm_minor*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_debugfs_root ; 
 struct drm_minor** drm_minor_get_slot (struct drm_device*,unsigned int) ; 
 int /*<<< orphan*/  drm_minor_lock ; 
 int /*<<< orphan*/  drm_minors_idr ; 
 int /*<<< orphan*/  idr_replace (int /*<<< orphan*/ *,struct drm_minor*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int drm_minor_register(struct drm_device *dev, unsigned int type)
{
	struct drm_minor *minor;
	unsigned long flags;
	int ret;

	DRM_DEBUG("\n");

	minor = *drm_minor_get_slot(dev, type);
	if (!minor)
		return 0;

	ret = drm_debugfs_init(minor, minor->index, drm_debugfs_root);
	if (ret) {
		DRM_ERROR("DRM: Failed to initialize /sys/kernel/debug/dri.\n");
		goto err_debugfs;
	}

	ret = device_add(minor->kdev);
	if (ret)
		goto err_debugfs;

	/* replace NULL with @minor so lookups will succeed from now on */
	spin_lock_irqsave(&drm_minor_lock, flags);
	idr_replace(&drm_minors_idr, minor, minor->index);
	spin_unlock_irqrestore(&drm_minor_lock, flags);

	DRM_DEBUG("new minor registered %d\n", minor->index);
	return 0;

err_debugfs:
	drm_debugfs_cleanup(minor);
	return ret;
}