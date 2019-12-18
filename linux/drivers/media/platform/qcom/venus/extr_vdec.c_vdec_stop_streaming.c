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
struct venus_inst {int /*<<< orphan*/  lock; scalar_t__ streamon_cap; scalar_t__ streamon_out; } ;
struct vb2_queue {scalar_t__ type; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE ; 
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct venus_inst* vb2_get_drv_priv (struct vb2_queue*) ; 
 int vdec_stop_capture (struct venus_inst*) ; 
 int vdec_stop_output (struct venus_inst*) ; 
 int /*<<< orphan*/  venus_helper_buffers_done (struct venus_inst*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vdec_stop_streaming(struct vb2_queue *q)
{
	struct venus_inst *inst = vb2_get_drv_priv(q);
	int ret = -EINVAL;

	mutex_lock(&inst->lock);

	if (q->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
		ret = vdec_stop_capture(inst);
	else
		ret = vdec_stop_output(inst);

	venus_helper_buffers_done(inst, VB2_BUF_STATE_ERROR);

	if (ret)
		goto unlock;

	if (q->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		inst->streamon_out = 0;
	else
		inst->streamon_cap = 0;

unlock:
	mutex_unlock(&inst->lock);
}