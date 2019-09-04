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
struct drm_device {int dummy; } ;
struct cirrus_bo {struct drm_gem_object gem; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int cirrus_bo_create (struct drm_device*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cirrus_bo**) ; 
 scalar_t__ roundup (scalar_t__,int /*<<< orphan*/ ) ; 

int cirrus_gem_create(struct drm_device *dev,
		   u32 size, bool iskernel,
		   struct drm_gem_object **obj)
{
	struct cirrus_bo *cirrusbo;
	int ret;

	*obj = NULL;

	size = roundup(size, PAGE_SIZE);
	if (size == 0)
		return -EINVAL;

	ret = cirrus_bo_create(dev, size, 0, 0, &cirrusbo);
	if (ret) {
		if (ret != -ERESTARTSYS)
			DRM_ERROR("failed to allocate GEM object\n");
		return ret;
	}
	*obj = &cirrusbo->gem;
	return 0;
}