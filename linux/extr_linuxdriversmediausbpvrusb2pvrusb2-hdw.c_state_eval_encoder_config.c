#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ expires; } ;
struct pvr2_hdw {int state_encoder_config; int state_encoder_waitok; scalar_t__ pathway_state; scalar_t__ state_encoder_ok; TYPE_1__ encoder_wait_timer; int /*<<< orphan*/  state_pipeline_config; scalar_t__ state_pipeline_req; scalar_t__ state_pipeline_pause; int /*<<< orphan*/  state_pipeline_idle; int /*<<< orphan*/  state_pathway_ok; } ;

/* Variables and functions */
 scalar_t__ PVR2_PATHWAY_ANALOG ; 
 int /*<<< orphan*/  TIME_MSEC_ENCODER_WAIT ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  del_timer_sync (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvr2_encoder_configure (struct pvr2_hdw*) ; 
 scalar_t__ timer_pending (TYPE_1__*) ; 
 int /*<<< orphan*/  trace_stbit (char*,int) ; 

__attribute__((used)) static int state_eval_encoder_config(struct pvr2_hdw *hdw)
{
	if (hdw->state_encoder_config) {
		if (hdw->state_encoder_ok) {
			if (hdw->state_pipeline_req &&
			    !hdw->state_pipeline_pause) return 0;
		}
		hdw->state_encoder_config = 0;
		hdw->state_encoder_waitok = 0;
		trace_stbit("state_encoder_waitok",hdw->state_encoder_waitok);
		/* paranoia - solve race if timer just completed */
		del_timer_sync(&hdw->encoder_wait_timer);
	} else {
		if (!hdw->state_pathway_ok ||
		    (hdw->pathway_state != PVR2_PATHWAY_ANALOG) ||
		    !hdw->state_encoder_ok ||
		    !hdw->state_pipeline_idle ||
		    hdw->state_pipeline_pause ||
		    !hdw->state_pipeline_req ||
		    !hdw->state_pipeline_config) {
			/* We must reset the enforced wait interval if
			   anything has happened that might have disturbed
			   the encoder.  This should be a rare case. */
			if (timer_pending(&hdw->encoder_wait_timer)) {
				del_timer_sync(&hdw->encoder_wait_timer);
			}
			if (hdw->state_encoder_waitok) {
				/* Must clear the state - therefore we did
				   something to a state bit and must also
				   return true. */
				hdw->state_encoder_waitok = 0;
				trace_stbit("state_encoder_waitok",
					    hdw->state_encoder_waitok);
				return !0;
			}
			return 0;
		}
		if (!hdw->state_encoder_waitok) {
			if (!timer_pending(&hdw->encoder_wait_timer)) {
				/* waitok flag wasn't set and timer isn't
				   running.  Check flag once more to avoid
				   a race then start the timer.  This is
				   the point when we measure out a minimal
				   quiet interval before doing something to
				   the encoder. */
				if (!hdw->state_encoder_waitok) {
					hdw->encoder_wait_timer.expires =
						jiffies + msecs_to_jiffies(
						TIME_MSEC_ENCODER_WAIT);
					add_timer(&hdw->encoder_wait_timer);
				}
			}
			/* We can't continue until we know we have been
			   quiet for the interval measured by this
			   timer. */
			return 0;
		}
		pvr2_encoder_configure(hdw);
		if (hdw->state_encoder_ok) hdw->state_encoder_config = !0;
	}
	trace_stbit("state_encoder_config",hdw->state_encoder_config);
	return !0;
}