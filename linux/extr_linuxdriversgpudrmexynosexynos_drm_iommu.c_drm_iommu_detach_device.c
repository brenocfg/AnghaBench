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
struct exynos_drm_private {int dummy; } ;
struct drm_device {struct exynos_drm_private* dev_private; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __exynos_iommu_detach (struct exynos_drm_private*,struct device*) ; 
 int /*<<< orphan*/  clear_dma_max_seg_size (struct device*) ; 

void drm_iommu_detach_device(struct drm_device *drm_dev,
				struct device *subdrv_dev)
{
	struct exynos_drm_private *priv = drm_dev->dev_private;

	__exynos_iommu_detach(priv, subdrv_dev);
	clear_dma_max_seg_size(subdrv_dev);
}