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
struct venc_h264_inst {int /*<<< orphan*/  pps_buf; int /*<<< orphan*/  ctx; int /*<<< orphan*/ * work_bufs; } ;

/* Variables and functions */
 int VENC_H264_VPU_WORK_BUF_MAX ; 
 int VENC_H264_VPU_WORK_BUF_SKIP_FRAME ; 
 int /*<<< orphan*/  mtk_vcodec_debug_enter (struct venc_h264_inst*) ; 
 int /*<<< orphan*/  mtk_vcodec_debug_leave (struct venc_h264_inst*) ; 
 int /*<<< orphan*/  mtk_vcodec_mem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void h264_enc_free_work_buf(struct venc_h264_inst *inst)
{
	int i;

	mtk_vcodec_debug_enter(inst);

	/* Except the SKIP_FRAME buffers,
	 * other buffers need to be freed by AP.
	 */
	for (i = 0; i < VENC_H264_VPU_WORK_BUF_MAX; i++) {
		if (i != VENC_H264_VPU_WORK_BUF_SKIP_FRAME)
			mtk_vcodec_mem_free(inst->ctx, &inst->work_bufs[i]);
	}

	mtk_vcodec_mem_free(inst->ctx, &inst->pps_buf);

	mtk_vcodec_debug_leave(inst);
}