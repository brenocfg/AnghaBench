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
struct intel_fbdev {int /*<<< orphan*/  helper; } ;
struct drm_i915_private {int /*<<< orphan*/  fbdev_suspend_work; struct intel_fbdev* fbdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current_is_async () ; 
 int /*<<< orphan*/  drm_fb_helper_unregister_fbi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_fbdev_sync (struct intel_fbdev*) ; 

void intel_fbdev_unregister(struct drm_i915_private *dev_priv)
{
	struct intel_fbdev *ifbdev = dev_priv->fbdev;

	if (!ifbdev)
		return;

	cancel_work_sync(&dev_priv->fbdev_suspend_work);
	if (!current_is_async())
		intel_fbdev_sync(ifbdev);

	drm_fb_helper_unregister_fbi(&ifbdev->helper);
}