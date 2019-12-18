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
typedef  int /*<<< orphan*/  vm_fault_t ;
struct vm_fault {int /*<<< orphan*/  address; int /*<<< orphan*/  vma; } ;
struct page {int dummy; } ;
struct nouveau_drm {TYPE_3__* dmem; TYPE_1__* dev; } ;
struct migrate_vma {int* src; int* dst; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_5__ {scalar_t__ (* copy_func ) (struct nouveau_drm*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {TYPE_2__ migrate; } ;
struct TYPE_4__ {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  GFP_HIGHUSER ; 
 int MIGRATE_PFN_LOCKED ; 
 int MIGRATE_PFN_MIGRATE ; 
 int /*<<< orphan*/  NOUVEAU_APER_HOST ; 
 int /*<<< orphan*/  NOUVEAU_APER_VRAM ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  VM_FAULT_SIGBUS ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 struct page* alloc_page_vma (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_page (struct device*,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int migrate_pfn (int /*<<< orphan*/ ) ; 
 struct page* migrate_pfn_to_page (int) ; 
 int /*<<< orphan*/  nouveau_dmem_page_addr (struct page*) ; 
 int /*<<< orphan*/  page_to_pfn (struct page*) ; 
 scalar_t__ stub1 (struct nouveau_drm*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static vm_fault_t nouveau_dmem_fault_copy_one(struct nouveau_drm *drm,
		struct vm_fault *vmf, struct migrate_vma *args,
		dma_addr_t *dma_addr)
{
	struct device *dev = drm->dev->dev;
	struct page *dpage, *spage;

	spage = migrate_pfn_to_page(args->src[0]);
	if (!spage || !(args->src[0] & MIGRATE_PFN_MIGRATE))
		return 0;

	dpage = alloc_page_vma(GFP_HIGHUSER, vmf->vma, vmf->address);
	if (!dpage)
		return VM_FAULT_SIGBUS;
	lock_page(dpage);

	*dma_addr = dma_map_page(dev, dpage, 0, PAGE_SIZE, DMA_BIDIRECTIONAL);
	if (dma_mapping_error(dev, *dma_addr))
		goto error_free_page;

	if (drm->dmem->migrate.copy_func(drm, 1, NOUVEAU_APER_HOST, *dma_addr,
			NOUVEAU_APER_VRAM, nouveau_dmem_page_addr(spage)))
		goto error_dma_unmap;

	args->dst[0] = migrate_pfn(page_to_pfn(dpage)) | MIGRATE_PFN_LOCKED;
	return 0;

error_dma_unmap:
	dma_unmap_page(dev, *dma_addr, PAGE_SIZE, DMA_BIDIRECTIONAL);
error_free_page:
	__free_page(dpage);
	return VM_FAULT_SIGBUS;
}