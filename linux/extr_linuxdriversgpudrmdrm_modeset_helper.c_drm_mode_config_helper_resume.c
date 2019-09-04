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
struct TYPE_2__ {int /*<<< orphan*/ * suspend_state; } ;
struct drm_device {int /*<<< orphan*/  fb_helper; TYPE_1__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int drm_atomic_helper_resume (struct drm_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_fb_helper_set_suspend_unlocked (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_enable (struct drm_device*) ; 

int drm_mode_config_helper_resume(struct drm_device *dev)
{
	int ret;

	if (!dev)
		return 0;

	if (WARN_ON(!dev->mode_config.suspend_state))
		return -EINVAL;

	ret = drm_atomic_helper_resume(dev, dev->mode_config.suspend_state);
	if (ret)
		DRM_ERROR("Failed to resume (%d)\n", ret);
	dev->mode_config.suspend_state = NULL;

	drm_fb_helper_set_suspend_unlocked(dev->fb_helper, 0);
	drm_kms_helper_poll_enable(dev);

	return ret;
}