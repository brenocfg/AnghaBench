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
struct exynos_drm_private {int /*<<< orphan*/ * dma_dev; int /*<<< orphan*/ * mapping; } ;
struct drm_device {struct exynos_drm_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_EXYNOS_IOMMU ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm_iommu_release_mapping (int /*<<< orphan*/ *) ; 

void exynos_drm_cleanup_dma(struct drm_device *drm)
{
	struct exynos_drm_private *priv = drm->dev_private;

	if (!IS_ENABLED(CONFIG_EXYNOS_IOMMU))
		return;

	arm_iommu_release_mapping(priv->mapping);
	priv->mapping = NULL;
	priv->dma_dev = NULL;
}