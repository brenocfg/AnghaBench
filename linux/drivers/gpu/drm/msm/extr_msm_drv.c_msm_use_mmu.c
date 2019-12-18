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
struct msm_drm_private {scalar_t__ is_a2xx; } ;
struct drm_device {struct msm_drm_private* dev_private; } ;

/* Variables and functions */
 scalar_t__ iommu_present (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_bus_type ; 

bool msm_use_mmu(struct drm_device *dev)
{
	struct msm_drm_private *priv = dev->dev_private;

	/* a2xx comes with its own MMU */
	return priv->is_a2xx || iommu_present(&platform_bus_type);
}