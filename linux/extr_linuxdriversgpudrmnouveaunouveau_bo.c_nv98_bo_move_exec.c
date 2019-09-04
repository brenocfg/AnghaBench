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
struct ttm_mem_reg {int num_pages; } ;
struct ttm_buffer_object {int dummy; } ;
struct nouveau_mem {TYPE_1__* vma; } ;
struct nouveau_channel {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEGIN_NV04 (struct nouveau_channel*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  NvSubCopy ; 
 int /*<<< orphan*/  OUT_RING (struct nouveau_channel*,int) ; 
 int PAGE_SHIFT ; 
 int RING_SPACE (struct nouveau_channel*,int) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 struct nouveau_mem* nouveau_mem (struct ttm_mem_reg*) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nv98_bo_move_exec(struct nouveau_channel *chan, struct ttm_buffer_object *bo,
		  struct ttm_mem_reg *old_reg, struct ttm_mem_reg *new_reg)
{
	struct nouveau_mem *mem = nouveau_mem(old_reg);
	int ret = RING_SPACE(chan, 7);
	if (ret == 0) {
		BEGIN_NV04(chan, NvSubCopy, 0x0320, 6);
		OUT_RING  (chan, upper_32_bits(mem->vma[0].addr));
		OUT_RING  (chan, lower_32_bits(mem->vma[0].addr));
		OUT_RING  (chan, upper_32_bits(mem->vma[1].addr));
		OUT_RING  (chan, lower_32_bits(mem->vma[1].addr));
		OUT_RING  (chan, 0x00000000 /* COPY */);
		OUT_RING  (chan, new_reg->num_pages << PAGE_SHIFT);
	}
	return ret;
}