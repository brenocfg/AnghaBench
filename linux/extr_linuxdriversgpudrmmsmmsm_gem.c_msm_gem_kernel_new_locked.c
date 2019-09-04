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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct msm_gem_address_space {int dummy; } ;
struct drm_gem_object {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 void* _msm_gem_kernel_new (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct msm_gem_address_space*,struct drm_gem_object**,int /*<<< orphan*/ *,int) ; 

void *msm_gem_kernel_new_locked(struct drm_device *dev, uint32_t size,
		uint32_t flags, struct msm_gem_address_space *aspace,
		struct drm_gem_object **bo, uint64_t *iova)
{
	return _msm_gem_kernel_new(dev, size, flags, aspace, bo, iova, true);
}