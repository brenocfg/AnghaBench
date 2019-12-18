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
typedef  int /*<<< orphan*/  u32 ;
struct omap_gem_object {scalar_t__ dma_addr_cnt; int flags; int /*<<< orphan*/  lock; scalar_t__ block; } ;
struct drm_gem_object {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int EINVAL ; 
 int OMAP_BO_TILED ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tiler_tsptr (scalar_t__,int /*<<< orphan*/ ,int,int) ; 
 struct omap_gem_object* to_omap_bo (struct drm_gem_object*) ; 

int omap_gem_rotated_dma_addr(struct drm_gem_object *obj, u32 orient,
		int x, int y, dma_addr_t *dma_addr)
{
	struct omap_gem_object *omap_obj = to_omap_bo(obj);
	int ret = -EINVAL;

	mutex_lock(&omap_obj->lock);

	if ((omap_obj->dma_addr_cnt > 0) && omap_obj->block &&
			(omap_obj->flags & OMAP_BO_TILED)) {
		*dma_addr = tiler_tsptr(omap_obj->block, orient, x, y);
		ret = 0;
	}

	mutex_unlock(&omap_obj->lock);

	return ret;
}