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
struct TYPE_5__ {scalar_t__ match; } ;
struct TYPE_4__ {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct exynos_drm_driver_info*) ; 
 int DRM_VIRTUAL_DEVICE ; 
 struct device* bus_find_device (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 struct exynos_drm_driver_info* exynos_drm_drivers ; 
 TYPE_2__ platform_bus_type ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  to_platform_device (struct device*) ; 

__attribute__((used)) static void exynos_drm_unregister_devices(void)
{
	int i;

	for (i = ARRAY_SIZE(exynos_drm_drivers) - 1; i >= 0; --i) {
		struct exynos_drm_driver_info *info = &exynos_drm_drivers[i];
		struct device *dev;

		if (!info->driver || !(info->flags & DRM_VIRTUAL_DEVICE))
			continue;

		while ((dev = bus_find_device(&platform_bus_type, NULL,
					    &info->driver->driver,
					    (void *)platform_bus_type.match))) {
			put_device(dev);
			platform_device_unregister(to_platform_device(dev));
		}
	}
}