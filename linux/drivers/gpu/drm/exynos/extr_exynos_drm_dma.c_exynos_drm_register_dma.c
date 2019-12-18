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
struct exynos_drm_private {void* mapping; struct device* dma_dev; } ;
struct drm_device {struct exynos_drm_private* dev_private; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_ARM_DMA_USE_IOMMU ; 
 int /*<<< orphan*/  CONFIG_EXYNOS_IOMMU ; 
 int /*<<< orphan*/  CONFIG_IOMMU_DMA ; 
 int /*<<< orphan*/  DRM_INFO (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXYNOS_DEV_ADDR_SIZE ; 
 int /*<<< orphan*/  EXYNOS_DEV_ADDR_START ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 void* arm_iommu_create_mapping (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int drm_iommu_attach_device (struct drm_device*,struct device*) ; 
 void* iommu_get_domain_for_dev (struct device*) ; 
 int /*<<< orphan*/  platform_bus_type ; 

int exynos_drm_register_dma(struct drm_device *drm, struct device *dev)
{
	struct exynos_drm_private *priv = drm->dev_private;

	if (!priv->dma_dev) {
		priv->dma_dev = dev;
		DRM_INFO("Exynos DRM: using %s device for DMA mapping operations\n",
			 dev_name(dev));
	}

	if (!IS_ENABLED(CONFIG_EXYNOS_IOMMU))
		return 0;

	if (!priv->mapping) {
		void *mapping;

		if (IS_ENABLED(CONFIG_ARM_DMA_USE_IOMMU))
			mapping = arm_iommu_create_mapping(&platform_bus_type,
				EXYNOS_DEV_ADDR_START, EXYNOS_DEV_ADDR_SIZE);
		else if (IS_ENABLED(CONFIG_IOMMU_DMA))
			mapping = iommu_get_domain_for_dev(priv->dma_dev);

		if (IS_ERR(mapping))
			return PTR_ERR(mapping);
		priv->mapping = mapping;
	}

	return drm_iommu_attach_device(drm, dev);
}