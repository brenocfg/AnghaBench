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
typedef  scalar_t__ u32 ;
struct drm_gem_object {int dummy; } ;
struct hibmc_bo {struct drm_gem_object gem; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int EINVAL ; 
 int ERESTARTSYS ; 
 scalar_t__ PAGE_ALIGN (scalar_t__) ; 
 int hibmc_bo_create (struct drm_device*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hibmc_bo**) ; 

int hibmc_gem_create(struct drm_device *dev, u32 size, bool iskernel,
		     struct drm_gem_object **obj)
{
	struct hibmc_bo *hibmcbo;
	int ret;

	*obj = NULL;

	size = PAGE_ALIGN(size);
	if (size == 0) {
		DRM_ERROR("error: zero size\n");
		return -EINVAL;
	}

	ret = hibmc_bo_create(dev, size, 0, 0, &hibmcbo);
	if (ret) {
		if (ret != -ERESTARTSYS)
			DRM_ERROR("failed to allocate GEM object: %d\n", ret);
		return ret;
	}
	*obj = &hibmcbo->gem;
	return 0;
}