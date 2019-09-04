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
struct venus_inst {unsigned int input_buf_size; } ;
struct vb2_buffer {scalar_t__ type; int /*<<< orphan*/  vb2_queue; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE ; 
 struct venus_inst* vb2_get_drv_priv (int /*<<< orphan*/ ) ; 
 unsigned int vb2_plane_size (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 unsigned int venus_helper_get_opb_size (struct venus_inst*) ; 

int venus_helper_vb2_buf_prepare(struct vb2_buffer *vb)
{
	struct venus_inst *inst = vb2_get_drv_priv(vb->vb2_queue);
	unsigned int out_buf_size = venus_helper_get_opb_size(inst);

	if (vb->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE &&
	    vb2_plane_size(vb, 0) < out_buf_size)
		return -EINVAL;
	if (vb->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE &&
	    vb2_plane_size(vb, 0) < inst->input_buf_size)
		return -EINVAL;

	return 0;
}