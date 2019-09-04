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
struct sg_table {int /*<<< orphan*/  dir; int /*<<< orphan*/  nents; int /*<<< orphan*/  sgl; struct sg_table* sgt; } ;
struct drm_prime_attachment {int /*<<< orphan*/  dir; int /*<<< orphan*/  nents; int /*<<< orphan*/  sgl; struct drm_prime_attachment* sgt; } ;
struct drm_gem_object {struct drm_device* dev; } ;
struct drm_device {TYPE_1__* driver; } ;
struct dma_buf_attachment {struct sg_table* priv; int /*<<< orphan*/  dev; } ;
struct dma_buf {struct drm_gem_object* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* gem_prime_unpin ) (struct drm_gem_object*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_ATTR_SKIP_CPU_SYNC ; 
 int /*<<< orphan*/  DMA_NONE ; 
 int /*<<< orphan*/  dma_unmap_sg_attrs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct sg_table*) ; 
 int /*<<< orphan*/  sg_free_table (struct sg_table*) ; 
 int /*<<< orphan*/  stub1 (struct drm_gem_object*) ; 

void drm_gem_map_detach(struct dma_buf *dma_buf,
			struct dma_buf_attachment *attach)
{
	struct drm_prime_attachment *prime_attach = attach->priv;
	struct drm_gem_object *obj = dma_buf->priv;
	struct drm_device *dev = obj->dev;

	if (prime_attach) {
		struct sg_table *sgt = prime_attach->sgt;

		if (sgt) {
			if (prime_attach->dir != DMA_NONE)
				dma_unmap_sg_attrs(attach->dev, sgt->sgl,
						   sgt->nents,
						   prime_attach->dir,
						   DMA_ATTR_SKIP_CPU_SYNC);
			sg_free_table(sgt);
		}

		kfree(sgt);
		kfree(prime_attach);
		attach->priv = NULL;
	}

	if (dev->driver->gem_prime_unpin)
		dev->driver->gem_prime_unpin(obj);
}