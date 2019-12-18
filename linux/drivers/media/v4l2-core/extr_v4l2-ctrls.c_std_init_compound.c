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
struct TYPE_4__ {int picture_structure; int /*<<< orphan*/  picture_coding_type; } ;
struct TYPE_3__ {int chroma_format; } ;
struct v4l2_ctrl_mpeg2_slice_params {TYPE_2__ picture; TYPE_1__ sequence; } ;
struct v4l2_ctrl {int elem_size; int /*<<< orphan*/  type; } ;

/* Variables and functions */
#define  V4L2_CTRL_TYPE_MPEG2_SLICE_PARAMS 128 
 int /*<<< orphan*/  V4L2_MPEG2_PICTURE_CODING_TYPE_I ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void std_init_compound(const struct v4l2_ctrl *ctrl, u32 idx,
			      union v4l2_ctrl_ptr ptr)
{
	struct v4l2_ctrl_mpeg2_slice_params *p_mpeg2_slice_params;
	void *p = ptr.p + idx * ctrl->elem_size;

	memset(p, 0, ctrl->elem_size);

	/*
	 * The cast is needed to get rid of a gcc warning complaining that
	 * V4L2_CTRL_TYPE_MPEG2_SLICE_PARAMS is not part of the
	 * v4l2_ctrl_type enum.
	 */
	switch ((u32)ctrl->type) {
	case V4L2_CTRL_TYPE_MPEG2_SLICE_PARAMS:
		p_mpeg2_slice_params = p;
		/* 4:2:0 */
		p_mpeg2_slice_params->sequence.chroma_format = 1;
		/* interlaced top field */
		p_mpeg2_slice_params->picture.picture_structure = 1;
		p_mpeg2_slice_params->picture.picture_coding_type =
					V4L2_MPEG2_PICTURE_CODING_TYPE_I;
		break;
	}
}