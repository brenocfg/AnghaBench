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
struct vkms_gem_object {int vmap_count; int /*<<< orphan*/  pages_lock; int /*<<< orphan*/ * pages; int /*<<< orphan*/ * vaddr; } ;
struct drm_gem_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_gem_put_pages (struct drm_gem_object*,int /*<<< orphan*/ *,int,int) ; 
 struct vkms_gem_object* drm_gem_to_vkms_gem (struct drm_gem_object*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vunmap (int /*<<< orphan*/ *) ; 

void vkms_gem_vunmap(struct drm_gem_object *obj)
{
	struct vkms_gem_object *vkms_obj = drm_gem_to_vkms_gem(obj);

	mutex_lock(&vkms_obj->pages_lock);
	if (vkms_obj->vmap_count < 1) {
		WARN_ON(vkms_obj->vaddr);
		WARN_ON(vkms_obj->pages);
		mutex_unlock(&vkms_obj->pages_lock);
		return;
	}

	vkms_obj->vmap_count--;

	if (vkms_obj->vmap_count == 0) {
		vunmap(vkms_obj->vaddr);
		vkms_obj->vaddr = NULL;
		drm_gem_put_pages(obj, vkms_obj->pages, false, true);
		vkms_obj->pages = NULL;
	}

	mutex_unlock(&vkms_obj->pages_lock);
}