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
struct venus_inst {scalar_t__ session_type; int /*<<< orphan*/  lock; scalar_t__ streamon_cap; scalar_t__ streamon_out; struct v4l2_m2m_ctx* m2m_ctx; } ;
struct vb2_v4l2_buffer {int dummy; } ;
struct vb2_buffer {int /*<<< orphan*/  vb2_queue; } ;
struct v4l2_m2m_ctx {int dummy; } ;

/* Variables and functions */
 scalar_t__ VIDC_SESSION_TYPE_ENC ; 
 int is_buf_refed (struct venus_inst*,struct vb2_v4l2_buffer*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  return_buf_error (struct venus_inst*,struct vb2_v4l2_buffer*) ; 
 int session_process_buf (struct venus_inst*,struct vb2_v4l2_buffer*) ; 
 struct vb2_v4l2_buffer* to_vb2_v4l2_buffer (struct vb2_buffer*) ; 
 int /*<<< orphan*/  v4l2_m2m_buf_queue (struct v4l2_m2m_ctx*,struct vb2_v4l2_buffer*) ; 
 struct venus_inst* vb2_get_drv_priv (int /*<<< orphan*/ ) ; 
 scalar_t__ vb2_start_streaming_called (int /*<<< orphan*/ ) ; 

void venus_helper_vb2_buf_queue(struct vb2_buffer *vb)
{
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	struct venus_inst *inst = vb2_get_drv_priv(vb->vb2_queue);
	struct v4l2_m2m_ctx *m2m_ctx = inst->m2m_ctx;
	int ret;

	mutex_lock(&inst->lock);

	v4l2_m2m_buf_queue(m2m_ctx, vbuf);

	if (inst->session_type == VIDC_SESSION_TYPE_ENC &&
	    !(inst->streamon_out && inst->streamon_cap))
		goto unlock;

	if (vb2_start_streaming_called(vb->vb2_queue)) {
		ret = is_buf_refed(inst, vbuf);
		if (ret)
			goto unlock;

		ret = session_process_buf(inst, vbuf);
		if (ret)
			return_buf_error(inst, vbuf);
	}

unlock:
	mutex_unlock(&inst->lock);
}