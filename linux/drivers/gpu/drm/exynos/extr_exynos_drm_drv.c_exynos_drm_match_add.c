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
struct exynos_drm_driver_info {int flags; TYPE_1__* driver; } ;
struct device {int dummy; } ;
struct component_match {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct exynos_drm_driver_info*) ; 
 int DRM_COMPONENT_DRIVER ; 
 int DRM_FIMC_DEVICE ; 
 int /*<<< orphan*/  ENODEV ; 
 struct component_match* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compare_dev ; 
 int /*<<< orphan*/  component_match_add (struct device*,struct component_match**,int /*<<< orphan*/ ,struct device*) ; 
 scalar_t__ exynos_drm_check_fimc_device (struct device*) ; 
 struct exynos_drm_driver_info* exynos_drm_drivers ; 
 struct device* platform_find_device_by_driver (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 

__attribute__((used)) static struct component_match *exynos_drm_match_add(struct device *dev)
{
	struct component_match *match = NULL;
	int i;

	for (i = 0; i < ARRAY_SIZE(exynos_drm_drivers); ++i) {
		struct exynos_drm_driver_info *info = &exynos_drm_drivers[i];
		struct device *p = NULL, *d;

		if (!info->driver || !(info->flags & DRM_COMPONENT_DRIVER))
			continue;

		while ((d = platform_find_device_by_driver(p, &info->driver->driver))) {
			put_device(p);

			if (!(info->flags & DRM_FIMC_DEVICE) ||
			    exynos_drm_check_fimc_device(d) == 0)
				component_match_add(dev, &match,
						    compare_dev, d);
			p = d;
		}
		put_device(p);
	}

	return match ?: ERR_PTR(-ENODEV);
}