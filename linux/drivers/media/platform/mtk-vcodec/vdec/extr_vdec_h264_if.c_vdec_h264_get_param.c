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
struct vdec_h264_inst {TYPE_1__* vsi; } ;
typedef  enum vdec_get_param_type { ____Placeholder_vdec_get_param_type } vdec_get_param_type ;
struct TYPE_2__ {int /*<<< orphan*/  list_free; int /*<<< orphan*/  list_disp; } ;

/* Variables and functions */
 int EINVAL ; 
#define  GET_PARAM_CROP_INFO 132 
#define  GET_PARAM_DISP_FRAME_BUFFER 131 
#define  GET_PARAM_DPB_SIZE 130 
#define  GET_PARAM_FREE_FRAME_BUFFER 129 
#define  GET_PARAM_PIC_INFO 128 
 int /*<<< orphan*/  get_crop_info (struct vdec_h264_inst*,void*) ; 
 int /*<<< orphan*/  get_dpb_size (struct vdec_h264_inst*,void*) ; 
 int /*<<< orphan*/  get_pic_info (struct vdec_h264_inst*,void*) ; 
 int /*<<< orphan*/  mtk_vcodec_err (struct vdec_h264_inst*,char*,int) ; 
 int /*<<< orphan*/  vdec_h264_get_fb (struct vdec_h264_inst*,int /*<<< orphan*/ *,int,void*) ; 

__attribute__((used)) static int vdec_h264_get_param(void *h_vdec, enum vdec_get_param_type type,
			       void *out)
{
	struct vdec_h264_inst *inst = (struct vdec_h264_inst *)h_vdec;

	switch (type) {
	case GET_PARAM_DISP_FRAME_BUFFER:
		vdec_h264_get_fb(inst, &inst->vsi->list_disp, true, out);
		break;

	case GET_PARAM_FREE_FRAME_BUFFER:
		vdec_h264_get_fb(inst, &inst->vsi->list_free, false, out);
		break;

	case GET_PARAM_PIC_INFO:
		get_pic_info(inst, out);
		break;

	case GET_PARAM_DPB_SIZE:
		get_dpb_size(inst, out);
		break;

	case GET_PARAM_CROP_INFO:
		get_crop_info(inst, out);
		break;

	default:
		mtk_vcodec_err(inst, "invalid get parameter type=%d", type);
		return -EINVAL;
	}

	return 0;
}