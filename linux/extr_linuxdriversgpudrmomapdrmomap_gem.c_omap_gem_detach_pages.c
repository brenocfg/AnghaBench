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
struct omap_gem_object {int /*<<< orphan*/ * pages; scalar_t__* dma_addrs; int /*<<< orphan*/  lock; } ;
struct drm_gem_object {unsigned int size; TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 unsigned int PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_put_pages (struct drm_gem_object*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 struct omap_gem_object* to_omap_bo (struct drm_gem_object*) ; 

__attribute__((used)) static void omap_gem_detach_pages(struct drm_gem_object *obj)
{
	struct omap_gem_object *omap_obj = to_omap_bo(obj);
	unsigned int npages = obj->size >> PAGE_SHIFT;
	unsigned int i;

	lockdep_assert_held(&omap_obj->lock);

	for (i = 0; i < npages; i++) {
		if (omap_obj->dma_addrs[i])
			dma_unmap_page(obj->dev->dev, omap_obj->dma_addrs[i],
				       PAGE_SIZE, DMA_TO_DEVICE);
	}

	kfree(omap_obj->dma_addrs);
	omap_obj->dma_addrs = NULL;

	drm_gem_put_pages(obj, omap_obj->pages, true, false);
	omap_obj->pages = NULL;
}