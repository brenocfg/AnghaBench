#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct ttm_mem_reg {int start; int num_pages; } ;
struct ttm_buffer_object {int dummy; } ;
struct nouveau_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEGIN_NV04 (struct nouveau_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NV_MEMORY_TO_MEMORY_FORMAT_DMA_SOURCE ; 
 int /*<<< orphan*/  NV_MEMORY_TO_MEMORY_FORMAT_NOP ; 
 int /*<<< orphan*/  NV_MEMORY_TO_MEMORY_FORMAT_OFFSET_IN ; 
 int /*<<< orphan*/  NvSubCopy ; 
 int /*<<< orphan*/  OUT_RING (struct nouveau_channel*,int) ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int RING_SPACE (struct nouveau_channel*,int) ; 
 int nouveau_bo_mem_ctxdma (struct ttm_buffer_object*,struct nouveau_channel*,struct ttm_mem_reg*) ; 

__attribute__((used)) static int
nv04_bo_move_m2mf(struct nouveau_channel *chan, struct ttm_buffer_object *bo,
		  struct ttm_mem_reg *old_reg, struct ttm_mem_reg *new_reg)
{
	u32 src_offset = old_reg->start << PAGE_SHIFT;
	u32 dst_offset = new_reg->start << PAGE_SHIFT;
	u32 page_count = new_reg->num_pages;
	int ret;

	ret = RING_SPACE(chan, 3);
	if (ret)
		return ret;

	BEGIN_NV04(chan, NvSubCopy, NV_MEMORY_TO_MEMORY_FORMAT_DMA_SOURCE, 2);
	OUT_RING  (chan, nouveau_bo_mem_ctxdma(bo, chan, old_reg));
	OUT_RING  (chan, nouveau_bo_mem_ctxdma(bo, chan, new_reg));

	page_count = new_reg->num_pages;
	while (page_count) {
		int line_count = (page_count > 2047) ? 2047 : page_count;

		ret = RING_SPACE(chan, 11);
		if (ret)
			return ret;

		BEGIN_NV04(chan, NvSubCopy,
				 NV_MEMORY_TO_MEMORY_FORMAT_OFFSET_IN, 8);
		OUT_RING  (chan, src_offset);
		OUT_RING  (chan, dst_offset);
		OUT_RING  (chan, PAGE_SIZE); /* src_pitch */
		OUT_RING  (chan, PAGE_SIZE); /* dst_pitch */
		OUT_RING  (chan, PAGE_SIZE); /* line_length */
		OUT_RING  (chan, line_count);
		OUT_RING  (chan, 0x00000101);
		OUT_RING  (chan, 0x00000000);
		BEGIN_NV04(chan, NvSubCopy, NV_MEMORY_TO_MEMORY_FORMAT_NOP, 1);
		OUT_RING  (chan, 0);

		page_count -= line_count;
		src_offset += (PAGE_SIZE * line_count);
		dst_offset += (PAGE_SIZE * line_count);
	}

	return 0;
}