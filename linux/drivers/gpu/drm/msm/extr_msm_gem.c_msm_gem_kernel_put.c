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
struct msm_gem_address_space {int dummy; } ;
struct drm_gem_object {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct drm_gem_object*) ; 
 int /*<<< orphan*/  drm_gem_object_put (struct drm_gem_object*) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 int /*<<< orphan*/  msm_gem_put_vaddr (struct drm_gem_object*) ; 
 int /*<<< orphan*/  msm_gem_unpin_iova (struct drm_gem_object*,struct msm_gem_address_space*) ; 

void msm_gem_kernel_put(struct drm_gem_object *bo,
		struct msm_gem_address_space *aspace, bool locked)
{
	if (IS_ERR_OR_NULL(bo))
		return;

	msm_gem_put_vaddr(bo);
	msm_gem_unpin_iova(bo, aspace);

	if (locked)
		drm_gem_object_put(bo);
	else
		drm_gem_object_put_unlocked(bo);
}