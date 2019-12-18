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
struct venus_inst {int codec_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFI_FLUSH_ALL ; 
 int /*<<< orphan*/  HFI_FLUSH_INPUT ; 
#define  VENUS_DEC_STATE_CAPTURE_SETUP 132 
#define  VENUS_DEC_STATE_DECODING 131 
#define  VENUS_DEC_STATE_DRAIN 130 
#define  VENUS_DEC_STATE_INIT 129 
 int VENUS_DEC_STATE_SEEK ; 
#define  VENUS_DEC_STATE_STOPPED 128 
 int hfi_session_flush (struct venus_inst*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vdec_stop_output(struct venus_inst *inst)
{
	int ret = 0;

	switch (inst->codec_state) {
	case VENUS_DEC_STATE_DECODING:
	case VENUS_DEC_STATE_DRAIN:
	case VENUS_DEC_STATE_STOPPED:
		ret = hfi_session_flush(inst, HFI_FLUSH_ALL);
		inst->codec_state = VENUS_DEC_STATE_SEEK;
		break;
	case VENUS_DEC_STATE_INIT:
	case VENUS_DEC_STATE_CAPTURE_SETUP:
		ret = hfi_session_flush(inst, HFI_FLUSH_INPUT);
		break;
	default:
		break;
	}

	return ret;
}