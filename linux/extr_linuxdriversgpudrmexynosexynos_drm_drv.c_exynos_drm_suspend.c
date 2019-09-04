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
struct exynos_drm_private {int /*<<< orphan*/  suspend_state; } ;
struct drm_device {struct exynos_drm_private* dev_private; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 struct drm_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  drm_atomic_helper_suspend (struct drm_device*) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_disable (struct drm_device*) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_enable (struct drm_device*) ; 
 int /*<<< orphan*/  exynos_drm_fbdev_resume (struct drm_device*) ; 
 int /*<<< orphan*/  exynos_drm_fbdev_suspend (struct drm_device*) ; 

__attribute__((used)) static int exynos_drm_suspend(struct device *dev)
{
	struct drm_device *drm_dev = dev_get_drvdata(dev);
	struct exynos_drm_private *private;

	if (!drm_dev)
		return 0;

	private = drm_dev->dev_private;

	drm_kms_helper_poll_disable(drm_dev);
	exynos_drm_fbdev_suspend(drm_dev);
	private->suspend_state = drm_atomic_helper_suspend(drm_dev);
	if (IS_ERR(private->suspend_state)) {
		exynos_drm_fbdev_resume(drm_dev);
		drm_kms_helper_poll_enable(drm_dev);
		return PTR_ERR(private->suspend_state);
	}

	return 0;
}