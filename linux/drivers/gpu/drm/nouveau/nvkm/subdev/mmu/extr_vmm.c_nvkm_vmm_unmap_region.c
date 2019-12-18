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
struct nvkm_vmm {TYPE_2__* mmu; } ;
struct nvkm_vma {int mapped; int /*<<< orphan*/  size; scalar_t__ part; int /*<<< orphan*/  memory; int /*<<< orphan*/  tags; } ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;
struct TYPE_4__ {TYPE_1__ subdev; } ;

/* Variables and functions */
 struct nvkm_vma* node (struct nvkm_vma*,struct nvkm_vma*) ; 
 int /*<<< orphan*/  nvkm_memory_tags_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_memory_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_vmm_node_merge (struct nvkm_vmm*,struct nvkm_vma*,struct nvkm_vma*,struct nvkm_vma*,int /*<<< orphan*/ ) ; 

void
nvkm_vmm_unmap_region(struct nvkm_vmm *vmm, struct nvkm_vma *vma)
{
	struct nvkm_vma *prev = NULL;
	struct nvkm_vma *next;

	nvkm_memory_tags_put(vma->memory, vmm->mmu->subdev.device, &vma->tags);
	nvkm_memory_unref(&vma->memory);
	vma->mapped = false;

	if (vma->part && (prev = node(vma, prev)) && prev->mapped)
		prev = NULL;
	if ((next = node(vma, next)) && (!next->part || next->mapped))
		next = NULL;
	nvkm_vmm_node_merge(vmm, prev, vma, next, vma->size);
}