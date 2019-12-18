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
struct omap_gem_object {scalar_t__ dma_addr_cnt; int /*<<< orphan*/  lock; int /*<<< orphan*/ * block; scalar_t__ dma_addr; } ;
struct drm_gem_object {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int tiler_release (int /*<<< orphan*/ *) ; 
 int tiler_unpin (int /*<<< orphan*/ *) ; 
 struct omap_gem_object* to_omap_bo (struct drm_gem_object*) ; 

void omap_gem_unpin(struct drm_gem_object *obj)
{
	struct omap_gem_object *omap_obj = to_omap_bo(obj);
	int ret;

	mutex_lock(&omap_obj->lock);

	if (omap_obj->dma_addr_cnt > 0) {
		omap_obj->dma_addr_cnt--;
		if (omap_obj->dma_addr_cnt == 0) {
			ret = tiler_unpin(omap_obj->block);
			if (ret) {
				dev_err(obj->dev->dev,
					"could not unpin pages: %d\n", ret);
			}
			ret = tiler_release(omap_obj->block);
			if (ret) {
				dev_err(obj->dev->dev,
					"could not release unmap: %d\n", ret);
			}
			omap_obj->dma_addr = 0;
			omap_obj->block = NULL;
		}
	}

	mutex_unlock(&omap_obj->lock);
}