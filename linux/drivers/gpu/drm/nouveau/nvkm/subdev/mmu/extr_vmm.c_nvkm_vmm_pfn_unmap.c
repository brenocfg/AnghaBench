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
typedef  scalar_t__ u64 ;
struct nvkm_vmm {TYPE_1__* func; } ;
struct nvkm_vma {int mapped; size_t refd; scalar_t__ addr; scalar_t__ size; scalar_t__ memory; } ;
struct TYPE_2__ {int /*<<< orphan*/ * page; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t NVKM_VMA_PAGE_NONE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 struct nvkm_vma* node (struct nvkm_vma*,struct nvkm_vma*) ; 
 struct nvkm_vma* nvkm_vmm_node_search (struct nvkm_vmm*,scalar_t__) ; 
 struct nvkm_vma* nvkm_vmm_pfn_split_merge (struct nvkm_vmm*,struct nvkm_vma*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvkm_vmm_ptes_unmap_put (struct nvkm_vmm*,int /*<<< orphan*/ *,scalar_t__,scalar_t__,int,int) ; 

int
nvkm_vmm_pfn_unmap(struct nvkm_vmm *vmm, u64 addr, u64 size)
{
	struct nvkm_vma *vma = nvkm_vmm_node_search(vmm, addr);
	struct nvkm_vma *next;
	u64 limit = addr + size;
	u64 start = addr;

	if (!vma)
		return -EINVAL;

	do {
		if (!vma->mapped || vma->memory)
			continue;

		size = min(limit - start, vma->size - (start - vma->addr));

		nvkm_vmm_ptes_unmap_put(vmm, &vmm->func->page[vma->refd],
					start, size, false, true);

		next = nvkm_vmm_pfn_split_merge(vmm, vma, start, size, 0, false);
		if (!WARN_ON(!next)) {
			vma = next;
			vma->refd = NVKM_VMA_PAGE_NONE;
			vma->mapped = false;
		}
	} while ((vma = node(vma, next)) && (start = vma->addr) < limit);

	return 0;
}