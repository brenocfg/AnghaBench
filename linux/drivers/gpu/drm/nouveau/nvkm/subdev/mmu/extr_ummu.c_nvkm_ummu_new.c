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
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_object {int dummy; } ;
struct nvkm_ummu {struct nvkm_object object; struct nvkm_mmu* mmu; } ;
struct nvkm_oclass {int dummy; } ;
struct nvkm_mmu {int /*<<< orphan*/  type_nr; int /*<<< orphan*/  heap_nr; int /*<<< orphan*/  dma_bits; TYPE_1__* func; } ;
struct nvkm_device {struct nvkm_mmu* mmu; } ;
struct nvif_mmu_v0 {int kind_nr; int /*<<< orphan*/  type_nr; int /*<<< orphan*/  heap_nr; int /*<<< orphan*/  dmabits; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* kind ) (struct nvkm_mmu*,int*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nvkm_ummu* kzalloc (int,int /*<<< orphan*/ ) ; 
 int nvif_unpack (int,void**,int /*<<< orphan*/ *,struct nvif_mmu_v0,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvkm_object_ctor (int /*<<< orphan*/ *,struct nvkm_oclass const*,struct nvkm_object*) ; 
 int /*<<< orphan*/  nvkm_ummu ; 
 int /*<<< orphan*/  stub1 (struct nvkm_mmu*,int*) ; 

int
nvkm_ummu_new(struct nvkm_device *device, const struct nvkm_oclass *oclass,
	      void *argv, u32 argc, struct nvkm_object **pobject)
{
	union {
		struct nvif_mmu_v0 v0;
	} *args = argv;
	struct nvkm_mmu *mmu = device->mmu;
	struct nvkm_ummu *ummu;
	int ret = -ENOSYS, kinds = 0;

	if (mmu->func->kind)
		mmu->func->kind(mmu, &kinds);

	if (!(ret = nvif_unpack(ret, &argv, &argc, args->v0, 0, 0, false))) {
		args->v0.dmabits = mmu->dma_bits;
		args->v0.heap_nr = mmu->heap_nr;
		args->v0.type_nr = mmu->type_nr;
		args->v0.kind_nr = kinds;
	} else
		return ret;

	if (!(ummu = kzalloc(sizeof(*ummu), GFP_KERNEL)))
		return -ENOMEM;
	nvkm_object_ctor(&nvkm_ummu, oclass, &ummu->object);
	ummu->mmu = mmu;
	*pobject = &ummu->object;
	return 0;
}