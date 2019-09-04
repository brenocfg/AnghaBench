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
struct nvkm_mmu {size_t heap_nr; TYPE_1__* heap; } ;
struct nvif_mmu_heap_v0 {size_t index; int /*<<< orphan*/  size; } ;
struct TYPE_2__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSYS ; 
 int nvif_unpack (int,void**,int /*<<< orphan*/ *,struct nvif_mmu_heap_v0,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
nvkm_ummu_heap(struct nvkm_ummu *ummu, void *argv, u32 argc)
{
	struct nvkm_mmu *mmu = ummu->mmu;
	union {
		struct nvif_mmu_heap_v0 v0;
	} *args = argv;
	int ret = -ENOSYS;
	u8 index;

	if (!(ret = nvif_unpack(ret, &argv, &argc, args->v0, 0, 0, false))) {
		if ((index = args->v0.index) >= mmu->heap_nr)
			return -EINVAL;
		args->v0.size = mmu->heap[index].size;
	} else
		return ret;

	return 0;
}