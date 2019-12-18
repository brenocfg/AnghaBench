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
struct drm_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_EXYNOS_IOMMU ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_iommu_detach_device (struct drm_device*,struct device*) ; 

void exynos_drm_unregister_dma(struct drm_device *drm, struct device *dev)
{
	if (IS_ENABLED(CONFIG_EXYNOS_IOMMU))
		drm_iommu_detach_device(drm, dev);
}