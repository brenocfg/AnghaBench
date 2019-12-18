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
struct msm_gem_vma {int dummy; } ;
struct msm_gem_object {int /*<<< orphan*/  lock; } ;
struct msm_gem_address_space {int dummy; } ;
struct drm_gem_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct msm_gem_vma* lookup_vma (struct drm_gem_object*,struct msm_gem_address_space*) ; 
 int /*<<< orphan*/  msm_gem_unmap_vma (struct msm_gem_address_space*,struct msm_gem_vma*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct msm_gem_object* to_msm_bo (struct drm_gem_object*) ; 

void msm_gem_unpin_iova(struct drm_gem_object *obj,
		struct msm_gem_address_space *aspace)
{
	struct msm_gem_object *msm_obj = to_msm_bo(obj);
	struct msm_gem_vma *vma;

	mutex_lock(&msm_obj->lock);
	vma = lookup_vma(obj, aspace);

	if (!WARN_ON(!vma))
		msm_gem_unmap_vma(aspace, vma);

	mutex_unlock(&msm_obj->lock);
}