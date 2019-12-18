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
struct nvif_vma {unsigned long long addr; int size; } ;
struct nouveau_vma {scalar_t__ refs; unsigned long long addr; int /*<<< orphan*/  head; TYPE_1__* vmm; } ;
struct TYPE_2__ {int /*<<< orphan*/  vmm; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nouveau_vma*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvif_vmm_put (int /*<<< orphan*/ *,struct nvif_vma*) ; 

void
nouveau_vma_del(struct nouveau_vma **pvma)
{
	struct nouveau_vma *vma = *pvma;
	if (vma && --vma->refs <= 0) {
		if (likely(vma->addr != ~0ULL)) {
			struct nvif_vma tmp = { .addr = vma->addr, .size = 1 };
			nvif_vmm_put(&vma->vmm->vmm, &tmp);
		}
		list_del(&vma->head);
		kfree(*pvma);
		*pvma = NULL;
	}
}