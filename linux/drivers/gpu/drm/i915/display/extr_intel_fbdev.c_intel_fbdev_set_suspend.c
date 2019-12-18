#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct fb_info* fbdev; } ;
struct intel_fbdev {TYPE_3__ helper; TYPE_1__* fb; int /*<<< orphan*/  vma; } ;
struct fb_info {int /*<<< orphan*/  screen_size; int /*<<< orphan*/  screen_base; } ;
struct drm_i915_private {int /*<<< orphan*/  fbdev_suspend_work; struct intel_fbdev* fbdev; } ;
struct drm_device {int dummy; } ;
struct TYPE_5__ {scalar_t__ stolen; } ;
struct TYPE_4__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int FBINFO_STATE_RUNNING ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  console_lock () ; 
 int /*<<< orphan*/  console_trylock () ; 
 int /*<<< orphan*/  console_unlock () ; 
 int /*<<< orphan*/  drm_fb_helper_set_suspend (TYPE_3__*,int) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 TYPE_2__* intel_fb_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_fbdev_hpd_set_suspend (struct intel_fbdev*,int) ; 
 int /*<<< orphan*/  memset_io (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

void intel_fbdev_set_suspend(struct drm_device *dev, int state, bool synchronous)
{
	struct drm_i915_private *dev_priv = to_i915(dev);
	struct intel_fbdev *ifbdev = dev_priv->fbdev;
	struct fb_info *info;

	if (!ifbdev || !ifbdev->vma)
		return;

	info = ifbdev->helper.fbdev;

	if (synchronous) {
		/* Flush any pending work to turn the console on, and then
		 * wait to turn it off. It must be synchronous as we are
		 * about to suspend or unload the driver.
		 *
		 * Note that from within the work-handler, we cannot flush
		 * ourselves, so only flush outstanding work upon suspend!
		 */
		if (state != FBINFO_STATE_RUNNING)
			flush_work(&dev_priv->fbdev_suspend_work);

		console_lock();
	} else {
		/*
		 * The console lock can be pretty contented on resume due
		 * to all the printk activity.  Try to keep it out of the hot
		 * path of resume if possible.
		 */
		WARN_ON(state != FBINFO_STATE_RUNNING);
		if (!console_trylock()) {
			/* Don't block our own workqueue as this can
			 * be run in parallel with other i915.ko tasks.
			 */
			schedule_work(&dev_priv->fbdev_suspend_work);
			return;
		}
	}

	/* On resume from hibernation: If the object is shmemfs backed, it has
	 * been restored from swap. If the object is stolen however, it will be
	 * full of whatever garbage was left in there.
	 */
	if (state == FBINFO_STATE_RUNNING &&
	    intel_fb_obj(&ifbdev->fb->base)->stolen)
		memset_io(info->screen_base, 0, info->screen_size);

	drm_fb_helper_set_suspend(&ifbdev->helper, state);
	console_unlock();

	intel_fbdev_hpd_set_suspend(ifbdev, state);
}