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
typedef  size_t u8 ;
typedef  scalar_t__ u64 ;
struct nvkm_vmm_page {int dummy; } ;
struct nvkm_vmm {TYPE_1__* func; } ;
struct nvkm_vma {int mapped; size_t refd; size_t page; int used; int user; scalar_t__ size; scalar_t__ addr; scalar_t__ sparse; scalar_t__ mapref; scalar_t__ part; int /*<<< orphan*/ * memory; } ;
struct TYPE_2__ {struct nvkm_vmm_page* page; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (scalar_t__) ; 
 size_t const NVKM_VMA_PAGE_NONE ; 
 struct nvkm_vma* node (struct nvkm_vma*,struct nvkm_vma*) ; 
 int /*<<< orphan*/  nvkm_vmm_node_remove (struct nvkm_vmm*,struct nvkm_vma*) ; 
 int /*<<< orphan*/  nvkm_vmm_ptes_put (struct nvkm_vmm*,struct nvkm_vmm_page const*,scalar_t__ const,scalar_t__) ; 
 int /*<<< orphan*/  nvkm_vmm_ptes_sparse (struct nvkm_vmm*,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  nvkm_vmm_ptes_sparse_put (struct nvkm_vmm*,struct nvkm_vmm_page const*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  nvkm_vmm_ptes_unmap_put (struct nvkm_vmm*,struct nvkm_vmm_page const*,scalar_t__ const,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  nvkm_vmm_put_region (struct nvkm_vmm*,struct nvkm_vma*) ; 
 int /*<<< orphan*/  nvkm_vmm_unmap_region (struct nvkm_vmm*,struct nvkm_vma*) ; 

void
nvkm_vmm_put_locked(struct nvkm_vmm *vmm, struct nvkm_vma *vma)
{
	const struct nvkm_vmm_page *page = vmm->func->page;
	struct nvkm_vma *next = vma;

	BUG_ON(vma->part);

	if (vma->mapref || !vma->sparse) {
		do {
			const bool mem = next->memory != NULL;
			const bool map = next->mapped;
			const u8  refd = next->refd;
			const u64 addr = next->addr;
			u64 size = next->size;

			/* Merge regions that are in the same state. */
			while ((next = node(next, next)) && next->part &&
			       (next->mapped == map) &&
			       (next->memory != NULL) == mem &&
			       (next->refd == refd))
				size += next->size;

			if (map) {
				/* Region(s) are mapped, merge the unmap
				 * and dereference into a single walk of
				 * the page tree.
				 */
				nvkm_vmm_ptes_unmap_put(vmm, &page[refd], addr,
							size, vma->sparse,
							!mem);
			} else
			if (refd != NVKM_VMA_PAGE_NONE) {
				/* Drop allocation-time PTE references. */
				nvkm_vmm_ptes_put(vmm, &page[refd], addr, size);
			}
		} while (next && next->part);
	}

	/* Merge any mapped regions that were split from the initial
	 * address-space allocation back into the allocated VMA, and
	 * release memory/compression resources.
	 */
	next = vma;
	do {
		if (next->mapped)
			nvkm_vmm_unmap_region(vmm, next);
	} while ((next = node(vma, next)) && next->part);

	if (vma->sparse && !vma->mapref) {
		/* Sparse region that was allocated with a fixed page size,
		 * meaning all relevant PTEs were referenced once when the
		 * region was allocated, and remained that way, regardless
		 * of whether memory was mapped into it afterwards.
		 *
		 * The process of unmapping, unsparsing, and dereferencing
		 * PTEs can be done in a single page tree walk.
		 */
		nvkm_vmm_ptes_sparse_put(vmm, &page[vma->refd], vma->addr, vma->size);
	} else
	if (vma->sparse) {
		/* Sparse region that wasn't allocated with a fixed page size,
		 * PTE references were taken both at allocation time (to make
		 * the GPU see the region as sparse), and when mapping memory
		 * into the region.
		 *
		 * The latter was handled above, and the remaining references
		 * are dealt with here.
		 */
		nvkm_vmm_ptes_sparse(vmm, vma->addr, vma->size, false);
	}

	/* Remove VMA from the list of allocated nodes. */
	nvkm_vmm_node_remove(vmm, vma);

	/* Merge VMA back into the free list. */
	vma->page = NVKM_VMA_PAGE_NONE;
	vma->refd = NVKM_VMA_PAGE_NONE;
	vma->used = false;
	vma->user = false;
	nvkm_vmm_put_region(vmm, vma);
}