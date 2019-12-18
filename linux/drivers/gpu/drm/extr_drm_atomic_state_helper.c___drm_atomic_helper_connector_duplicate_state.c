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
struct drm_connector_state {int /*<<< orphan*/ * writeback_job; scalar_t__ hdr_output_metadata; int /*<<< orphan*/ * commit; scalar_t__ crtc; } ;
struct drm_connector {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_connector_get (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_property_blob_get (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (struct drm_connector_state*,int /*<<< orphan*/ ,int) ; 

void
__drm_atomic_helper_connector_duplicate_state(struct drm_connector *connector,
					    struct drm_connector_state *state)
{
	memcpy(state, connector->state, sizeof(*state));
	if (state->crtc)
		drm_connector_get(connector);
	state->commit = NULL;

	if (state->hdr_output_metadata)
		drm_property_blob_get(state->hdr_output_metadata);

	/* Don't copy over a writeback job, they are used only once */
	state->writeback_job = NULL;
}