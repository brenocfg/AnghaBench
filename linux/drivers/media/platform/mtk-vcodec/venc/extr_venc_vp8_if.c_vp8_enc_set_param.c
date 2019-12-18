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
struct venc_vp8_inst {int ts_mode; int work_buf_allocated; int /*<<< orphan*/  vpu_inst; TYPE_2__* vsi; } ;
struct venc_enc_param {int /*<<< orphan*/  frm_rate; int /*<<< orphan*/  gop_size; int /*<<< orphan*/  buf_height; int /*<<< orphan*/  buf_width; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  bitrate; int /*<<< orphan*/  input_yuv_fmt; } ;
typedef  enum venc_set_param_type { ____Placeholder_venc_set_param_type } venc_set_param_type ;
struct TYPE_3__ {int ts_mode; int /*<<< orphan*/  framerate; int /*<<< orphan*/  gop_size; int /*<<< orphan*/  buf_h; int /*<<< orphan*/  buf_w; int /*<<< orphan*/  pic_h; int /*<<< orphan*/  pic_w; int /*<<< orphan*/  bitrate; int /*<<< orphan*/  input_fourcc; } ;
struct TYPE_4__ {TYPE_1__ config; } ;

/* Variables and functions */
#define  VENC_SET_PARAM_ENC 129 
#define  VENC_SET_PARAM_TS_MODE 128 
 int /*<<< orphan*/  mtk_vcodec_debug (struct venc_vp8_inst*,char*,...) ; 
 int /*<<< orphan*/  mtk_vcodec_debug_leave (struct venc_vp8_inst*) ; 
 int vp8_enc_alloc_work_buf (struct venc_vp8_inst*) ; 
 int /*<<< orphan*/  vp8_enc_free_work_buf (struct venc_vp8_inst*) ; 
 int vpu_enc_set_param (int /*<<< orphan*/ *,int,struct venc_enc_param*) ; 

__attribute__((used)) static int vp8_enc_set_param(void *handle,
			     enum venc_set_param_type type,
			     struct venc_enc_param *enc_prm)
{
	int ret = 0;
	struct venc_vp8_inst *inst = (struct venc_vp8_inst *)handle;

	mtk_vcodec_debug(inst, "->type=%d", type);

	switch (type) {
	case VENC_SET_PARAM_ENC:
		inst->vsi->config.input_fourcc = enc_prm->input_yuv_fmt;
		inst->vsi->config.bitrate = enc_prm->bitrate;
		inst->vsi->config.pic_w = enc_prm->width;
		inst->vsi->config.pic_h = enc_prm->height;
		inst->vsi->config.buf_w = enc_prm->buf_width;
		inst->vsi->config.buf_h = enc_prm->buf_height;
		inst->vsi->config.gop_size = enc_prm->gop_size;
		inst->vsi->config.framerate = enc_prm->frm_rate;
		inst->vsi->config.ts_mode = inst->ts_mode;
		ret = vpu_enc_set_param(&inst->vpu_inst, type, enc_prm);
		if (ret)
			break;
		if (inst->work_buf_allocated) {
			vp8_enc_free_work_buf(inst);
			inst->work_buf_allocated = false;
		}
		ret = vp8_enc_alloc_work_buf(inst);
		if (ret)
			break;
		inst->work_buf_allocated = true;
		break;

	/*
	 * VENC_SET_PARAM_TS_MODE must be called before VENC_SET_PARAM_ENC
	 */
	case VENC_SET_PARAM_TS_MODE:
		inst->ts_mode = 1;
		mtk_vcodec_debug(inst, "set ts_mode");
		break;

	default:
		ret = vpu_enc_set_param(&inst->vpu_inst, type, enc_prm);
		break;
	}

	mtk_vcodec_debug_leave(inst);

	return ret;
}