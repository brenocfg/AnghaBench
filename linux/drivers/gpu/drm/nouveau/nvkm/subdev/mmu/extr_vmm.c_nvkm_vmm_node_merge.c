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
struct nvkm_vma {scalar_t__ size; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (struct nvkm_vma*) ; 
 int /*<<< orphan*/  nvkm_vmm_node_delete (struct nvkm_vmm*,struct nvkm_vma*) ; 
 int /*<<< orphan*/  nvkm_vmm_node_insert (struct nvkm_vmm*,struct nvkm_vma*) ; 
 int /*<<< orphan*/  nvkm_vmm_node_remove (struct nvkm_vmm*,struct nvkm_vma*) ; 

__attribute__((used)) static struct nvkm_vma *
nvkm_vmm_node_merge(struct nvkm_vmm *vmm, struct nvkm_vma *prev,
		    struct nvkm_vma *vma, struct nvkm_vma *next, u64 size)
{
	if (next) {
		if (vma->size == size) {
			vma->size += next->size;
			nvkm_vmm_node_delete(vmm, next);
			if (prev) {
				prev->size += vma->size;
				nvkm_vmm_node_delete(vmm, vma);
				return prev;
			}
			return vma;
		}
		BUG_ON(prev);

		nvkm_vmm_node_remove(vmm, next);
		vma->size -= size;
		next->addr -= size;
		next->size += size;
		nvkm_vmm_node_insert(vmm, next);
		return next;
	}

	if (prev) {
		if (vma->size != size) {
			nvkm_vmm_node_remove(vmm, vma);
			prev->size += size;
			vma->addr += size;
			vma->size -= size;
			nvkm_vmm_node_insert(vmm, vma);
		} else {
			prev->size += vma->size;
			nvkm_vmm_node_delete(vmm, vma);
		}
		return prev;
	}

	return vma;
}