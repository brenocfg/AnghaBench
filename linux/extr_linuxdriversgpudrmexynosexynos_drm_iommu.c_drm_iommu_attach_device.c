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
struct exynos_drm_private {struct device* dma_dev; } ;
struct drm_device {struct exynos_drm_private* dev_private; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int __exynos_iommu_attach (struct exynos_drm_private*,struct device*) ; 
 int /*<<< orphan*/  clear_dma_max_seg_size (struct device*) ; 
 int configure_dma_max_seg_size (struct device*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 scalar_t__ get_dma_ops (struct device*) ; 

int drm_iommu_attach_device(struct drm_device *drm_dev,
				struct device *subdrv_dev)
{
	struct exynos_drm_private *priv = drm_dev->dev_private;
	int ret;

	if (get_dma_ops(priv->dma_dev) != get_dma_ops(subdrv_dev)) {
		DRM_ERROR("Device %s lacks support for IOMMU\n",
			  dev_name(subdrv_dev));
		return -EINVAL;
	}

	ret = configure_dma_max_seg_size(subdrv_dev);
	if (ret)
		return ret;

	ret = __exynos_iommu_attach(priv, subdrv_dev);
	if (ret)
		clear_dma_max_seg_size(subdrv_dev);

	return 0;
}