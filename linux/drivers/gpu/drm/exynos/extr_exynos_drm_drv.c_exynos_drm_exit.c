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
 int /*<<< orphan*/  exynos_drm_unregister_devices () ; 
 int /*<<< orphan*/  exynos_drm_unregister_drivers () ; 

__attribute__((used)) static void exynos_drm_exit(void)
{
	exynos_drm_unregister_drivers();
	exynos_drm_unregister_devices();
}