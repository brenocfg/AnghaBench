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
typedef  int uint32_t ;
struct timing_generator {TYPE_1__* funcs; } ;
struct dc_context {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* wait_for_state ) (struct timing_generator*,int /*<<< orphan*/ ) ;scalar_t__ (* did_triggered_reset_occur ) (struct timing_generator*) ;int /*<<< orphan*/  (* is_counter_moving ) (struct timing_generator*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CRTC_STATE_VACTIVE ; 
 int /*<<< orphan*/  CRTC_STATE_VBLANK ; 
 int /*<<< orphan*/  DC_ERROR (char*) ; 
 int /*<<< orphan*/  DC_SYNC_INFO (char*,int) ; 
 int /*<<< orphan*/  stub1 (struct timing_generator*) ; 
 scalar_t__ stub2 (struct timing_generator*) ; 
 int /*<<< orphan*/  stub3 (struct timing_generator*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct timing_generator*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool wait_for_reset_trigger_to_occur(
	struct dc_context *dc_ctx,
	struct timing_generator *tg)
{
	bool rc = false;

	/* To avoid endless loop we wait at most
	 * frames_to_wait_on_triggered_reset frames for the reset to occur. */
	const uint32_t frames_to_wait_on_triggered_reset = 10;
	int i;

	for (i = 0; i < frames_to_wait_on_triggered_reset; i++) {

		if (!tg->funcs->is_counter_moving(tg)) {
			DC_ERROR("TG counter is not moving!\n");
			break;
		}

		if (tg->funcs->did_triggered_reset_occur(tg)) {
			rc = true;
			/* usually occurs at i=1 */
			DC_SYNC_INFO("GSL: reset occurred at wait count: %d\n",
					i);
			break;
		}

		/* Wait for one frame. */
		tg->funcs->wait_for_state(tg, CRTC_STATE_VACTIVE);
		tg->funcs->wait_for_state(tg, CRTC_STATE_VBLANK);
	}

	if (false == rc)
		DC_ERROR("GSL: Timeout on reset trigger!\n");

	return rc;
}