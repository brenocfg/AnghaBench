#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct msm_gem_object {int flags; int /*<<< orphan*/ * pages; TYPE_2__* sgt; } ;
struct drm_gem_object {TYPE_1__* dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  nents; int /*<<< orphan*/  sgl; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int MSM_BO_UNCACHED ; 
 int MSM_BO_WC ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_put_pages (struct drm_gem_object*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 int /*<<< orphan*/  put_pages_vram (struct drm_gem_object*) ; 
 int /*<<< orphan*/  sg_free_table (TYPE_2__*) ; 
 struct msm_gem_object* to_msm_bo (struct drm_gem_object*) ; 
 scalar_t__ use_pages (struct drm_gem_object*) ; 

__attribute__((used)) static void put_pages(struct drm_gem_object *obj)
{
	struct msm_gem_object *msm_obj = to_msm_bo(obj);

	if (msm_obj->pages) {
		if (msm_obj->sgt) {
			/* For non-cached buffers, ensure the new
			 * pages are clean because display controller,
			 * GPU, etc. are not coherent:
			 */
			if (msm_obj->flags & (MSM_BO_WC|MSM_BO_UNCACHED))
				dma_unmap_sg(obj->dev->dev, msm_obj->sgt->sgl,
					     msm_obj->sgt->nents,
					     DMA_BIDIRECTIONAL);

			sg_free_table(msm_obj->sgt);
			kfree(msm_obj->sgt);
		}

		if (use_pages(obj))
			drm_gem_put_pages(obj, msm_obj->pages, true, false);
		else
			put_pages_vram(obj);

		msm_obj->pages = NULL;
	}
}