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
struct venc_vpu_inst {int /*<<< orphan*/  inst_addr; } ;
struct venc_enc_param {int /*<<< orphan*/  intra_period; int /*<<< orphan*/  gop_size; int /*<<< orphan*/  frm_rate; int /*<<< orphan*/  bitrate; } ;
struct venc_ap_ipi_msg_set_param {int param_id; int data_item; int /*<<< orphan*/ * data; int /*<<< orphan*/  vpu_inst_addr; int /*<<< orphan*/  msg_id; } ;
typedef  int /*<<< orphan*/  out ;
typedef  enum venc_set_param_type { ____Placeholder_venc_set_param_type } venc_set_param_type ;

/* Variables and functions */
 int /*<<< orphan*/  AP_IPIMSG_ENC_SET_PARAM ; 
 int EINVAL ; 
#define  VENC_SET_PARAM_ADJUST_BITRATE 134 
#define  VENC_SET_PARAM_ADJUST_FRAMERATE 133 
#define  VENC_SET_PARAM_ENC 132 
#define  VENC_SET_PARAM_FORCE_INTRA 131 
#define  VENC_SET_PARAM_GOP_SIZE 130 
#define  VENC_SET_PARAM_INTRA_PERIOD 129 
#define  VENC_SET_PARAM_SKIP_FRAME 128 
 int /*<<< orphan*/  memset (struct venc_ap_ipi_msg_set_param*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtk_vcodec_debug (struct venc_vpu_inst*,char*,int) ; 
 int /*<<< orphan*/  mtk_vcodec_err (struct venc_vpu_inst*,char*,int) ; 
 scalar_t__ vpu_enc_send_msg (struct venc_vpu_inst*,struct venc_ap_ipi_msg_set_param*,int) ; 

int vpu_enc_set_param(struct venc_vpu_inst *vpu,
		      enum venc_set_param_type id,
		      struct venc_enc_param *enc_param)
{
	struct venc_ap_ipi_msg_set_param out;

	mtk_vcodec_debug(vpu, "id %d ->", id);

	memset(&out, 0, sizeof(out));
	out.msg_id = AP_IPIMSG_ENC_SET_PARAM;
	out.vpu_inst_addr = vpu->inst_addr;
	out.param_id = id;
	switch (id) {
	case VENC_SET_PARAM_ENC:
		out.data_item = 0;
		break;
	case VENC_SET_PARAM_FORCE_INTRA:
		out.data_item = 0;
		break;
	case VENC_SET_PARAM_ADJUST_BITRATE:
		out.data_item = 1;
		out.data[0] = enc_param->bitrate;
		break;
	case VENC_SET_PARAM_ADJUST_FRAMERATE:
		out.data_item = 1;
		out.data[0] = enc_param->frm_rate;
		break;
	case VENC_SET_PARAM_GOP_SIZE:
		out.data_item = 1;
		out.data[0] = enc_param->gop_size;
		break;
	case VENC_SET_PARAM_INTRA_PERIOD:
		out.data_item = 1;
		out.data[0] = enc_param->intra_period;
		break;
	case VENC_SET_PARAM_SKIP_FRAME:
		out.data_item = 0;
		break;
	default:
		mtk_vcodec_err(vpu, "id %d not supported", id);
		return -EINVAL;
	}
	if (vpu_enc_send_msg(vpu, &out, sizeof(out))) {
		mtk_vcodec_err(vpu,
			       "AP_IPIMSG_ENC_SET_PARAM %d fail", id);
		return -EINVAL;
	}

	mtk_vcodec_debug(vpu, "id %d <-", id);

	return 0;
}