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
typedef  scalar_t__ u64 ;
struct nvkm_vmm {int dummy; } ;
struct nvkm_vma {scalar_t__ addr; scalar_t__ size; int part; } ;

/* Variables and functions */
 struct nvkm_vma* nvkm_vma_tail (struct nvkm_vma*,scalar_t__) ; 
 int /*<<< orphan*/  nvkm_vmm_node_insert (struct nvkm_vmm*,struct nvkm_vma*) ; 
 int /*<<< orphan*/  nvkm_vmm_node_merge (struct nvkm_vmm*,struct nvkm_vma*,struct nvkm_vma*,int /*<<< orphan*/ *,scalar_t__) ; 

struct nvkm_vma *
nvkm_vmm_node_split(struct nvkm_vmm *vmm,
		    struct nvkm_vma *vma, u64 addr, u64 size)
{
	struct nvkm_vma *prev = NULL;

	if (vma->addr != addr) {
		prev = vma;
		if (!(vma = nvkm_vma_tail(vma, vma->size + vma->addr - addr)))
			return NULL;
		vma->part = true;
		nvkm_vmm_node_insert(vmm, vma);
	}

	if (vma->size != size) {
		struct nvkm_vma *tmp;
		if (!(tmp = nvkm_vma_tail(vma, vma->size - size))) {
			nvkm_vmm_node_merge(vmm, prev, vma, NULL, vma->size);
			return NULL;
		}
		tmp->part = true;
		nvkm_vmm_node_insert(vmm, tmp);
	}

	return vma;
}