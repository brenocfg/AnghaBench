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
struct nvkm_vmm {int /*<<< orphan*/  free; } ;
struct nvkm_vma {scalar_t__ size; int /*<<< orphan*/  head; int /*<<< orphan*/  tree; int /*<<< orphan*/  used; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nvkm_vma*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct nvkm_vma* node (struct nvkm_vma*,struct nvkm_vma*) ; 
 int /*<<< orphan*/  nvkm_vmm_free_insert (struct nvkm_vmm*,struct nvkm_vma*) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nvkm_vmm_put_region(struct nvkm_vmm *vmm, struct nvkm_vma *vma)
{
	struct nvkm_vma *prev, *next;

	if ((prev = node(vma, prev)) && !prev->used) {
		rb_erase(&prev->tree, &vmm->free);
		list_del(&prev->head);
		vma->addr  = prev->addr;
		vma->size += prev->size;
		kfree(prev);
	}

	if ((next = node(vma, next)) && !next->used) {
		rb_erase(&next->tree, &vmm->free);
		list_del(&next->head);
		vma->size += next->size;
		kfree(next);
	}

	nvkm_vmm_free_insert(vmm, vma);
}