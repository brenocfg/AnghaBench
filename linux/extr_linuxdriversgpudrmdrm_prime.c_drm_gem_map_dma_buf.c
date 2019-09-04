#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sg_table {int /*<<< orphan*/  nents; int /*<<< orphan*/  sgl; } ;
struct drm_prime_attachment {int dir; struct sg_table* sgt; } ;
struct drm_gem_object {TYPE_3__* dev; } ;
struct dma_buf_attachment {int /*<<< orphan*/  dev; TYPE_1__* dmabuf; struct drm_prime_attachment* priv; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_6__ {TYPE_2__* driver; } ;
struct TYPE_5__ {struct sg_table* (* gem_prime_get_sg_table ) (struct drm_gem_object*) ;} ;
struct TYPE_4__ {struct drm_gem_object* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_ATTR_SKIP_CPU_SYNC ; 
 int DMA_NONE ; 
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct sg_table* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (struct sg_table*) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dma_map_sg_attrs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct sg_table*) ; 
 int /*<<< orphan*/  sg_free_table (struct sg_table*) ; 
 struct sg_table* stub1 (struct drm_gem_object*) ; 

struct sg_table *drm_gem_map_dma_buf(struct dma_buf_attachment *attach,
				     enum dma_data_direction dir)
{
	struct drm_prime_attachment *prime_attach = attach->priv;
	struct drm_gem_object *obj = attach->dmabuf->priv;
	struct sg_table *sgt;

	if (WARN_ON(dir == DMA_NONE || !prime_attach))
		return ERR_PTR(-EINVAL);

	/* return the cached mapping when possible */
	if (prime_attach->dir == dir)
		return prime_attach->sgt;

	/*
	 * two mappings with different directions for the same attachment are
	 * not allowed
	 */
	if (WARN_ON(prime_attach->dir != DMA_NONE))
		return ERR_PTR(-EBUSY);

	sgt = obj->dev->driver->gem_prime_get_sg_table(obj);

	if (!IS_ERR(sgt)) {
		if (!dma_map_sg_attrs(attach->dev, sgt->sgl, sgt->nents, dir,
				      DMA_ATTR_SKIP_CPU_SYNC)) {
			sg_free_table(sgt);
			kfree(sgt);
			sgt = ERR_PTR(-ENOMEM);
		} else {
			prime_attach->sgt = sgt;
			prime_attach->dir = dir;
		}
	}

	return sgt;
}