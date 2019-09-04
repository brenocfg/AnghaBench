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
struct nvif_vma {int /*<<< orphan*/  addr; } ;
struct nouveau_vma {struct nouveau_mem* mem; TYPE_1__* vmm; int /*<<< orphan*/  addr; } ;
struct nouveau_mem {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  vmm; } ;

/* Variables and functions */
 int nouveau_mem_map (struct nouveau_mem*,int /*<<< orphan*/ *,struct nvif_vma*) ; 

int
nouveau_vma_map(struct nouveau_vma *vma, struct nouveau_mem *mem)
{
	struct nvif_vma tmp = { .addr = vma->addr };
	int ret = nouveau_mem_map(mem, &vma->vmm->vmm, &tmp);
	if (ret)
		return ret;
	vma->mem = mem;
	return 0;
}