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

/* Variables and functions */
 int /*<<< orphan*/  EXYNOS_DEV_ADDR_SIZE ; 
 int /*<<< orphan*/  EXYNOS_DEV_ADDR_START ; 
 int __exynos_iommu_create_mapping (struct exynos_drm_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int drm_create_iommu_mapping(struct drm_device *drm_dev)
{
	struct exynos_drm_private *priv = drm_dev->dev_private;

	return __exynos_iommu_create_mapping(priv, EXYNOS_DEV_ADDR_START,
					     EXYNOS_DEV_ADDR_SIZE);
}