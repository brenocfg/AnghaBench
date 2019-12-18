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
struct sg_table {int /*<<< orphan*/  nents; int /*<<< orphan*/  sgl; } ;
struct drm_gem_shmem_object {struct sg_table* sgt; int /*<<< orphan*/  base; } ;
struct drm_gem_object {TYPE_1__* dev; int /*<<< orphan*/  import_attach; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 struct sg_table* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct sg_table*) ; 
 int PTR_ERR (struct sg_table*) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int drm_gem_shmem_get_pages (struct drm_gem_shmem_object*) ; 
 struct sg_table* drm_gem_shmem_get_sg_table (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_gem_shmem_put_pages (struct drm_gem_shmem_object*) ; 
 struct drm_gem_shmem_object* to_drm_gem_shmem_obj (struct drm_gem_object*) ; 

struct sg_table *drm_gem_shmem_get_pages_sgt(struct drm_gem_object *obj)
{
	int ret;
	struct drm_gem_shmem_object *shmem = to_drm_gem_shmem_obj(obj);
	struct sg_table *sgt;

	if (shmem->sgt)
		return shmem->sgt;

	WARN_ON(obj->import_attach);

	ret = drm_gem_shmem_get_pages(shmem);
	if (ret)
		return ERR_PTR(ret);

	sgt = drm_gem_shmem_get_sg_table(&shmem->base);
	if (IS_ERR(sgt)) {
		ret = PTR_ERR(sgt);
		goto err_put_pages;
	}
	/* Map the pages for use by the h/w. */
	dma_map_sg(obj->dev->dev, sgt->sgl, sgt->nents, DMA_BIDIRECTIONAL);

	shmem->sgt = sgt;

	return sgt;

err_put_pages:
	drm_gem_shmem_put_pages(shmem);
	return ERR_PTR(ret);
}