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
struct venus_inst {int streamon_out; int streamon_cap; int /*<<< orphan*/  lock; int /*<<< orphan*/  registeredbufs; scalar_t__ session_error; struct venus_core* core; } ;
struct venus_core {scalar_t__ sys_error; } ;
struct vb2_queue {scalar_t__ type; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE ; 
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 int /*<<< orphan*/  hfi_session_abort (struct venus_inst*) ; 
 int hfi_session_deinit (struct venus_inst*) ; 
 int hfi_session_stop (struct venus_inst*) ; 
 int hfi_session_unload_res (struct venus_inst*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct venus_inst* vb2_get_drv_priv (struct vb2_queue*) ; 
 int /*<<< orphan*/  venus_helper_buffers_done (struct venus_inst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  venus_helper_free_dpb_bufs (struct venus_inst*) ; 
 int venus_helper_intbufs_free (struct venus_inst*) ; 
 int /*<<< orphan*/  venus_helper_load_scale_clocks (struct venus_core*) ; 
 int venus_helper_unregister_bufs (struct venus_inst*) ; 

void venus_helper_vb2_stop_streaming(struct vb2_queue *q)
{
	struct venus_inst *inst = vb2_get_drv_priv(q);
	struct venus_core *core = inst->core;
	int ret;

	mutex_lock(&inst->lock);

	if (inst->streamon_out & inst->streamon_cap) {
		ret = hfi_session_stop(inst);
		ret |= hfi_session_unload_res(inst);
		ret |= venus_helper_unregister_bufs(inst);
		ret |= venus_helper_intbufs_free(inst);
		ret |= hfi_session_deinit(inst);

		if (inst->session_error || core->sys_error)
			ret = -EIO;

		if (ret)
			hfi_session_abort(inst);

		venus_helper_free_dpb_bufs(inst);

		venus_helper_load_scale_clocks(core);
		INIT_LIST_HEAD(&inst->registeredbufs);
	}

	venus_helper_buffers_done(inst, VB2_BUF_STATE_ERROR);

	if (q->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		inst->streamon_out = 0;
	else
		inst->streamon_cap = 0;

	mutex_unlock(&inst->lock);
}