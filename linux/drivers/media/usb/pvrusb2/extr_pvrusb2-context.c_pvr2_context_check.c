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
struct TYPE_2__ {int /*<<< orphan*/  stream; } ;
struct pvr2_context {int initialized_flag; struct pvr2_channel* mc_first; scalar_t__ disconnect_flag; int /*<<< orphan*/  (* setup_func ) (struct pvr2_context*) ;int /*<<< orphan*/  hdw; TYPE_1__ video_stream; } ;
struct pvr2_channel {int /*<<< orphan*/  (* check_func ) (struct pvr2_channel*) ;struct pvr2_channel* mc_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  PVR2_TRACE_CTXT ; 
 int /*<<< orphan*/  pvr2_context_destroy (struct pvr2_context*) ; 
 scalar_t__ pvr2_context_notify ; 
 int /*<<< orphan*/  pvr2_hdw_get_video_stream (int /*<<< orphan*/ ) ; 
 scalar_t__ pvr2_hdw_initialize (int /*<<< orphan*/ ,void (*) (void*),struct pvr2_context*) ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*,struct pvr2_context*) ; 
 int /*<<< orphan*/  stub1 (struct pvr2_context*) ; 
 int /*<<< orphan*/  stub2 (struct pvr2_channel*) ; 

__attribute__((used)) static void pvr2_context_check(struct pvr2_context *mp)
{
	struct pvr2_channel *ch1, *ch2;
	pvr2_trace(PVR2_TRACE_CTXT,
		   "pvr2_context %p (notify)", mp);
	if (!mp->initialized_flag && !mp->disconnect_flag) {
		mp->initialized_flag = !0;
		pvr2_trace(PVR2_TRACE_CTXT,
			   "pvr2_context %p (initialize)", mp);
		/* Finish hardware initialization */
		if (pvr2_hdw_initialize(mp->hdw,
					(void (*)(void *))pvr2_context_notify,
					mp)) {
			mp->video_stream.stream =
				pvr2_hdw_get_video_stream(mp->hdw);
			/* Trigger interface initialization.  By doing this
			   here initialization runs in our own safe and
			   cozy thread context. */
			if (mp->setup_func) mp->setup_func(mp);
		} else {
			pvr2_trace(PVR2_TRACE_CTXT,
				   "pvr2_context %p (thread skipping setup)",
				   mp);
			/* Even though initialization did not succeed,
			   we're still going to continue anyway.  We need
			   to do this in order to await the expected
			   disconnect (which we will detect in the normal
			   course of operation). */
		}
	}

	for (ch1 = mp->mc_first; ch1; ch1 = ch2) {
		ch2 = ch1->mc_next;
		if (ch1->check_func) ch1->check_func(ch1);
	}

	if (mp->disconnect_flag && !mp->mc_first) {
		/* Go away... */
		pvr2_context_destroy(mp);
		return;
	}
}