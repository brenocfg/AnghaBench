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
typedef  int u32 ;
struct tiler_block {int dummy; } ;
struct omap_gem_object {scalar_t__ dma_addr_cnt; int flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  dma_addr; struct tiler_block* block; int /*<<< orphan*/  roll; int /*<<< orphan*/  pages; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct omap_drm_private {scalar_t__ has_dmm; } ;
struct drm_gem_object {int size; TYPE_1__* dev; } ;
typedef  enum tiler_fmt { ____Placeholder_tiler_fmt } tiler_fmt ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; struct omap_drm_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (struct tiler_block*) ; 
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct tiler_block*) ; 
 int OMAP_BO_TILED ; 
 int PAGE_SHIFT ; 
 int PTR_ERR (struct tiler_block*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int gem2fmt (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int omap_gem_attach_pages (struct drm_gem_object*) ; 
 scalar_t__ omap_gem_is_contiguous (struct omap_gem_object*) ; 
 int tiler_pin (struct tiler_block*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tiler_release (struct tiler_block*) ; 
 struct tiler_block* tiler_reserve_1d (int) ; 
 struct tiler_block* tiler_reserve_2d (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tiler_ssptr (struct tiler_block*) ; 
 struct omap_gem_object* to_omap_bo (struct drm_gem_object*) ; 

int omap_gem_pin(struct drm_gem_object *obj, dma_addr_t *dma_addr)
{
	struct omap_drm_private *priv = obj->dev->dev_private;
	struct omap_gem_object *omap_obj = to_omap_bo(obj);
	int ret = 0;

	mutex_lock(&omap_obj->lock);

	if (!omap_gem_is_contiguous(omap_obj) && priv->has_dmm) {
		if (omap_obj->dma_addr_cnt == 0) {
			u32 npages = obj->size >> PAGE_SHIFT;
			enum tiler_fmt fmt = gem2fmt(omap_obj->flags);
			struct tiler_block *block;

			BUG_ON(omap_obj->block);

			ret = omap_gem_attach_pages(obj);
			if (ret)
				goto fail;

			if (omap_obj->flags & OMAP_BO_TILED) {
				block = tiler_reserve_2d(fmt,
						omap_obj->width,
						omap_obj->height, 0);
			} else {
				block = tiler_reserve_1d(obj->size);
			}

			if (IS_ERR(block)) {
				ret = PTR_ERR(block);
				dev_err(obj->dev->dev,
					"could not remap: %d (%d)\n", ret, fmt);
				goto fail;
			}

			/* TODO: enable async refill.. */
			ret = tiler_pin(block, omap_obj->pages, npages,
					omap_obj->roll, true);
			if (ret) {
				tiler_release(block);
				dev_err(obj->dev->dev,
						"could not pin: %d\n", ret);
				goto fail;
			}

			omap_obj->dma_addr = tiler_ssptr(block);
			omap_obj->block = block;

			DBG("got dma address: %pad", &omap_obj->dma_addr);
		}

		omap_obj->dma_addr_cnt++;

		*dma_addr = omap_obj->dma_addr;
	} else if (omap_gem_is_contiguous(omap_obj)) {
		*dma_addr = omap_obj->dma_addr;
	} else {
		ret = -EINVAL;
		goto fail;
	}

fail:
	mutex_unlock(&omap_obj->lock);

	return ret;
}