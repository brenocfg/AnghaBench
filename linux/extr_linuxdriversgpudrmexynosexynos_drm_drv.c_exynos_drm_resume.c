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
 struct drm_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  drm_atomic_helper_resume (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_enable (struct drm_device*) ; 
 int /*<<< orphan*/  exynos_drm_fbdev_resume (struct drm_device*) ; 

__attribute__((used)) static void exynos_drm_resume(struct device *dev)
{
	struct drm_device *drm_dev = dev_get_drvdata(dev);
	struct exynos_drm_private *private;

	if (!drm_dev)
		return;

	private = drm_dev->dev_private;
	drm_atomic_helper_resume(drm_dev, private->suspend_state);
	exynos_drm_fbdev_resume(drm_dev);
	drm_kms_helper_poll_enable(drm_dev);
}