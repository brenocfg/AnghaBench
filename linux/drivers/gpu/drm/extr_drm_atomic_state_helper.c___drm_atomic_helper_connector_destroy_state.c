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
struct drm_connector_state {int /*<<< orphan*/  hdr_output_metadata; scalar_t__ writeback_job; scalar_t__ commit; int /*<<< orphan*/  connector; scalar_t__ crtc; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_connector_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_crtc_commit_put (scalar_t__) ; 
 int /*<<< orphan*/  drm_property_blob_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_writeback_cleanup_job (scalar_t__) ; 

void
__drm_atomic_helper_connector_destroy_state(struct drm_connector_state *state)
{
	if (state->crtc)
		drm_connector_put(state->connector);

	if (state->commit)
		drm_crtc_commit_put(state->commit);

	if (state->writeback_job)
		drm_writeback_cleanup_job(state->writeback_job);

	drm_property_blob_put(state->hdr_output_metadata);
}