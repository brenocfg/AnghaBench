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
struct nvkm_vmm {int dummy; } ;
struct nvkm_vma {int dummy; } ;
struct nvkm_gpuobj {int /*<<< orphan*/  memory; } ;

/* Variables and functions */
 int nvkm_memory_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nvkm_vmm*,struct nvkm_vma*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nvkm_gpuobj_heap_map(struct nvkm_gpuobj *gpuobj, u64 offset,
		     struct nvkm_vmm *vmm, struct nvkm_vma *vma,
		     void *argv, u32 argc)
{
	return nvkm_memory_map(gpuobj->memory, offset, vmm, vma, argv, argc);
}