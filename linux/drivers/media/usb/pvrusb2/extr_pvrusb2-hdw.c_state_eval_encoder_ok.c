#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pvr2_hdw {int state_encoder_ok; int flag_tripped; scalar_t__ pathway_state; TYPE_1__* hdw_desc; scalar_t__ state_usbstream_run; scalar_t__ state_decoder_run; scalar_t__ state_encoder_config; scalar_t__ state_encoder_run; } ;
struct TYPE_2__ {int /*<<< orphan*/  flag_digital_requires_cx23416; } ;

/* Variables and functions */
 scalar_t__ PVR2_PATHWAY_ANALOG ; 
 scalar_t__ PVR2_PATHWAY_DIGITAL ; 
 scalar_t__ pvr2_upload_firmware2 (struct pvr2_hdw*) ; 
 int /*<<< orphan*/  trace_stbit (char*,int) ; 

__attribute__((used)) static int state_eval_encoder_ok(struct pvr2_hdw *hdw)
{
	if (hdw->state_encoder_ok) return 0;
	if (hdw->flag_tripped) return 0;
	if (hdw->state_encoder_run) return 0;
	if (hdw->state_encoder_config) return 0;
	if (hdw->state_decoder_run) return 0;
	if (hdw->state_usbstream_run) return 0;
	if (hdw->pathway_state == PVR2_PATHWAY_DIGITAL) {
		if (!hdw->hdw_desc->flag_digital_requires_cx23416) return 0;
	} else if (hdw->pathway_state != PVR2_PATHWAY_ANALOG) {
		return 0;
	}

	if (pvr2_upload_firmware2(hdw) < 0) {
		hdw->flag_tripped = !0;
		trace_stbit("flag_tripped",hdw->flag_tripped);
		return !0;
	}
	hdw->state_encoder_ok = !0;
	trace_stbit("state_encoder_ok",hdw->state_encoder_ok);
	return !0;
}