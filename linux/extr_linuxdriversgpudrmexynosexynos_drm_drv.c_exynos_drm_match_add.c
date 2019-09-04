#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct exynos_drm_driver_info {int flags; TYPE_1__* driver; } ;
struct device {int dummy; } ;
struct component_match {int dummy; } ;
struct TYPE_5__ {scalar_t__ match; } ;
struct TYPE_4__ {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct exynos_drm_driver_info*) ; 
 int DRM_COMPONENT_DRIVER ; 
 int DRM_FIMC_DEVICE ; 
 int /*<<< orphan*/  ENODEV ; 
 struct component_match* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct device* bus_find_device (TYPE_2__*,struct device*,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  compare_dev ; 
 int /*<<< orphan*/  component_match_add (struct device*,struct component_match**,int /*<<< orphan*/ ,struct device*) ; 
 scalar_t__ exynos_drm_check_fimc_device (struct device*) ; 
 struct exynos_drm_driver_info* exynos_drm_drivers ; 
 TYPE_2__ platform_bus_type ; 
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

		while ((d = bus_find_device(&platform_bus_type, p,
					    &info->driver->driver,
					    (void *)platform_bus_type.match))) {
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