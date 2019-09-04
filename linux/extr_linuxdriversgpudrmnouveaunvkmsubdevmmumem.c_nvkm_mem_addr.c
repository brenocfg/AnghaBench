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
typedef  unsigned long long u64 ;
struct nvkm_memory {int dummy; } ;
struct nvkm_mem {int pages; unsigned long long* dma; scalar_t__ mem; } ;

/* Variables and functions */
 struct nvkm_mem* nvkm_mem (struct nvkm_memory*) ; 

__attribute__((used)) static u64
nvkm_mem_addr(struct nvkm_memory *memory)
{
	struct nvkm_mem *mem = nvkm_mem(memory);
	if (mem->pages == 1 && mem->mem)
		return mem->dma[0];
	return ~0ULL;
}