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
struct exynos_drm_private {int /*<<< orphan*/  fb_helper; } ;
struct drm_device {struct exynos_drm_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  console_lock () ; 
 int /*<<< orphan*/  console_unlock () ; 
 int /*<<< orphan*/  drm_fb_helper_set_suspend (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void exynos_drm_fbdev_resume(struct drm_device *dev)
{
	struct exynos_drm_private *private = dev->dev_private;

	console_lock();
	drm_fb_helper_set_suspend(private->fb_helper, 0);
	console_unlock();
}