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
struct drm_device {int /*<<< orphan*/  fb_helper; } ;

/* Variables and functions */
 int /*<<< orphan*/  ast_post_gpu (struct drm_device*) ; 
 int /*<<< orphan*/  drm_fb_helper_set_suspend_unlocked (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  drm_helper_resume_force_mode (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_reset (struct drm_device*) ; 

__attribute__((used)) static int ast_drm_thaw(struct drm_device *dev)
{
	ast_post_gpu(dev);

	drm_mode_config_reset(dev);
	drm_helper_resume_force_mode(dev);
	drm_fb_helper_set_suspend_unlocked(dev->fb_helper, false);

	return 0;
}