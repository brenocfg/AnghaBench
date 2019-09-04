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
struct exynos_drm_ipp {int dummy; } ;
struct rot_context {int /*<<< orphan*/  dev; int /*<<< orphan*/  drm_dev; struct exynos_drm_ipp ipp; } ;
struct drm_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct rot_context* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  drm_iommu_detach_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos_drm_ipp_unregister (struct drm_device*,struct exynos_drm_ipp*) ; 

__attribute__((used)) static void rotator_unbind(struct device *dev, struct device *master,
			void *data)
{
	struct rot_context *rot = dev_get_drvdata(dev);
	struct drm_device *drm_dev = data;
	struct exynos_drm_ipp *ipp = &rot->ipp;

	exynos_drm_ipp_unregister(drm_dev, ipp);
	drm_iommu_detach_device(rot->drm_dev, rot->dev);
}