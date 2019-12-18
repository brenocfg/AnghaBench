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
struct pvr2_hdw {unsigned int state_pipeline_idle; scalar_t__ state_pipeline_pause; int /*<<< orphan*/  state_decoder_quiescent; scalar_t__ state_usbstream_run; scalar_t__ state_decoder_run; scalar_t__ state_encoder_run; } ;

/* Variables and functions */

__attribute__((used)) static int state_update_pipeline_state(struct pvr2_hdw *hdw)
{
	unsigned int st;
	int updatedFl = 0;
	/* Update pipeline state */
	st = !(hdw->state_encoder_run ||
	       hdw->state_decoder_run ||
	       hdw->state_usbstream_run ||
	       (!hdw->state_decoder_quiescent));
	if (!st != !hdw->state_pipeline_idle) {
		hdw->state_pipeline_idle = st;
		updatedFl = !0;
	}
	if (hdw->state_pipeline_idle && hdw->state_pipeline_pause) {
		hdw->state_pipeline_pause = 0;
		updatedFl = !0;
	}
	return updatedFl;
}