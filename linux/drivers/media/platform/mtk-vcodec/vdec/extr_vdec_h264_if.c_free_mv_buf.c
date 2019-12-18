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
struct vdec_h264_inst {int /*<<< orphan*/  ctx; struct mtk_vcodec_mem* mv_buf; TYPE_1__* vsi; } ;
struct mtk_vcodec_mem {scalar_t__ va; } ;
struct TYPE_2__ {scalar_t__* mv_buf_dma; } ;

/* Variables and functions */
 int H264_MAX_FB_NUM ; 
 int /*<<< orphan*/  mtk_vcodec_mem_free (int /*<<< orphan*/ ,struct mtk_vcodec_mem*) ; 

__attribute__((used)) static void free_mv_buf(struct vdec_h264_inst *inst)
{
	int i;
	struct mtk_vcodec_mem *mem = NULL;

	for (i = 0; i < H264_MAX_FB_NUM; i++) {
		inst->vsi->mv_buf_dma[i] = 0;
		mem = &inst->mv_buf[i];
		if (mem->va)
			mtk_vcodec_mem_free(inst->ctx, mem);
	}
}