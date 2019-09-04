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
struct rockchip_drm_private {int /*<<< orphan*/  domain; int /*<<< orphan*/  mm; } ;
struct drm_device {struct rockchip_drm_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_mm_takedown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iommu_domain_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_support_iommu ; 

__attribute__((used)) static void rockchip_iommu_cleanup(struct drm_device *drm_dev)
{
	struct rockchip_drm_private *private = drm_dev->dev_private;

	if (!is_support_iommu)
		return;

	drm_mm_takedown(&private->mm);
	iommu_domain_free(private->domain);
}