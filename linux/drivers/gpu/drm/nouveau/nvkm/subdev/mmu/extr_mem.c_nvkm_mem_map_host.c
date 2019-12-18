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
struct nvkm_memory {int dummy; } ;
struct nvkm_mem {int /*<<< orphan*/  pages; scalar_t__ mem; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 int /*<<< orphan*/  VM_MAP ; 
 struct nvkm_mem* nvkm_mem (struct nvkm_memory*) ; 
 void* vmap (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
nvkm_mem_map_host(struct nvkm_memory *memory, void **pmap)
{
	struct nvkm_mem *mem = nvkm_mem(memory);
	if (mem->mem) {
		*pmap = vmap(mem->mem, mem->pages, VM_MAP, PAGE_KERNEL);
		return *pmap ? 0 : -EFAULT;
	}
	return -EINVAL;
}