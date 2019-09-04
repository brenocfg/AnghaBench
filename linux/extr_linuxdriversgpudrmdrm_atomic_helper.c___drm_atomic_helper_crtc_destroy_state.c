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
struct drm_crtc_state {int /*<<< orphan*/  gamma_lut; int /*<<< orphan*/  ctm; int /*<<< orphan*/  degamma_lut; int /*<<< orphan*/  mode_blob; TYPE_1__* commit; scalar_t__ event; } ;
struct TYPE_2__ {int /*<<< orphan*/ * event; scalar_t__ abort_completion; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_crtc_commit_put (TYPE_1__*) ; 
 int /*<<< orphan*/  drm_property_blob_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void __drm_atomic_helper_crtc_destroy_state(struct drm_crtc_state *state)
{
	if (state->commit) {
		/*
		 * In the event that a non-blocking commit returns
		 * -ERESTARTSYS before the commit_tail work is queued, we will
		 * have an extra reference to the commit object. Release it, if
		 * the event has not been consumed by the worker.
		 *
		 * state->event may be freed, so we can't directly look at
		 * state->event->base.completion.
		 */
		if (state->event && state->commit->abort_completion)
			drm_crtc_commit_put(state->commit);

		kfree(state->commit->event);
		state->commit->event = NULL;

		drm_crtc_commit_put(state->commit);
	}

	drm_property_blob_put(state->mode_blob);
	drm_property_blob_put(state->degamma_lut);
	drm_property_blob_put(state->ctm);
	drm_property_blob_put(state->gamma_lut);
}