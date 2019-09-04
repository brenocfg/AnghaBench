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
struct venc_vp8_inst {TYPE_1__* work_bufs; int /*<<< orphan*/  ctx; } ;
struct TYPE_2__ {scalar_t__ size; } ;

/* Variables and functions */
 int VENC_VP8_VPU_WORK_BUF_MAX ; 
 int /*<<< orphan*/  mtk_vcodec_debug_enter (struct venc_vp8_inst*) ; 
 int /*<<< orphan*/  mtk_vcodec_debug_leave (struct venc_vp8_inst*) ; 
 int /*<<< orphan*/  mtk_vcodec_mem_free (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void vp8_enc_free_work_buf(struct venc_vp8_inst *inst)
{
	int i;

	mtk_vcodec_debug_enter(inst);

	/* Buffers need to be freed by AP. */
	for (i = 0; i < VENC_VP8_VPU_WORK_BUF_MAX; i++) {
		if (inst->work_bufs[i].size == 0)
			continue;
		mtk_vcodec_mem_free(inst->ctx, &inst->work_bufs[i]);
	}

	mtk_vcodec_debug_leave(inst);
}