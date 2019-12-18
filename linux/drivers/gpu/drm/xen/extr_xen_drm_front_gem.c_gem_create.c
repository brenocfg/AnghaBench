#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xen_gem_object {int be_alloc; struct xen_gem_object* pages; int /*<<< orphan*/  base; int /*<<< orphan*/  num_pages; } ;
struct xen_drm_front_drm_info {TYPE_2__* front_info; } ;
struct drm_device {struct xen_drm_front_drm_info* dev_private; } ;
struct TYPE_3__ {scalar_t__ be_alloc; } ;
struct TYPE_4__ {TYPE_1__ cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,size_t,...) ; 
 struct xen_gem_object* ERR_PTR (int) ; 
 scalar_t__ IS_ERR_OR_NULL (struct xen_gem_object*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PTR_ERR (struct xen_gem_object*) ; 
 int alloc_xenballooned_pages (int /*<<< orphan*/ ,struct xen_gem_object*) ; 
 struct xen_gem_object* drm_gem_get_pages (int /*<<< orphan*/ *) ; 
 int gem_alloc_pages_array (struct xen_gem_object*,size_t) ; 
 struct xen_gem_object* gem_create_obj (struct drm_device*,size_t) ; 
 int /*<<< orphan*/  gem_free_pages_array (struct xen_gem_object*) ; 
 size_t round_up (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct xen_gem_object *gem_create(struct drm_device *dev, size_t size)
{
	struct xen_drm_front_drm_info *drm_info = dev->dev_private;
	struct xen_gem_object *xen_obj;
	int ret;

	size = round_up(size, PAGE_SIZE);
	xen_obj = gem_create_obj(dev, size);
	if (IS_ERR_OR_NULL(xen_obj))
		return xen_obj;

	if (drm_info->front_info->cfg.be_alloc) {
		/*
		 * backend will allocate space for this buffer, so
		 * only allocate array of pointers to pages
		 */
		ret = gem_alloc_pages_array(xen_obj, size);
		if (ret < 0)
			goto fail;

		/*
		 * allocate ballooned pages which will be used to map
		 * grant references provided by the backend
		 */
		ret = alloc_xenballooned_pages(xen_obj->num_pages,
					       xen_obj->pages);
		if (ret < 0) {
			DRM_ERROR("Cannot allocate %zu ballooned pages: %d\n",
				  xen_obj->num_pages, ret);
			gem_free_pages_array(xen_obj);
			goto fail;
		}

		xen_obj->be_alloc = true;
		return xen_obj;
	}
	/*
	 * need to allocate backing pages now, so we can share those
	 * with the backend
	 */
	xen_obj->num_pages = DIV_ROUND_UP(size, PAGE_SIZE);
	xen_obj->pages = drm_gem_get_pages(&xen_obj->base);
	if (IS_ERR_OR_NULL(xen_obj->pages)) {
		ret = PTR_ERR(xen_obj->pages);
		xen_obj->pages = NULL;
		goto fail;
	}

	return xen_obj;

fail:
	DRM_ERROR("Failed to allocate buffer with size %zu\n", size);
	return ERR_PTR(ret);
}