#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct drm_fb_helper {int delayed_hotplug; int /*<<< orphan*/  fbdev; int /*<<< orphan*/  lock; TYPE_1__* fb; int /*<<< orphan*/  client; int /*<<< orphan*/  dev; int /*<<< orphan*/  preferred_bpp; scalar_t__ deferred_setup; } ;
struct TYPE_2__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int __drm_fb_helper_initial_config_and_unlock (struct drm_fb_helper*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_client_modeset_probe (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_fb_helper_set_par (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_fbdev_emulation ; 
 int /*<<< orphan*/  drm_master_internal_acquire (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_master_internal_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_setup_crtcs_fb (struct drm_fb_helper*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int drm_fb_helper_hotplug_event(struct drm_fb_helper *fb_helper)
{
	int err = 0;

	if (!drm_fbdev_emulation || !fb_helper)
		return 0;

	mutex_lock(&fb_helper->lock);
	if (fb_helper->deferred_setup) {
		err = __drm_fb_helper_initial_config_and_unlock(fb_helper,
				fb_helper->preferred_bpp);
		return err;
	}

	if (!fb_helper->fb || !drm_master_internal_acquire(fb_helper->dev)) {
		fb_helper->delayed_hotplug = true;
		mutex_unlock(&fb_helper->lock);
		return err;
	}

	drm_master_internal_release(fb_helper->dev);

	DRM_DEBUG_KMS("\n");

	drm_client_modeset_probe(&fb_helper->client, fb_helper->fb->width, fb_helper->fb->height);
	drm_setup_crtcs_fb(fb_helper);
	mutex_unlock(&fb_helper->lock);

	drm_fb_helper_set_par(fb_helper->fbdev);

	return 0;
}