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
struct drm_gem_object {int dummy; } ;
struct xen_gem_object {struct drm_gem_object base; int /*<<< orphan*/  pages; int /*<<< orphan*/  num_pages; struct sg_table* sgt_imported; } ;
struct xen_drm_front_drm_info {int /*<<< orphan*/  front_info; } ;
struct sg_table {int /*<<< orphan*/  nents; } ;
struct drm_device {struct xen_drm_front_drm_info* dev_private; } ;
struct dma_buf_attachment {TYPE_1__* dmabuf; } ;
struct TYPE_2__ {size_t size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,size_t,int /*<<< orphan*/ ) ; 
 struct drm_gem_object* ERR_CAST (struct xen_gem_object*) ; 
 struct drm_gem_object* ERR_PTR (int) ; 
 scalar_t__ IS_ERR_OR_NULL (struct xen_gem_object*) ; 
 int drm_prime_sg_to_page_addr_arrays (struct sg_table*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int gem_alloc_pages_array (struct xen_gem_object*,size_t) ; 
 struct xen_gem_object* gem_create_obj (struct drm_device*,size_t) ; 
 int xen_drm_front_dbuf_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xen_drm_front_dbuf_to_cookie (struct drm_gem_object*) ; 

struct drm_gem_object *
xen_drm_front_gem_import_sg_table(struct drm_device *dev,
				  struct dma_buf_attachment *attach,
				  struct sg_table *sgt)
{
	struct xen_drm_front_drm_info *drm_info = dev->dev_private;
	struct xen_gem_object *xen_obj;
	size_t size;
	int ret;

	size = attach->dmabuf->size;
	xen_obj = gem_create_obj(dev, size);
	if (IS_ERR_OR_NULL(xen_obj))
		return ERR_CAST(xen_obj);

	ret = gem_alloc_pages_array(xen_obj, size);
	if (ret < 0)
		return ERR_PTR(ret);

	xen_obj->sgt_imported = sgt;

	ret = drm_prime_sg_to_page_addr_arrays(sgt, xen_obj->pages,
					       NULL, xen_obj->num_pages);
	if (ret < 0)
		return ERR_PTR(ret);

	ret = xen_drm_front_dbuf_create(drm_info->front_info,
					xen_drm_front_dbuf_to_cookie(&xen_obj->base),
					0, 0, 0, size, xen_obj->pages);
	if (ret < 0)
		return ERR_PTR(ret);

	DRM_DEBUG("Imported buffer of size %zu with nents %u\n",
		  size, sgt->nents);

	return &xen_obj->base;
}