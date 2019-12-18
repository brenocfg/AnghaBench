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

/* Variables and functions */
 int exynos_drm_register_devices () ; 
 int exynos_drm_register_drivers () ; 
 int /*<<< orphan*/  exynos_drm_unregister_devices () ; 

__attribute__((used)) static int exynos_drm_init(void)
{
	int ret;

	ret = exynos_drm_register_devices();
	if (ret)
		return ret;

	ret = exynos_drm_register_drivers();
	if (ret)
		goto err_unregister_pdevs;

	return 0;

err_unregister_pdevs:
	exynos_drm_unregister_devices();

	return ret;
}