#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct nvkm_mmu {size_t type_nr; TYPE_2__* type; TYPE_1__* heap; } ;
struct TYPE_4__ {int type; int heap; } ;
struct TYPE_3__ {int type; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_2__*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static void
nvkm_mmu_type(struct nvkm_mmu *mmu, int heap, u8 type)
{
	if (heap >= 0 && !WARN_ON(mmu->type_nr == ARRAY_SIZE(mmu->type))) {
		mmu->type[mmu->type_nr].type = type | mmu->heap[heap].type;
		mmu->type[mmu->type_nr].heap = heap;
		mmu->type_nr++;
	}
}