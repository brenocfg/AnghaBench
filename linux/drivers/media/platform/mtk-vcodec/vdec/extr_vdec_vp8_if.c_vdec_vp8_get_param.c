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
struct vdec_vp8_inst {int dummy; } ;
typedef  enum vdec_get_param_type { ____Placeholder_vdec_get_param_type } vdec_get_param_type ;

/* Variables and functions */
 int EINVAL ; 
#define  GET_PARAM_CROP_INFO 132 
#define  GET_PARAM_DISP_FRAME_BUFFER 131 
#define  GET_PARAM_DPB_SIZE 130 
#define  GET_PARAM_FREE_FRAME_BUFFER 129 
#define  GET_PARAM_PIC_INFO 128 
 unsigned int VP8_DPB_SIZE ; 
 int /*<<< orphan*/  get_crop_info (struct vdec_vp8_inst*,void*) ; 
 int /*<<< orphan*/  get_disp_fb (struct vdec_vp8_inst*,void*) ; 
 int /*<<< orphan*/  get_free_fb (struct vdec_vp8_inst*,void*) ; 
 int /*<<< orphan*/  get_pic_info (struct vdec_vp8_inst*,void*) ; 
 int /*<<< orphan*/  mtk_vcodec_err (struct vdec_vp8_inst*,char*,int) ; 

__attribute__((used)) static int vdec_vp8_get_param(void *h_vdec, enum vdec_get_param_type type,
			      void *out)
{
	struct vdec_vp8_inst *inst = (struct vdec_vp8_inst *)h_vdec;

	switch (type) {
	case GET_PARAM_DISP_FRAME_BUFFER:
		get_disp_fb(inst, out);
		break;

	case GET_PARAM_FREE_FRAME_BUFFER:
		get_free_fb(inst, out);
		break;

	case GET_PARAM_PIC_INFO:
		get_pic_info(inst, out);
		break;

	case GET_PARAM_CROP_INFO:
		get_crop_info(inst, out);
		break;

	case GET_PARAM_DPB_SIZE:
		*((unsigned int *)out) = VP8_DPB_SIZE;
		break;

	default:
		mtk_vcodec_err(inst, "invalid get parameter type=%d", type);
		return -EINVAL;
	}

	return 0;
}