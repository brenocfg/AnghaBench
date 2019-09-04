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
struct drm_gem_object {struct dma_buf_attachment* import_attach; } ;
struct v3d_bo {struct sg_table* sgt; int /*<<< orphan*/  resv; struct drm_gem_object base; } ;
struct sg_table {int dummy; } ;
struct drm_device {int dummy; } ;
struct dma_buf_attachment {TYPE_1__* dmabuf; } ;
struct TYPE_2__ {int /*<<< orphan*/  resv; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 struct drm_gem_object* ERR_CAST (struct v3d_bo*) ; 
 scalar_t__ IS_ERR (struct v3d_bo*) ; 
 struct v3d_bo* v3d_bo_create_struct (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v3d_bo_get_pages (struct v3d_bo*) ; 
 int /*<<< orphan*/  v3d_mmu_insert_ptes (struct v3d_bo*) ; 

struct drm_gem_object *
v3d_prime_import_sg_table(struct drm_device *dev,
			  struct dma_buf_attachment *attach,
			  struct sg_table *sgt)
{
	struct drm_gem_object *obj;
	struct v3d_bo *bo;

	bo = v3d_bo_create_struct(dev, attach->dmabuf->size);
	if (IS_ERR(bo))
		return ERR_CAST(bo);
	obj = &bo->base;

	bo->resv = attach->dmabuf->resv;

	bo->sgt = sgt;
	obj->import_attach = attach;
	v3d_bo_get_pages(bo);

	v3d_mmu_insert_ptes(bo);

	return obj;
}