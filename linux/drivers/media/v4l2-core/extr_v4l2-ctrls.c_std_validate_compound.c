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
union v4l2_ctrl_ptr {void* p; } ;
typedef  int u32 ;
struct v4l2_ctrl_vp8_frame_header {int /*<<< orphan*/  coder_state; int /*<<< orphan*/  entropy_header; int /*<<< orphan*/  quant_header; int /*<<< orphan*/  lf_header; int /*<<< orphan*/  segment_header; int /*<<< orphan*/  num_dct_parts; } ;
struct TYPE_4__ {int /*<<< orphan*/  picture_coding_type; int /*<<< orphan*/  picture_structure; int /*<<< orphan*/  intra_dc_precision; } ;
struct TYPE_3__ {int /*<<< orphan*/  chroma_format; } ;
struct v4l2_ctrl_mpeg2_slice_params {TYPE_2__ picture; TYPE_1__ sequence; } ;
struct v4l2_ctrl {int elem_size; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_CTRL_TYPE_FWHT_PARAMS 139 
#define  V4L2_CTRL_TYPE_H264_DECODE_PARAMS 138 
#define  V4L2_CTRL_TYPE_H264_PPS 137 
#define  V4L2_CTRL_TYPE_H264_SCALING_MATRIX 136 
#define  V4L2_CTRL_TYPE_H264_SLICE_PARAMS 135 
#define  V4L2_CTRL_TYPE_H264_SPS 134 
#define  V4L2_CTRL_TYPE_MPEG2_QUANTIZATION 133 
#define  V4L2_CTRL_TYPE_MPEG2_SLICE_PARAMS 132 
#define  V4L2_CTRL_TYPE_VP8_FRAME_HEADER 131 
#define  V4L2_MPEG2_PICTURE_CODING_TYPE_B 130 
#define  V4L2_MPEG2_PICTURE_CODING_TYPE_I 129 
#define  V4L2_MPEG2_PICTURE_CODING_TYPE_P 128 
 int /*<<< orphan*/  zero_padding (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int std_validate_compound(const struct v4l2_ctrl *ctrl, u32 idx,
				 union v4l2_ctrl_ptr ptr)
{
	struct v4l2_ctrl_mpeg2_slice_params *p_mpeg2_slice_params;
	struct v4l2_ctrl_vp8_frame_header *p_vp8_frame_header;
	void *p = ptr.p + idx * ctrl->elem_size;

	switch ((u32)ctrl->type) {
	case V4L2_CTRL_TYPE_MPEG2_SLICE_PARAMS:
		p_mpeg2_slice_params = p;

		switch (p_mpeg2_slice_params->sequence.chroma_format) {
		case 1: /* 4:2:0 */
		case 2: /* 4:2:2 */
		case 3: /* 4:4:4 */
			break;
		default:
			return -EINVAL;
		}

		switch (p_mpeg2_slice_params->picture.intra_dc_precision) {
		case 0: /* 8 bits */
		case 1: /* 9 bits */
		case 2: /* 10 bits */
		case 3: /* 11 bits */
			break;
		default:
			return -EINVAL;
		}

		switch (p_mpeg2_slice_params->picture.picture_structure) {
		case 1: /* interlaced top field */
		case 2: /* interlaced bottom field */
		case 3: /* progressive */
			break;
		default:
			return -EINVAL;
		}

		switch (p_mpeg2_slice_params->picture.picture_coding_type) {
		case V4L2_MPEG2_PICTURE_CODING_TYPE_I:
		case V4L2_MPEG2_PICTURE_CODING_TYPE_P:
		case V4L2_MPEG2_PICTURE_CODING_TYPE_B:
			break;
		default:
			return -EINVAL;
		}

		break;

	case V4L2_CTRL_TYPE_MPEG2_QUANTIZATION:
		break;

	case V4L2_CTRL_TYPE_FWHT_PARAMS:
		break;

	case V4L2_CTRL_TYPE_H264_SPS:
	case V4L2_CTRL_TYPE_H264_PPS:
	case V4L2_CTRL_TYPE_H264_SCALING_MATRIX:
	case V4L2_CTRL_TYPE_H264_SLICE_PARAMS:
	case V4L2_CTRL_TYPE_H264_DECODE_PARAMS:
		break;

	case V4L2_CTRL_TYPE_VP8_FRAME_HEADER:
		p_vp8_frame_header = p;

		switch (p_vp8_frame_header->num_dct_parts) {
		case 1:
		case 2:
		case 4:
		case 8:
			break;
		default:
			return -EINVAL;
		}
		zero_padding(p_vp8_frame_header->segment_header);
		zero_padding(p_vp8_frame_header->lf_header);
		zero_padding(p_vp8_frame_header->quant_header);
		zero_padding(p_vp8_frame_header->entropy_header);
		zero_padding(p_vp8_frame_header->coder_state);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}