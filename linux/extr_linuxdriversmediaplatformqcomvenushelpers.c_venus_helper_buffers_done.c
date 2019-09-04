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
struct venus_inst {int /*<<< orphan*/  m2m_ctx; } ;
struct vb2_v4l2_buffer {int dummy; } ;
typedef  enum vb2_buffer_state { ____Placeholder_vb2_buffer_state } vb2_buffer_state ;

/* Variables and functions */
 int /*<<< orphan*/  v4l2_m2m_buf_done (struct vb2_v4l2_buffer*,int) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_dst_buf_remove (int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_src_buf_remove (int /*<<< orphan*/ ) ; 

void venus_helper_buffers_done(struct venus_inst *inst,
			       enum vb2_buffer_state state)
{
	struct vb2_v4l2_buffer *buf;

	while ((buf = v4l2_m2m_src_buf_remove(inst->m2m_ctx)))
		v4l2_m2m_buf_done(buf, state);
	while ((buf = v4l2_m2m_dst_buf_remove(inst->m2m_ctx)))
		v4l2_m2m_buf_done(buf, state);
}