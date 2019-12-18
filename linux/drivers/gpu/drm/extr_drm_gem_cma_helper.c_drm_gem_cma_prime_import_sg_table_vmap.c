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
struct sg_table {int dummy; } ;
struct drm_gem_object {int dummy; } ;
struct drm_gem_cma_object {void* vaddr; } ;
struct drm_device {int dummy; } ;
struct dma_buf_attachment {int /*<<< orphan*/  dmabuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct drm_gem_object* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct drm_gem_object*) ; 
 void* dma_buf_vmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_buf_vunmap (int /*<<< orphan*/ ,void*) ; 
 struct drm_gem_object* drm_gem_cma_prime_import_sg_table (struct drm_device*,struct dma_buf_attachment*,struct sg_table*) ; 
 struct drm_gem_cma_object* to_drm_gem_cma_obj (struct drm_gem_object*) ; 

struct drm_gem_object *
drm_gem_cma_prime_import_sg_table_vmap(struct drm_device *dev,
				       struct dma_buf_attachment *attach,
				       struct sg_table *sgt)
{
	struct drm_gem_cma_object *cma_obj;
	struct drm_gem_object *obj;
	void *vaddr;

	vaddr = dma_buf_vmap(attach->dmabuf);
	if (!vaddr) {
		DRM_ERROR("Failed to vmap PRIME buffer\n");
		return ERR_PTR(-ENOMEM);
	}

	obj = drm_gem_cma_prime_import_sg_table(dev, attach, sgt);
	if (IS_ERR(obj)) {
		dma_buf_vunmap(attach->dmabuf, vaddr);
		return obj;
	}

	cma_obj = to_drm_gem_cma_obj(obj);
	cma_obj->vaddr = vaddr;

	return obj;
}