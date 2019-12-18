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
struct venus_inst {struct v4l2_m2m_ctx* m2m_ctx; } ;
struct TYPE_2__ {scalar_t__ type; } ;
struct vb2_v4l2_buffer {TYPE_1__ vb2_buf; } ;
struct v4l2_m2m_ctx {int dummy; } ;

/* Variables and functions */
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE ; 
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 int /*<<< orphan*/  v4l2_m2m_buf_done (struct vb2_v4l2_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_dst_buf_remove_by_buf (struct v4l2_m2m_ctx*,struct vb2_v4l2_buffer*) ; 
 int /*<<< orphan*/  v4l2_m2m_src_buf_remove_by_buf (struct v4l2_m2m_ctx*,struct vb2_v4l2_buffer*) ; 

__attribute__((used)) static void return_buf_error(struct venus_inst *inst,
			     struct vb2_v4l2_buffer *vbuf)
{
	struct v4l2_m2m_ctx *m2m_ctx = inst->m2m_ctx;

	if (vbuf->vb2_buf.type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		v4l2_m2m_src_buf_remove_by_buf(m2m_ctx, vbuf);
	else
		v4l2_m2m_dst_buf_remove_by_buf(m2m_ctx, vbuf);

	v4l2_m2m_buf_done(vbuf, VB2_BUF_STATE_ERROR);
}