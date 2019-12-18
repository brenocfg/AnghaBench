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
struct exynos_drm_private {int /*<<< orphan*/  mapping; struct device* dma_dev; } ;
struct drm_device {struct exynos_drm_private* dev_private; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_ARM_DMA_USE_IOMMU ; 
 int /*<<< orphan*/  CONFIG_IOMMU_DMA ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (struct device*,char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int arm_iommu_attach_device (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm_iommu_detach_device (struct device*) ; 
 int /*<<< orphan*/  clear_dma_max_seg_size (struct device*) ; 
 int configure_dma_max_seg_size (struct device*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 scalar_t__ get_dma_ops (struct device*) ; 
 int iommu_attach_device (int /*<<< orphan*/ ,struct device*) ; 
 scalar_t__ to_dma_iommu_mapping (struct device*) ; 

__attribute__((used)) static int drm_iommu_attach_device(struct drm_device *drm_dev,
				struct device *subdrv_dev)
{
	struct exynos_drm_private *priv = drm_dev->dev_private;
	int ret;

	if (get_dma_ops(priv->dma_dev) != get_dma_ops(subdrv_dev)) {
		DRM_DEV_ERROR(subdrv_dev, "Device %s lacks support for IOMMU\n",
			  dev_name(subdrv_dev));
		return -EINVAL;
	}

	ret = configure_dma_max_seg_size(subdrv_dev);
	if (ret)
		return ret;

	if (IS_ENABLED(CONFIG_ARM_DMA_USE_IOMMU)) {
		if (to_dma_iommu_mapping(subdrv_dev))
			arm_iommu_detach_device(subdrv_dev);

		ret = arm_iommu_attach_device(subdrv_dev, priv->mapping);
	} else if (IS_ENABLED(CONFIG_IOMMU_DMA)) {
		ret = iommu_attach_device(priv->mapping, subdrv_dev);
	}

	if (ret)
		clear_dma_max_seg_size(subdrv_dev);

	return 0;
}