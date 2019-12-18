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
typedef  int u64 ;
typedef  int u32 ;
struct ttm_mem_reg {int num_pages; } ;
struct ttm_buffer_object {int dummy; } ;
struct nouveau_mem {int /*<<< orphan*/  kind; TYPE_1__* vma; } ;
struct nouveau_channel {int dummy; } ;
struct TYPE_2__ {int addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEGIN_NV04 (struct nouveau_channel*,int /*<<< orphan*/ ,int,int) ; 
 int NV_MEMORY_TO_MEMORY_FORMAT_NOP ; 
 int /*<<< orphan*/  NvSubCopy ; 
 int /*<<< orphan*/  OUT_RING (struct nouveau_channel*,int) ; 
 int PAGE_SHIFT ; 
 int RING_SPACE (struct nouveau_channel*,int) ; 
 int lower_32_bits (int) ; 
 int min (int,int) ; 
 struct nouveau_mem* nouveau_mem (struct ttm_mem_reg*) ; 
 int upper_32_bits (int) ; 

__attribute__((used)) static int
nv50_bo_move_m2mf(struct nouveau_channel *chan, struct ttm_buffer_object *bo,
		  struct ttm_mem_reg *old_reg, struct ttm_mem_reg *new_reg)
{
	struct nouveau_mem *mem = nouveau_mem(old_reg);
	u64 length = (new_reg->num_pages << PAGE_SHIFT);
	u64 src_offset = mem->vma[0].addr;
	u64 dst_offset = mem->vma[1].addr;
	int src_tiled = !!mem->kind;
	int dst_tiled = !!nouveau_mem(new_reg)->kind;
	int ret;

	while (length) {
		u32 amount, stride, height;

		ret = RING_SPACE(chan, 18 + 6 * (src_tiled + dst_tiled));
		if (ret)
			return ret;

		amount  = min(length, (u64)(4 * 1024 * 1024));
		stride  = 16 * 4;
		height  = amount / stride;

		if (src_tiled) {
			BEGIN_NV04(chan, NvSubCopy, 0x0200, 7);
			OUT_RING  (chan, 0);
			OUT_RING  (chan, 0);
			OUT_RING  (chan, stride);
			OUT_RING  (chan, height);
			OUT_RING  (chan, 1);
			OUT_RING  (chan, 0);
			OUT_RING  (chan, 0);
		} else {
			BEGIN_NV04(chan, NvSubCopy, 0x0200, 1);
			OUT_RING  (chan, 1);
		}
		if (dst_tiled) {
			BEGIN_NV04(chan, NvSubCopy, 0x021c, 7);
			OUT_RING  (chan, 0);
			OUT_RING  (chan, 0);
			OUT_RING  (chan, stride);
			OUT_RING  (chan, height);
			OUT_RING  (chan, 1);
			OUT_RING  (chan, 0);
			OUT_RING  (chan, 0);
		} else {
			BEGIN_NV04(chan, NvSubCopy, 0x021c, 1);
			OUT_RING  (chan, 1);
		}

		BEGIN_NV04(chan, NvSubCopy, 0x0238, 2);
		OUT_RING  (chan, upper_32_bits(src_offset));
		OUT_RING  (chan, upper_32_bits(dst_offset));
		BEGIN_NV04(chan, NvSubCopy, 0x030c, 8);
		OUT_RING  (chan, lower_32_bits(src_offset));
		OUT_RING  (chan, lower_32_bits(dst_offset));
		OUT_RING  (chan, stride);
		OUT_RING  (chan, stride);
		OUT_RING  (chan, stride);
		OUT_RING  (chan, height);
		OUT_RING  (chan, 0x00000101);
		OUT_RING  (chan, 0x00000000);
		BEGIN_NV04(chan, NvSubCopy, NV_MEMORY_TO_MEMORY_FORMAT_NOP, 1);
		OUT_RING  (chan, 0);

		length -= amount;
		src_offset += amount;
		dst_offset += amount;
	}

	return 0;
}