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
struct page {int dummy; } ;
struct nouveau_drm {TYPE_2__* dmem; TYPE_3__* dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_6__ {struct device* dev; } ;
struct TYPE_4__ {scalar_t__ (* copy_func ) (struct nouveau_drm*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {TYPE_1__ migrate; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 unsigned long MIGRATE_PFN_LOCKED ; 
 unsigned long MIGRATE_PFN_MIGRATE ; 
 int /*<<< orphan*/  NOUVEAU_APER_HOST ; 
 int /*<<< orphan*/  NOUVEAU_APER_VRAM ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dma_map_page (struct device*,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long migrate_pfn (int /*<<< orphan*/ ) ; 
 struct page* migrate_pfn_to_page (unsigned long) ; 
 int /*<<< orphan*/  nouveau_dmem_page_addr (struct page*) ; 
 struct page* nouveau_dmem_page_alloc_locked (struct nouveau_drm*) ; 
 int /*<<< orphan*/  nouveau_dmem_page_free_locked (struct nouveau_drm*,struct page*) ; 
 int /*<<< orphan*/  page_to_pfn (struct page*) ; 
 scalar_t__ stub1 (struct nouveau_drm*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long nouveau_dmem_migrate_copy_one(struct nouveau_drm *drm,
		unsigned long src, dma_addr_t *dma_addr)
{
	struct device *dev = drm->dev->dev;
	struct page *dpage, *spage;

	spage = migrate_pfn_to_page(src);
	if (!spage || !(src & MIGRATE_PFN_MIGRATE))
		goto out;

	dpage = nouveau_dmem_page_alloc_locked(drm);
	if (!dpage)
		return 0;

	*dma_addr = dma_map_page(dev, spage, 0, PAGE_SIZE, DMA_BIDIRECTIONAL);
	if (dma_mapping_error(dev, *dma_addr))
		goto out_free_page;

	if (drm->dmem->migrate.copy_func(drm, 1, NOUVEAU_APER_VRAM,
			nouveau_dmem_page_addr(dpage), NOUVEAU_APER_HOST,
			*dma_addr))
		goto out_dma_unmap;

	return migrate_pfn(page_to_pfn(dpage)) | MIGRATE_PFN_LOCKED;

out_dma_unmap:
	dma_unmap_page(dev, *dma_addr, PAGE_SIZE, DMA_BIDIRECTIONAL);
out_free_page:
	nouveau_dmem_page_free_locked(drm, dpage);
out:
	return 0;
}