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
struct drm_gem_object {TYPE_1__* import_attach; struct drm_device* dev; } ;
struct msm_gem_object {int /*<<< orphan*/  lock; int /*<<< orphan*/  sgt; scalar_t__ pages; scalar_t__ vaddr; int /*<<< orphan*/  mm_list; struct drm_gem_object base; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; } ;
struct TYPE_2__ {int /*<<< orphan*/  dmabuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dma_buf_vunmap (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  drm_gem_object_release (struct drm_gem_object*) ; 
 int /*<<< orphan*/  drm_prime_gem_destroy (struct drm_gem_object*,int /*<<< orphan*/ ) ; 
 int is_active (struct msm_gem_object*) ; 
 int /*<<< orphan*/  kfree (struct msm_gem_object*) ; 
 int /*<<< orphan*/  kvfree (scalar_t__) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msm_gem_vunmap_locked (struct drm_gem_object*) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_iova (struct drm_gem_object*) ; 
 int /*<<< orphan*/  put_pages (struct drm_gem_object*) ; 

__attribute__((used)) static void free_object(struct msm_gem_object *msm_obj)
{
	struct drm_gem_object *obj = &msm_obj->base;
	struct drm_device *dev = obj->dev;

	WARN_ON(!mutex_is_locked(&dev->struct_mutex));

	/* object should not be on active list: */
	WARN_ON(is_active(msm_obj));

	list_del(&msm_obj->mm_list);

	mutex_lock(&msm_obj->lock);

	put_iova(obj);

	if (obj->import_attach) {
		if (msm_obj->vaddr)
			dma_buf_vunmap(obj->import_attach->dmabuf, msm_obj->vaddr);

		/* Don't drop the pages for imported dmabuf, as they are not
		 * ours, just free the array we allocated:
		 */
		if (msm_obj->pages)
			kvfree(msm_obj->pages);

		drm_prime_gem_destroy(obj, msm_obj->sgt);
	} else {
		msm_gem_vunmap_locked(obj);
		put_pages(obj);
	}

	drm_gem_object_release(obj);

	mutex_unlock(&msm_obj->lock);
	kfree(msm_obj);
}