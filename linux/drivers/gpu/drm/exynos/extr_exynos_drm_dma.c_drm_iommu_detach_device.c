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
struct exynos_drm_private {int /*<<< orphan*/  mapping; } ;
struct drm_device {struct exynos_drm_private* dev_private; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_ARM_DMA_USE_IOMMU ; 
 int /*<<< orphan*/  CONFIG_IOMMU_DMA ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm_iommu_detach_device (struct device*) ; 
 int /*<<< orphan*/  clear_dma_max_seg_size (struct device*) ; 
 int /*<<< orphan*/  iommu_detach_device (int /*<<< orphan*/ ,struct device*) ; 

__attribute__((used)) static void drm_iommu_detach_device(struct drm_device *drm_dev,
				struct device *subdrv_dev)
{
	struct exynos_drm_private *priv = drm_dev->dev_private;

	if (IS_ENABLED(CONFIG_ARM_DMA_USE_IOMMU))
		arm_iommu_detach_device(subdrv_dev);
	else if (IS_ENABLED(CONFIG_IOMMU_DMA))
		iommu_detach_device(priv->mapping, subdrv_dev);

	clear_dma_max_seg_size(subdrv_dev);
}