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
struct mtk_vcodec_mem {scalar_t__ va; } ;
struct vdec_h264_inst {int /*<<< orphan*/  ctx; struct mtk_vcodec_mem pred_buf; TYPE_1__* vsi; } ;
struct TYPE_2__ {scalar_t__ pred_buf_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtk_vcodec_debug_enter (struct vdec_h264_inst*) ; 
 int /*<<< orphan*/  mtk_vcodec_mem_free (int /*<<< orphan*/ ,struct mtk_vcodec_mem*) ; 

__attribute__((used)) static void free_predication_buf(struct vdec_h264_inst *inst)
{
	struct mtk_vcodec_mem *mem = NULL;

	mtk_vcodec_debug_enter(inst);

	inst->vsi->pred_buf_dma = 0;
	mem = &inst->pred_buf;
	if (mem->va)
		mtk_vcodec_mem_free(inst->ctx, mem);
}