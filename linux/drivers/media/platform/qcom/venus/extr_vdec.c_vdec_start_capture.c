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
struct venus_inst {scalar_t__ codec_state; int reconfig; int streamon_cap; scalar_t__ sequence_cap; int /*<<< orphan*/  core; int /*<<< orphan*/  num_input_bufs; int /*<<< orphan*/  streamon_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFI_FLUSH_OUTPUT ; 
 int /*<<< orphan*/  VB2_MAX_FRAME ; 
 scalar_t__ VENUS_DEC_STATE_DECODING ; 
 scalar_t__ VENUS_DEC_STATE_STOPPED ; 
 int hfi_session_continue (struct venus_inst*) ; 
 int hfi_session_flush (struct venus_inst*,int /*<<< orphan*/ ) ; 
 int vdec_output_conf (struct venus_inst*) ; 
 int venus_helper_alloc_dpb_bufs (struct venus_inst*) ; 
 int /*<<< orphan*/  venus_helper_free_dpb_bufs (struct venus_inst*) ; 
 int venus_helper_intbufs_realloc (struct venus_inst*) ; 
 int /*<<< orphan*/  venus_helper_load_scale_clocks (int /*<<< orphan*/ ) ; 
 int venus_helper_process_initial_cap_bufs (struct venus_inst*) ; 
 int venus_helper_queue_dpb_bufs (struct venus_inst*) ; 
 int venus_helper_set_num_bufs (struct venus_inst*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vdec_start_capture(struct venus_inst *inst)
{
	int ret;

	if (!inst->streamon_out)
		return 0;

	if (inst->codec_state == VENUS_DEC_STATE_DECODING) {
		if (inst->reconfig)
			goto reconfigure;

		venus_helper_queue_dpb_bufs(inst);
		venus_helper_process_initial_cap_bufs(inst);
		inst->streamon_cap = 1;
		return 0;
	}

	if (inst->codec_state != VENUS_DEC_STATE_STOPPED)
		return 0;

reconfigure:
	ret = hfi_session_flush(inst, HFI_FLUSH_OUTPUT);
	if (ret)
		return ret;

	ret = vdec_output_conf(inst);
	if (ret)
		return ret;

	ret = venus_helper_set_num_bufs(inst, inst->num_input_bufs,
					VB2_MAX_FRAME, VB2_MAX_FRAME);
	if (ret)
		return ret;

	ret = venus_helper_intbufs_realloc(inst);
	if (ret)
		goto err;

	ret = venus_helper_alloc_dpb_bufs(inst);
	if (ret)
		goto err;

	ret = venus_helper_queue_dpb_bufs(inst);
	if (ret)
		goto free_dpb_bufs;

	ret = venus_helper_process_initial_cap_bufs(inst);
	if (ret)
		goto free_dpb_bufs;

	venus_helper_load_scale_clocks(inst->core);

	ret = hfi_session_continue(inst);
	if (ret)
		goto free_dpb_bufs;

	inst->codec_state = VENUS_DEC_STATE_DECODING;

	inst->streamon_cap = 1;
	inst->sequence_cap = 0;
	inst->reconfig = false;

	return 0;

free_dpb_bufs:
	venus_helper_free_dpb_bufs(inst);
err:
	return ret;
}