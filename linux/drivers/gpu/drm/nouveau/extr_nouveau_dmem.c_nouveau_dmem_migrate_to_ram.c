#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_fault_t ;
struct vm_fault {scalar_t__ address; int /*<<< orphan*/  vma; int /*<<< orphan*/  page; } ;
struct nouveau_fence {int dummy; } ;
struct nouveau_drm {TYPE_2__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  chan; } ;
struct nouveau_dmem {TYPE_1__ migrate; struct nouveau_drm* drm; } ;
struct migrate_vma {unsigned long* src; unsigned long* dst; int /*<<< orphan*/  cpages; scalar_t__ end; scalar_t__ start; int /*<<< orphan*/  vma; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ VM_FAULT_SIGBUS ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  migrate_vma_finalize (struct migrate_vma*) ; 
 int /*<<< orphan*/  migrate_vma_pages (struct migrate_vma*) ; 
 scalar_t__ migrate_vma_setup (struct migrate_vma*) ; 
 scalar_t__ nouveau_dmem_fault_copy_one (struct nouveau_drm*,struct vm_fault*,struct migrate_vma*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_dmem_fence_done (struct nouveau_fence**) ; 
 int /*<<< orphan*/  nouveau_fence_new (int /*<<< orphan*/ ,int,struct nouveau_fence**) ; 
 struct nouveau_dmem* page_to_dmem (int /*<<< orphan*/ ) ; 

__attribute__((used)) static vm_fault_t nouveau_dmem_migrate_to_ram(struct vm_fault *vmf)
{
	struct nouveau_dmem *dmem = page_to_dmem(vmf->page);
	struct nouveau_drm *drm = dmem->drm;
	struct nouveau_fence *fence;
	unsigned long src = 0, dst = 0;
	dma_addr_t dma_addr = 0;
	vm_fault_t ret;
	struct migrate_vma args = {
		.vma		= vmf->vma,
		.start		= vmf->address,
		.end		= vmf->address + PAGE_SIZE,
		.src		= &src,
		.dst		= &dst,
	};

	/*
	 * FIXME what we really want is to find some heuristic to migrate more
	 * than just one page on CPU fault. When such fault happens it is very
	 * likely that more surrounding page will CPU fault too.
	 */
	if (migrate_vma_setup(&args) < 0)
		return VM_FAULT_SIGBUS;
	if (!args.cpages)
		return 0;

	ret = nouveau_dmem_fault_copy_one(drm, vmf, &args, &dma_addr);
	if (ret || dst == 0)
		goto done;

	nouveau_fence_new(dmem->migrate.chan, false, &fence);
	migrate_vma_pages(&args);
	nouveau_dmem_fence_done(&fence);
	dma_unmap_page(drm->dev->dev, dma_addr, PAGE_SIZE, DMA_BIDIRECTIONAL);
done:
	migrate_vma_finalize(&args);
	return ret;
}