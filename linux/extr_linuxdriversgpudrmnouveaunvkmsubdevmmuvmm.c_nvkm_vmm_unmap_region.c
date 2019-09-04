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
struct nvkm_vmm {int /*<<< orphan*/  root; TYPE_2__* mmu; } ;
struct nvkm_vma {int /*<<< orphan*/  head; int /*<<< orphan*/  tree; scalar_t__ size; int /*<<< orphan*/  memory; scalar_t__ part; int /*<<< orphan*/  tags; } ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;
struct TYPE_4__ {TYPE_1__ subdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nvkm_vma*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct nvkm_vma* node (struct nvkm_vma*,struct nvkm_vma*) ; 
 int /*<<< orphan*/  nvkm_memory_tags_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_memory_unref (int /*<<< orphan*/ *) ; 
 struct nvkm_vma* prev ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
nvkm_vmm_unmap_region(struct nvkm_vmm *vmm, struct nvkm_vma *vma)
{
	struct nvkm_vma *next;

	nvkm_memory_tags_put(vma->memory, vmm->mmu->subdev.device, &vma->tags);
	nvkm_memory_unref(&vma->memory);

	if (vma->part) {
		struct nvkm_vma *prev = node(vma, prev);
		if (!prev->memory) {
			prev->size += vma->size;
			rb_erase(&vma->tree, &vmm->root);
			list_del(&vma->head);
			kfree(vma);
			vma = prev;
		}
	}

	next = node(vma, next);
	if (next && next->part) {
		if (!next->memory) {
			vma->size += next->size;
			rb_erase(&next->tree, &vmm->root);
			list_del(&next->head);
			kfree(next);
		}
	}
}