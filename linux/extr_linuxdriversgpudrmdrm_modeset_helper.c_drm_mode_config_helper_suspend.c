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
struct TYPE_2__ {struct drm_atomic_state* suspend_state; } ;
struct drm_device {TYPE_1__ mode_config; int /*<<< orphan*/  fb_helper; } ;
struct drm_atomic_state {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct drm_atomic_state*) ; 
 int PTR_ERR (struct drm_atomic_state*) ; 
 struct drm_atomic_state* drm_atomic_helper_suspend (struct drm_device*) ; 
 int /*<<< orphan*/  drm_fb_helper_set_suspend_unlocked (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_disable (struct drm_device*) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_enable (struct drm_device*) ; 

int drm_mode_config_helper_suspend(struct drm_device *dev)
{
	struct drm_atomic_state *state;

	if (!dev)
		return 0;

	drm_kms_helper_poll_disable(dev);
	drm_fb_helper_set_suspend_unlocked(dev->fb_helper, 1);
	state = drm_atomic_helper_suspend(dev);
	if (IS_ERR(state)) {
		drm_fb_helper_set_suspend_unlocked(dev->fb_helper, 0);
		drm_kms_helper_poll_enable(dev);
		return PTR_ERR(state);
	}

	dev->mode_config.suspend_state = state;

	return 0;
}