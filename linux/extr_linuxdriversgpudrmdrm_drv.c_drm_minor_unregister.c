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
struct drm_minor {int /*<<< orphan*/  kdev; int /*<<< orphan*/  index; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_is_registered (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_debugfs_cleanup (struct drm_minor*) ; 
 struct drm_minor** drm_minor_get_slot (struct drm_device*,unsigned int) ; 
 int /*<<< orphan*/  drm_minor_lock ; 
 int /*<<< orphan*/  drm_minors_idr ; 
 int /*<<< orphan*/  idr_replace (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void drm_minor_unregister(struct drm_device *dev, unsigned int type)
{
	struct drm_minor *minor;
	unsigned long flags;

	minor = *drm_minor_get_slot(dev, type);
	if (!minor || !device_is_registered(minor->kdev))
		return;

	/* replace @minor with NULL so lookups will fail from now on */
	spin_lock_irqsave(&drm_minor_lock, flags);
	idr_replace(&drm_minors_idr, NULL, minor->index);
	spin_unlock_irqrestore(&drm_minor_lock, flags);

	device_del(minor->kdev);
	dev_set_drvdata(minor->kdev, NULL); /* safety belt */
	drm_debugfs_cleanup(minor);
}