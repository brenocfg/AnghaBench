#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_mmu {TYPE_3__* func; TYPE_1__* type; } ;
struct nvkm_memory {int dummy; } ;
struct TYPE_5__ {int (* vram ) (struct nvkm_mmu*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,struct nvkm_memory**) ;} ;
struct TYPE_6__ {TYPE_2__ mem; } ;
struct TYPE_4__ {int type; } ;

/* Variables and functions */
 int NVKM_MEM_VRAM ; 
 int nvkm_mem_new_host (struct nvkm_mmu*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,struct nvkm_memory**) ; 
 int /*<<< orphan*/  nvkm_memory_unref (struct nvkm_memory**) ; 
 int stub1 (struct nvkm_mmu*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,struct nvkm_memory**) ; 

int
nvkm_mem_new_type(struct nvkm_mmu *mmu, int type, u8 page, u64 size,
		  void *argv, u32 argc, struct nvkm_memory **pmemory)
{
	struct nvkm_memory *memory = NULL;
	int ret;

	if (mmu->type[type].type & NVKM_MEM_VRAM) {
		ret = mmu->func->mem.vram(mmu, type, page, size,
					  argv, argc, &memory);
	} else {
		ret = nvkm_mem_new_host(mmu, type, page, size,
					argv, argc, &memory);
	}

	if (ret)
		nvkm_memory_unref(&memory);
	*pmemory = memory;
	return ret;
}