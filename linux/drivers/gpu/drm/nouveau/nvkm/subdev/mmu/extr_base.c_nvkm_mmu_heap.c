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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
struct nvkm_mmu {size_t heap_nr; TYPE_1__* heap; } ;
struct TYPE_2__ {scalar_t__ size; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static int
nvkm_mmu_heap(struct nvkm_mmu *mmu, u8 type, u64 size)
{
	if (size) {
		if (!WARN_ON(mmu->heap_nr == ARRAY_SIZE(mmu->heap))) {
			mmu->heap[mmu->heap_nr].type = type;
			mmu->heap[mmu->heap_nr].size = size;
			return mmu->heap_nr++;
		}
	}
	return -EINVAL;
}