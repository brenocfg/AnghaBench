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
struct venus_inst {int /*<<< orphan*/  lock; } ;
struct vb2_queue {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE ; 
 int /*<<< orphan*/  VB2_BUF_STATE_QUEUED ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct venus_inst* vb2_get_drv_priv (struct vb2_queue*) ; 
 int vdec_start_capture (struct venus_inst*) ; 
 int vdec_start_output (struct venus_inst*) ; 
 int /*<<< orphan*/  venus_helper_buffers_done (struct venus_inst*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vdec_start_streaming(struct vb2_queue *q, unsigned int count)
{
	struct venus_inst *inst = vb2_get_drv_priv(q);
	int ret;

	mutex_lock(&inst->lock);

	if (q->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
		ret = vdec_start_capture(inst);
	else
		ret = vdec_start_output(inst);

	if (ret)
		goto error;

	mutex_unlock(&inst->lock);
	return 0;

error:
	venus_helper_buffers_done(inst, VB2_BUF_STATE_QUEUED);
	mutex_unlock(&inst->lock);
	return ret;
}