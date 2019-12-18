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
struct exynos_drm_gem {unsigned int flags; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*) ; 
 int EINVAL ; 
 scalar_t__ IS_NONCONTIG_BUFFER (unsigned int) ; 
 scalar_t__ is_drm_iommu_supported (struct drm_device*) ; 

__attribute__((used)) static int check_fb_gem_memory_type(struct drm_device *drm_dev,
				    struct exynos_drm_gem *exynos_gem)
{
	unsigned int flags;

	/*
	 * if exynos drm driver supports iommu then framebuffer can use
	 * all the buffer types.
	 */
	if (is_drm_iommu_supported(drm_dev))
		return 0;

	flags = exynos_gem->flags;

	/*
	 * Physically non-contiguous memory type for framebuffer is not
	 * supported without IOMMU.
	 */
	if (IS_NONCONTIG_BUFFER(flags)) {
		DRM_DEV_ERROR(drm_dev->dev,
			      "Non-contiguous GEM memory is not supported.\n");
		return -EINVAL;
	}

	return 0;
}