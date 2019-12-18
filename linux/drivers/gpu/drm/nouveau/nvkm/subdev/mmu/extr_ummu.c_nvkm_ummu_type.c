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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_ummu {struct nvkm_mmu* mmu; } ;
struct nvkm_mmu {size_t type_nr; TYPE_1__* type; } ;
struct nvif_mmu_type_v0 {size_t index; int vram; int host; int comp; int disp; int kind; int mappable; int coherent; int uncached; int /*<<< orphan*/  heap; } ;
struct TYPE_2__ {size_t type; int /*<<< orphan*/  heap; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSYS ; 
 size_t NVKM_MEM_COHERENT ; 
 size_t NVKM_MEM_COMP ; 
 size_t NVKM_MEM_DISP ; 
 size_t NVKM_MEM_HOST ; 
 size_t NVKM_MEM_KIND ; 
 size_t NVKM_MEM_MAPPABLE ; 
 size_t NVKM_MEM_UNCACHED ; 
 size_t NVKM_MEM_VRAM ; 
 int nvif_unpack (int,void**,int /*<<< orphan*/ *,struct nvif_mmu_type_v0,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
nvkm_ummu_type(struct nvkm_ummu *ummu, void *argv, u32 argc)
{
	struct nvkm_mmu *mmu = ummu->mmu;
	union {
		struct nvif_mmu_type_v0 v0;
	} *args = argv;
	int ret = -ENOSYS;
	u8 type, index;

	if (!(ret = nvif_unpack(ret, &argv, &argc, args->v0, 0, 0, false))) {
		if ((index = args->v0.index) >= mmu->type_nr)
			return -EINVAL;
		type = mmu->type[index].type;
		args->v0.heap = mmu->type[index].heap;
		args->v0.vram = !!(type & NVKM_MEM_VRAM);
		args->v0.host = !!(type & NVKM_MEM_HOST);
		args->v0.comp = !!(type & NVKM_MEM_COMP);
		args->v0.disp = !!(type & NVKM_MEM_DISP);
		args->v0.kind = !!(type & NVKM_MEM_KIND);
		args->v0.mappable = !!(type & NVKM_MEM_MAPPABLE);
		args->v0.coherent = !!(type & NVKM_MEM_COHERENT);
		args->v0.uncached = !!(type & NVKM_MEM_UNCACHED);
	} else
		return ret;

	return 0;
}