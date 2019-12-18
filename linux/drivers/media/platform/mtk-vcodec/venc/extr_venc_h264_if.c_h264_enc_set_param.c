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
struct venc_h264_inst {int work_buf_allocated; int prepend_hdr; int /*<<< orphan*/  vpu_inst; TYPE_2__* vsi; } ;
struct venc_enc_param {int /*<<< orphan*/  h264_level; int /*<<< orphan*/  h264_profile; int /*<<< orphan*/  intra_period; int /*<<< orphan*/  frm_rate; int /*<<< orphan*/  gop_size; int /*<<< orphan*/  buf_height; int /*<<< orphan*/  buf_width; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  bitrate; int /*<<< orphan*/  input_yuv_fmt; } ;
typedef  enum venc_set_param_type { ____Placeholder_venc_set_param_type } venc_set_param_type ;
struct TYPE_3__ {int /*<<< orphan*/  wfd; int /*<<< orphan*/  level; int /*<<< orphan*/  profile; int /*<<< orphan*/  intra_period; int /*<<< orphan*/  framerate; int /*<<< orphan*/  gop_size; int /*<<< orphan*/  buf_h; int /*<<< orphan*/  buf_w; int /*<<< orphan*/  pic_h; int /*<<< orphan*/  pic_w; int /*<<< orphan*/  bitrate; int /*<<< orphan*/  input_fourcc; } ;
struct TYPE_4__ {TYPE_1__ config; } ;

/* Variables and functions */
#define  VENC_SET_PARAM_ENC 129 
#define  VENC_SET_PARAM_PREPEND_HEADER 128 
 int h264_enc_alloc_work_buf (struct venc_h264_inst*) ; 
 int /*<<< orphan*/  h264_enc_free_work_buf (struct venc_h264_inst*) ; 
 int /*<<< orphan*/  h264_get_level (struct venc_h264_inst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h264_get_profile (struct venc_h264_inst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_vcodec_debug (struct venc_h264_inst*,char*,...) ; 
 int /*<<< orphan*/  mtk_vcodec_debug_leave (struct venc_h264_inst*) ; 
 int vpu_enc_set_param (int /*<<< orphan*/ *,int,struct venc_enc_param*) ; 

__attribute__((used)) static int h264_enc_set_param(void *handle,
			      enum venc_set_param_type type,
			      struct venc_enc_param *enc_prm)
{
	int ret = 0;
	struct venc_h264_inst *inst = (struct venc_h264_inst *)handle;

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
		inst->vsi->config.intra_period = enc_prm->intra_period;
		inst->vsi->config.profile =
			h264_get_profile(inst, enc_prm->h264_profile);
		inst->vsi->config.level =
			h264_get_level(inst, enc_prm->h264_level);
		inst->vsi->config.wfd = 0;
		ret = vpu_enc_set_param(&inst->vpu_inst, type, enc_prm);
		if (ret)
			break;
		if (inst->work_buf_allocated) {
			h264_enc_free_work_buf(inst);
			inst->work_buf_allocated = false;
		}
		ret = h264_enc_alloc_work_buf(inst);
		if (ret)
			break;
		inst->work_buf_allocated = true;
		break;

	case VENC_SET_PARAM_PREPEND_HEADER:
		inst->prepend_hdr = 1;
		mtk_vcodec_debug(inst, "set prepend header mode");
		break;

	default:
		ret = vpu_enc_set_param(&inst->vpu_inst, type, enc_prm);
		break;
	}

	mtk_vcodec_debug_leave(inst);

	return ret;
}