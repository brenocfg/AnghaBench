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
struct drm_fb_helper {int delayed_hotplug; int /*<<< orphan*/  lock; int /*<<< orphan*/  client; int /*<<< orphan*/  deferred_setup; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int drm_client_modeset_commit_force (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_fb_helper_hotplug_event (struct drm_fb_helper*) ; 
 int /*<<< orphan*/  drm_fbdev_emulation ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int drm_fb_helper_restore_fbdev_mode_unlocked(struct drm_fb_helper *fb_helper)
{
	bool do_delayed;
	int ret;

	if (!drm_fbdev_emulation || !fb_helper)
		return -ENODEV;

	if (READ_ONCE(fb_helper->deferred_setup))
		return 0;

	mutex_lock(&fb_helper->lock);
	/*
	 * TODO:
	 * We should bail out here if there is a master by dropping _force.
	 * Currently these igt tests fail if we do that:
	 * - kms_fbcon_fbt@psr
	 * - kms_fbcon_fbt@psr-suspend
	 *
	 * So first these tests need to be fixed so they drop master or don't
	 * have an fd open.
	 */
	ret = drm_client_modeset_commit_force(&fb_helper->client);

	do_delayed = fb_helper->delayed_hotplug;
	if (do_delayed)
		fb_helper->delayed_hotplug = false;
	mutex_unlock(&fb_helper->lock);

	if (do_delayed)
		drm_fb_helper_hotplug_event(fb_helper);

	return ret;
}