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
struct venus_inst {int /*<<< orphan*/  lock; int /*<<< orphan*/  registeredbufs; scalar_t__ session_error; int /*<<< orphan*/  codec_state; struct venus_core* core; } ;
struct venus_core {scalar_t__ sys_error; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VENUS_DEC_STATE_DEINIT ; 
 int /*<<< orphan*/  hfi_session_abort (struct venus_inst*) ; 
 int hfi_session_deinit (struct venus_inst*) ; 
 int hfi_session_stop (struct venus_inst*) ; 
 int hfi_session_unload_res (struct venus_inst*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  venus_helper_free_dpb_bufs (struct venus_inst*) ; 
 int venus_helper_intbufs_free (struct venus_inst*) ; 
 int /*<<< orphan*/  venus_helper_load_scale_clocks (struct venus_core*) ; 
 int venus_helper_unregister_bufs (struct venus_inst*) ; 

__attribute__((used)) static void vdec_session_release(struct venus_inst *inst)
{
	struct venus_core *core = inst->core;
	int ret, abort = 0;

	mutex_lock(&inst->lock);

	inst->codec_state = VENUS_DEC_STATE_DEINIT;

	ret = hfi_session_stop(inst);
	abort = (ret && ret != -EINVAL) ? 1 : 0;
	ret = hfi_session_unload_res(inst);
	abort = (ret && ret != -EINVAL) ? 1 : 0;
	ret = venus_helper_unregister_bufs(inst);
	abort = (ret && ret != -EINVAL) ? 1 : 0;
	ret = venus_helper_intbufs_free(inst);
	abort = (ret && ret != -EINVAL) ? 1 : 0;
	ret = hfi_session_deinit(inst);
	abort = (ret && ret != -EINVAL) ? 1 : 0;

	if (inst->session_error || core->sys_error)
		abort = 1;

	if (abort)
		hfi_session_abort(inst);

	venus_helper_free_dpb_bufs(inst);
	venus_helper_load_scale_clocks(core);
	INIT_LIST_HEAD(&inst->registeredbufs);

	mutex_unlock(&inst->lock);
}