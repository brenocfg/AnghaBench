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
struct TYPE_4__ {int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  size; } ;
struct vdec_h264_inst {TYPE_2__ pred_buf; TYPE_1__* vsi; int /*<<< orphan*/  ctx; } ;
struct TYPE_3__ {int /*<<< orphan*/  pred_buf_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_PREDICTION_SZ ; 
 int /*<<< orphan*/  mtk_vcodec_err (struct vdec_h264_inst*,char*) ; 
 int mtk_vcodec_mem_alloc (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static int allocate_predication_buf(struct vdec_h264_inst *inst)
{
	int err = 0;

	inst->pred_buf.size = BUF_PREDICTION_SZ;
	err = mtk_vcodec_mem_alloc(inst->ctx, &inst->pred_buf);
	if (err) {
		mtk_vcodec_err(inst, "failed to allocate ppl buf");
		return err;
	}

	inst->vsi->pred_buf_dma = inst->pred_buf.dma_addr;
	return 0;
}