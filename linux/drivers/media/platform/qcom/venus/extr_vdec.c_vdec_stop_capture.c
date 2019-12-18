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
struct venus_inst {int codec_state; int /*<<< orphan*/  registeredbufs; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFI_FLUSH_ALL ; 
 int /*<<< orphan*/  HFI_FLUSH_OUTPUT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int VENUS_DEC_STATE_CAPTURE_SETUP ; 
#define  VENUS_DEC_STATE_DECODING 130 
#define  VENUS_DEC_STATE_DRAIN 129 
#define  VENUS_DEC_STATE_DRC 128 
 int VENUS_DEC_STATE_STOPPED ; 
 int hfi_session_flush (struct venus_inst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdec_cancel_dst_buffers (struct venus_inst*) ; 
 int /*<<< orphan*/  venus_helper_free_dpb_bufs (struct venus_inst*) ; 

__attribute__((used)) static int vdec_stop_capture(struct venus_inst *inst)
{
	int ret = 0;

	switch (inst->codec_state) {
	case VENUS_DEC_STATE_DECODING:
		ret = hfi_session_flush(inst, HFI_FLUSH_ALL);
		/* fallthrough */
	case VENUS_DEC_STATE_DRAIN:
		vdec_cancel_dst_buffers(inst);
		inst->codec_state = VENUS_DEC_STATE_STOPPED;
		break;
	case VENUS_DEC_STATE_DRC:
		ret = hfi_session_flush(inst, HFI_FLUSH_OUTPUT);
		vdec_cancel_dst_buffers(inst);
		inst->codec_state = VENUS_DEC_STATE_CAPTURE_SETUP;
		INIT_LIST_HEAD(&inst->registeredbufs);
		venus_helper_free_dpb_bufs(inst);
		break;
	default:
		return 0;
	}

	return ret;
}