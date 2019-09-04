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
struct ttm_tt {int dummy; } ;
struct ttm_mem_reg {int dummy; } ;
struct nouveau_sgdma_be {struct nouveau_mem* mem; int /*<<< orphan*/  ttm; } ;
struct nouveau_mem {int /*<<< orphan*/ * vma; TYPE_1__* cli; } ;
struct TYPE_4__ {int /*<<< orphan*/  vmm; } ;
struct TYPE_3__ {TYPE_2__ vmm; } ;

/* Variables and functions */
 struct nouveau_mem* nouveau_mem (struct ttm_mem_reg*) ; 
 int /*<<< orphan*/  nouveau_mem_fini (struct nouveau_mem*) ; 
 int nouveau_mem_host (struct ttm_mem_reg*,int /*<<< orphan*/ *) ; 
 int nouveau_mem_map (struct nouveau_mem*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nv04_sgdma_bind(struct ttm_tt *ttm, struct ttm_mem_reg *reg)
{
	struct nouveau_sgdma_be *nvbe = (struct nouveau_sgdma_be *)ttm;
	struct nouveau_mem *mem = nouveau_mem(reg);
	int ret;

	ret = nouveau_mem_host(reg, &nvbe->ttm);
	if (ret)
		return ret;

	ret = nouveau_mem_map(mem, &mem->cli->vmm.vmm, &mem->vma[0]);
	if (ret) {
		nouveau_mem_fini(mem);
		return ret;
	}

	nvbe->mem = mem;
	return 0;
}