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
struct venus_inst {int streamon_out; int streamon_cap; int /*<<< orphan*/  lock; int /*<<< orphan*/  num_output_bufs; int /*<<< orphan*/  num_input_bufs; scalar_t__ sequence_out; scalar_t__ sequence_cap; } ;
struct vb2_queue {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE ; 
 int /*<<< orphan*/  VB2_BUF_STATE_QUEUED ; 
 int /*<<< orphan*/  hfi_session_deinit (struct venus_inst*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct venus_inst* vb2_get_drv_priv (struct vb2_queue*) ; 
 int venc_init_session (struct venus_inst*) ; 
 int venc_set_properties (struct venus_inst*) ; 
 int venc_verify_conf (struct venus_inst*) ; 
 int /*<<< orphan*/  venus_helper_buffers_done (struct venus_inst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  venus_helper_init_instance (struct venus_inst*) ; 
 int venus_helper_set_num_bufs (struct venus_inst*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int venus_helper_vb2_start_streaming (struct venus_inst*) ; 

__attribute__((used)) static int venc_start_streaming(struct vb2_queue *q, unsigned int count)
{
	struct venus_inst *inst = vb2_get_drv_priv(q);
	int ret;

	mutex_lock(&inst->lock);

	if (q->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		inst->streamon_out = 1;
	else
		inst->streamon_cap = 1;

	if (!(inst->streamon_out & inst->streamon_cap)) {
		mutex_unlock(&inst->lock);
		return 0;
	}

	venus_helper_init_instance(inst);

	inst->sequence_cap = 0;
	inst->sequence_out = 0;

	ret = venc_init_session(inst);
	if (ret)
		goto bufs_done;

	ret = venc_set_properties(inst);
	if (ret)
		goto deinit_sess;

	ret = venc_verify_conf(inst);
	if (ret)
		goto deinit_sess;

	ret = venus_helper_set_num_bufs(inst, inst->num_input_bufs,
					inst->num_output_bufs, 0);
	if (ret)
		goto deinit_sess;

	ret = venus_helper_vb2_start_streaming(inst);
	if (ret)
		goto deinit_sess;

	mutex_unlock(&inst->lock);

	return 0;

deinit_sess:
	hfi_session_deinit(inst);
bufs_done:
	venus_helper_buffers_done(inst, VB2_BUF_STATE_QUEUED);
	if (q->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		inst->streamon_out = 0;
	else
		inst->streamon_cap = 0;
	mutex_unlock(&inst->lock);
	return ret;
}