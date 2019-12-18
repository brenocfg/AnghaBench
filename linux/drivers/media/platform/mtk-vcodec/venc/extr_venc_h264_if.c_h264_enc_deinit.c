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
struct venc_h264_inst {scalar_t__ work_buf_allocated; int /*<<< orphan*/  vpu_inst; } ;

/* Variables and functions */
 int /*<<< orphan*/  h264_enc_free_work_buf (struct venc_h264_inst*) ; 
 int /*<<< orphan*/  kfree (struct venc_h264_inst*) ; 
 int /*<<< orphan*/  mtk_vcodec_debug_enter (struct venc_h264_inst*) ; 
 int /*<<< orphan*/  mtk_vcodec_debug_leave (struct venc_h264_inst*) ; 
 int vpu_enc_deinit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int h264_enc_deinit(void *handle)
{
	int ret = 0;
	struct venc_h264_inst *inst = (struct venc_h264_inst *)handle;

	mtk_vcodec_debug_enter(inst);

	ret = vpu_enc_deinit(&inst->vpu_inst);

	if (inst->work_buf_allocated)
		h264_enc_free_work_buf(inst);

	mtk_vcodec_debug_leave(inst);
	kfree(inst);

	return ret;
}