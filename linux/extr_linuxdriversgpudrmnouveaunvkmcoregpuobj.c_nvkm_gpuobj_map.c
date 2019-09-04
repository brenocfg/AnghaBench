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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_vmm {int dummy; } ;
struct nvkm_vma {int dummy; } ;
struct nvkm_gpuobj {TYPE_1__* node; int /*<<< orphan*/  parent; } ;
struct TYPE_2__ {scalar_t__ offset; } ;

/* Variables and functions */
 int nvkm_memory_map (int /*<<< orphan*/ ,scalar_t__,struct nvkm_vmm*,struct nvkm_vma*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nvkm_gpuobj_map(struct nvkm_gpuobj *gpuobj, u64 offset,
		struct nvkm_vmm *vmm, struct nvkm_vma *vma,
		void *argv, u32 argc)
{
	return nvkm_memory_map(gpuobj->parent, gpuobj->node->offset + offset,
			       vmm, vma, argv, argc);
}