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
struct exynos_drm_driver_info {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct exynos_drm_driver_info*) ; 
 struct exynos_drm_driver_info* exynos_drm_drivers ; 
 int /*<<< orphan*/  exynos_drm_unregister_drivers () ; 
 int platform_driver_register (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int exynos_drm_register_drivers(void)
{
	int i, ret;

	for (i = 0; i < ARRAY_SIZE(exynos_drm_drivers); ++i) {
		struct exynos_drm_driver_info *info = &exynos_drm_drivers[i];

		if (!info->driver)
			continue;

		ret = platform_driver_register(info->driver);
		if (ret)
			goto fail;
	}
	return 0;
fail:
	exynos_drm_unregister_drivers();
	return ret;
}