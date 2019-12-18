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
struct page {int dummy; } ;
struct msm_gem_vma {int dummy; } ;
struct msm_gem_object {int flags; scalar_t__ madv; int /*<<< orphan*/  sgt; int /*<<< orphan*/  lock; } ;
struct msm_gem_address_space {int dummy; } ;
struct drm_gem_object {int size; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int IOMMU_READ ; 
 int IOMMU_WRITE ; 
 scalar_t__ IS_ERR (struct page**) ; 
 int MSM_BO_GPU_READONLY ; 
 scalar_t__ MSM_MADV_WILLNEED ; 
 int PAGE_SHIFT ; 
 int PTR_ERR (struct page**) ; 
 scalar_t__ WARN_ON (int) ; 
 struct page** get_pages (struct drm_gem_object*) ; 
 struct msm_gem_vma* lookup_vma (struct drm_gem_object*,struct msm_gem_address_space*) ; 
 int msm_gem_map_vma (struct msm_gem_address_space*,struct msm_gem_vma*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 struct msm_gem_object* to_msm_bo (struct drm_gem_object*) ; 

__attribute__((used)) static int msm_gem_pin_iova(struct drm_gem_object *obj,
		struct msm_gem_address_space *aspace)
{
	struct msm_gem_object *msm_obj = to_msm_bo(obj);
	struct msm_gem_vma *vma;
	struct page **pages;
	int prot = IOMMU_READ;

	if (!(msm_obj->flags & MSM_BO_GPU_READONLY))
		prot |= IOMMU_WRITE;

	WARN_ON(!mutex_is_locked(&msm_obj->lock));

	if (WARN_ON(msm_obj->madv != MSM_MADV_WILLNEED))
		return -EBUSY;

	vma = lookup_vma(obj, aspace);
	if (WARN_ON(!vma))
		return -EINVAL;

	pages = get_pages(obj);
	if (IS_ERR(pages))
		return PTR_ERR(pages);

	return msm_gem_map_vma(aspace, vma, prot,
			msm_obj->sgt, obj->size >> PAGE_SHIFT);
}