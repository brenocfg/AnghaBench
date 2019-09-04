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
struct nouveau_vma {int /*<<< orphan*/ * mem; int /*<<< orphan*/  addr; TYPE_1__* vmm; } ;
struct TYPE_2__ {int /*<<< orphan*/  vmm; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvif_vmm_unmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
nouveau_vma_unmap(struct nouveau_vma *vma)
{
	if (vma->mem) {
		nvif_vmm_unmap(&vma->vmm->vmm, vma->addr);
		vma->mem = NULL;
	}
}