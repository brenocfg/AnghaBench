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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_vmm {int dummy; } ;
struct nvkm_vma {int dummy; } ;
struct nvkm_memory {int dummy; } ;
struct TYPE_2__ {struct nvkm_memory* ram; } ;

/* Variables and functions */
 TYPE_1__* nv50_instobj (struct nvkm_memory*) ; 
 int nvkm_memory_map (struct nvkm_memory*,int /*<<< orphan*/ ,struct nvkm_vmm*,struct nvkm_vma*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nv50_instobj_map(struct nvkm_memory *memory, u64 offset, struct nvkm_vmm *vmm,
		 struct nvkm_vma *vma, void *argv, u32 argc)
{
	memory = nv50_instobj(memory)->ram;
	return nvkm_memory_map(memory, offset, vmm, vma, argv, argc);
}