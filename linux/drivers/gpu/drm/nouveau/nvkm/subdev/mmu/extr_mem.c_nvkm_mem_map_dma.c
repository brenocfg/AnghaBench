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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_vmm_map {int /*<<< orphan*/  dma; int /*<<< orphan*/  offset; int /*<<< orphan*/ * memory; } ;
struct nvkm_vmm {int dummy; } ;
struct nvkm_vma {int dummy; } ;
struct nvkm_memory {int dummy; } ;
struct nvkm_mem {int /*<<< orphan*/  dma; int /*<<< orphan*/  memory; } ;

/* Variables and functions */
 struct nvkm_mem* nvkm_mem (struct nvkm_memory*) ; 
 int nvkm_vmm_map (struct nvkm_vmm*,struct nvkm_vma*,void*,int /*<<< orphan*/ ,struct nvkm_vmm_map*) ; 

__attribute__((used)) static int
nvkm_mem_map_dma(struct nvkm_memory *memory, u64 offset, struct nvkm_vmm *vmm,
		 struct nvkm_vma *vma, void *argv, u32 argc)
{
	struct nvkm_mem *mem = nvkm_mem(memory);
	struct nvkm_vmm_map map = {
		.memory = &mem->memory,
		.offset = offset,
		.dma = mem->dma,
	};
	return nvkm_vmm_map(vmm, vma, argv, argc, &map);
}