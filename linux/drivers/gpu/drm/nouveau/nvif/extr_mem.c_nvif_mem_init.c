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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct nvif_mmu {int type_nr; TYPE_2__* type; } ;
struct TYPE_3__ {int /*<<< orphan*/ * client; } ;
struct nvif_mem {TYPE_1__ object; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_4__ {int type; } ;

/* Variables and functions */
 int EINVAL ; 
 int nvif_mem_init_type (struct nvif_mmu*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,struct nvif_mem*) ; 

int
nvif_mem_init(struct nvif_mmu *mmu, s32 oclass, u8 type, u8 page,
	      u64 size, void *argv, u32 argc, struct nvif_mem *mem)
{
	int ret = -EINVAL, i;

	mem->object.client = NULL;

	for (i = 0; ret && i < mmu->type_nr; i++) {
		if ((mmu->type[i].type & type) == type) {
			ret = nvif_mem_init_type(mmu, oclass, i, page, size,
						 argv, argc, mem);
		}
	}

	return ret;
}