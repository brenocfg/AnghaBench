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
struct drm_minor {unsigned int type; int index; int /*<<< orphan*/  kdev; struct drm_device* dev; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 struct drm_minor** drm_minor_get_slot (struct drm_device*,unsigned int) ; 
 int /*<<< orphan*/  drm_minor_lock ; 
 int /*<<< orphan*/  drm_minors_idr ; 
 int /*<<< orphan*/  drm_sysfs_minor_alloc (struct drm_minor*) ; 
 int idr_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload_end () ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct drm_minor*) ; 
 struct drm_minor* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int drm_minor_alloc(struct drm_device *dev, unsigned int type)
{
	struct drm_minor *minor;
	unsigned long flags;
	int r;

	minor = kzalloc(sizeof(*minor), GFP_KERNEL);
	if (!minor)
		return -ENOMEM;

	minor->type = type;
	minor->dev = dev;

	idr_preload(GFP_KERNEL);
	spin_lock_irqsave(&drm_minor_lock, flags);
	r = idr_alloc(&drm_minors_idr,
		      NULL,
		      64 * type,
		      64 * (type + 1),
		      GFP_NOWAIT);
	spin_unlock_irqrestore(&drm_minor_lock, flags);
	idr_preload_end();

	if (r < 0)
		goto err_free;

	minor->index = r;

	minor->kdev = drm_sysfs_minor_alloc(minor);
	if (IS_ERR(minor->kdev)) {
		r = PTR_ERR(minor->kdev);
		goto err_index;
	}

	*drm_minor_get_slot(dev, type) = minor;
	return 0;

err_index:
	spin_lock_irqsave(&drm_minor_lock, flags);
	idr_remove(&drm_minors_idr, minor->index);
	spin_unlock_irqrestore(&drm_minor_lock, flags);
err_free:
	kfree(minor);
	return r;
}