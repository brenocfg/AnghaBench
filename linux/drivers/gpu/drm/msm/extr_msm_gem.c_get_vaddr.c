#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct msm_gem_object {unsigned int madv; void* vaddr; int /*<<< orphan*/  lock; int /*<<< orphan*/  vmap_count; } ;
struct drm_gem_object {int size; TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 int EBUSY ; 
 int ENOMEM ; 
 void* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct page**) ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 int PAGE_SHIFT ; 
 int PTR_ERR (struct page**) ; 
 int /*<<< orphan*/  VM_MAP ; 
 scalar_t__ WARN_ON (int) ; 
 struct page** get_pages (struct drm_gem_object*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgprot_writecombine (int /*<<< orphan*/ ) ; 
 struct msm_gem_object* to_msm_bo (struct drm_gem_object*) ; 
 void* vmap (struct page**,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *get_vaddr(struct drm_gem_object *obj, unsigned madv)
{
	struct msm_gem_object *msm_obj = to_msm_bo(obj);
	int ret = 0;

	mutex_lock(&msm_obj->lock);

	if (WARN_ON(msm_obj->madv > madv)) {
		DRM_DEV_ERROR(obj->dev->dev, "Invalid madv state: %u vs %u\n",
			msm_obj->madv, madv);
		mutex_unlock(&msm_obj->lock);
		return ERR_PTR(-EBUSY);
	}

	/* increment vmap_count *before* vmap() call, so shrinker can
	 * check vmap_count (is_vunmapable()) outside of msm_obj->lock.
	 * This guarantees that we won't try to msm_gem_vunmap() this
	 * same object from within the vmap() call (while we already
	 * hold msm_obj->lock)
	 */
	msm_obj->vmap_count++;

	if (!msm_obj->vaddr) {
		struct page **pages = get_pages(obj);
		if (IS_ERR(pages)) {
			ret = PTR_ERR(pages);
			goto fail;
		}
		msm_obj->vaddr = vmap(pages, obj->size >> PAGE_SHIFT,
				VM_MAP, pgprot_writecombine(PAGE_KERNEL));
		if (msm_obj->vaddr == NULL) {
			ret = -ENOMEM;
			goto fail;
		}
	}

	mutex_unlock(&msm_obj->lock);
	return msm_obj->vaddr;

fail:
	msm_obj->vmap_count--;
	mutex_unlock(&msm_obj->lock);
	return ERR_PTR(ret);
}