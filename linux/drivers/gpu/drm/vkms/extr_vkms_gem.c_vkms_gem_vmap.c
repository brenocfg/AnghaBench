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
struct vkms_gem_object {int /*<<< orphan*/  pages_lock; int /*<<< orphan*/ * pages; int /*<<< orphan*/  vmap_count; scalar_t__ vaddr; } ;
struct page {int dummy; } ;
struct drm_gem_object {unsigned int size; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct page**) ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 unsigned int PAGE_SHIFT ; 
 int PTR_ERR (struct page**) ; 
 int /*<<< orphan*/  VM_MAP ; 
 struct page** _get_pages (struct vkms_gem_object*) ; 
 int /*<<< orphan*/  drm_gem_put_pages (struct drm_gem_object*,int /*<<< orphan*/ *,int,int) ; 
 struct vkms_gem_object* drm_gem_to_vkms_gem (struct drm_gem_object*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ vmap (struct page**,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int vkms_gem_vmap(struct drm_gem_object *obj)
{
	struct vkms_gem_object *vkms_obj = drm_gem_to_vkms_gem(obj);
	int ret = 0;

	mutex_lock(&vkms_obj->pages_lock);

	if (!vkms_obj->vaddr) {
		unsigned int n_pages = obj->size >> PAGE_SHIFT;
		struct page **pages = _get_pages(vkms_obj);

		if (IS_ERR(pages)) {
			ret = PTR_ERR(pages);
			goto out;
		}

		vkms_obj->vaddr = vmap(pages, n_pages, VM_MAP, PAGE_KERNEL);
		if (!vkms_obj->vaddr)
			goto err_vmap;
	}

	vkms_obj->vmap_count++;
	goto out;

err_vmap:
	ret = -ENOMEM;
	drm_gem_put_pages(obj, vkms_obj->pages, false, true);
	vkms_obj->pages = NULL;
out:
	mutex_unlock(&vkms_obj->pages_lock);
	return ret;
}