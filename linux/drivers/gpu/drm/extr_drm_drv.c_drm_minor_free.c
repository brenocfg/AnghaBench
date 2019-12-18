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
 struct drm_minor** drm_minor_get_slot (struct drm_device*,unsigned int) ; 
 int /*<<< orphan*/  drm_minor_lock ; 
 int /*<<< orphan*/  drm_minors_idr ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct drm_minor*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void drm_minor_free(struct drm_device *dev, unsigned int type)
{
	struct drm_minor **slot, *minor;
	unsigned long flags;

	slot = drm_minor_get_slot(dev, type);
	minor = *slot;
	if (!minor)
		return;

	put_device(minor->kdev);

	spin_lock_irqsave(&drm_minor_lock, flags);
	idr_remove(&drm_minors_idr, minor->index);
	spin_unlock_irqrestore(&drm_minor_lock, flags);

	kfree(minor);
	*slot = NULL;
}