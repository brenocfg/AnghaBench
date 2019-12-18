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
struct pvr2_hdw {int pathway_state; int /*<<< orphan*/  state_encoder_runok; TYPE_1__* hdw_desc; int /*<<< orphan*/  state_decoder_ready; int /*<<< orphan*/  state_decoder_run; int /*<<< orphan*/  state_pathway_ok; int /*<<< orphan*/  state_encoder_ok; } ;
struct TYPE_2__ {int /*<<< orphan*/  digital_control_scheme; } ;

/* Variables and functions */
 int /*<<< orphan*/  PVR2_DIGITAL_SCHEME_ONAIR ; 
#define  PVR2_PATHWAY_ANALOG 129 
#define  PVR2_PATHWAY_DIGITAL 128 

__attribute__((used)) static int state_check_enable_encoder_run(struct pvr2_hdw *hdw)
{
	if (!hdw->state_encoder_ok) {
		/* Don't run the encoder if it isn't healthy... */
		return 0;
	}
	if (!hdw->state_pathway_ok) {
		/* Don't run the encoder if we don't (yet) know what mode
		   we need to be in... */
		return 0;
	}

	switch (hdw->pathway_state) {
	case PVR2_PATHWAY_ANALOG:
		if (hdw->state_decoder_run && hdw->state_decoder_ready) {
			/* In analog mode, if the decoder is running, then
			   run the encoder. */
			return !0;
		}
		break;
	case PVR2_PATHWAY_DIGITAL:
		if ((hdw->hdw_desc->digital_control_scheme ==
		     PVR2_DIGITAL_SCHEME_ONAIR) &&
		    !hdw->state_encoder_runok) {
			/* This is a quirk.  OnAir hardware won't stream
			   digital until the encoder has been run at least
			   once, for a minimal period of time (empiricially
			   measured to be 1/4 second).  So if we're on
			   OnAir hardware and the encoder has never been
			   run at all, then start the encoder.  Normal
			   state machine logic in the driver will
			   automatically handle the remaining bits. */
			return !0;
		}
		break;
	default:
		/* For completeness (unknown mode; encoder won't run ever) */
		break;
	}
	/* If we get here, then we haven't found any reason to run the
	   encoder, so don't run it. */
	return 0;
}