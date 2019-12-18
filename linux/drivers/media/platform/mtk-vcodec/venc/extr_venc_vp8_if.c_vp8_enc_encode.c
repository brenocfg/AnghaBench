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
struct TYPE_3__ {int /*<<< orphan*/  is_key_frm; } ;
struct venc_vp8_inst {TYPE_1__ vpu_inst; struct mtk_vcodec_ctx* ctx; } ;
struct venc_frm_buf {int dummy; } ;
struct venc_done_result {int /*<<< orphan*/  is_key_frm; int /*<<< orphan*/  bs_size; } ;
struct mtk_vcodec_mem {int dummy; } ;
struct mtk_vcodec_ctx {TYPE_2__* dev; } ;
typedef  enum venc_start_opt { ____Placeholder_venc_start_opt } venc_start_opt ;
struct TYPE_4__ {int /*<<< orphan*/  enc_lt_irq; } ;

/* Variables and functions */
 int EINVAL ; 
#define  VENC_START_OPT_ENCODE_FRAME 128 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_vcodec_debug_enter (struct venc_vp8_inst*) ; 
 int /*<<< orphan*/  mtk_vcodec_debug_leave (struct venc_vp8_inst*) ; 
 int /*<<< orphan*/  mtk_vcodec_err (struct venc_vp8_inst*,char*,int) ; 
 int vp8_enc_encode_frame (struct venc_vp8_inst*,struct venc_frm_buf*,struct mtk_vcodec_mem*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vp8_enc_encode(void *handle,
			  enum venc_start_opt opt,
			  struct venc_frm_buf *frm_buf,
			  struct mtk_vcodec_mem *bs_buf,
			  struct venc_done_result *result)
{
	int ret = 0;
	struct venc_vp8_inst *inst = (struct venc_vp8_inst *)handle;
	struct mtk_vcodec_ctx *ctx = inst->ctx;

	mtk_vcodec_debug_enter(inst);

	enable_irq(ctx->dev->enc_lt_irq);

	switch (opt) {
	case VENC_START_OPT_ENCODE_FRAME:
		ret = vp8_enc_encode_frame(inst, frm_buf, bs_buf,
					   &result->bs_size);
		if (ret)
			goto encode_err;
		result->is_key_frm = inst->vpu_inst.is_key_frm;
		break;

	default:
		mtk_vcodec_err(inst, "opt not support:%d", opt);
		ret = -EINVAL;
		break;
	}

encode_err:

	disable_irq(ctx->dev->enc_lt_irq);
	mtk_vcodec_debug_leave(inst);

	return ret;
}