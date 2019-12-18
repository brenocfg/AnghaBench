#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mod_vrr_params {int /*<<< orphan*/  adjust; } ;
struct mod_freesync_config {int /*<<< orphan*/  state; scalar_t__ max_refresh_in_uhz; scalar_t__ min_refresh_in_uhz; } ;
struct TYPE_5__ {scalar_t__ vrr_enabled; } ;
struct dm_crtc_state {int freesync_timing_changed; struct mod_vrr_params vrr_params; TYPE_2__ base; scalar_t__ vrr_supported; struct mod_freesync_config freesync_config; struct dc_stream_state* stream; } ;
struct TYPE_4__ {int /*<<< orphan*/  v_total; int /*<<< orphan*/  h_total; } ;
struct dc_stream_state {TYPE_1__ timing; } ;
struct amdgpu_display_manager {int /*<<< orphan*/  freesync_module; struct amdgpu_device* adev; } ;
struct amdgpu_device {TYPE_3__* ddev; } ;
struct TYPE_6__ {int /*<<< orphan*/  event_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  VRR_STATE_ACTIVE_VARIABLE ; 
 int /*<<< orphan*/  VRR_STATE_INACTIVE ; 
 int /*<<< orphan*/  VRR_STATE_UNSUPPORTED ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mod_freesync_build_vrr_params (int /*<<< orphan*/ ,struct dc_stream_state*,struct mod_freesync_config*,struct mod_vrr_params*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void pre_update_freesync_state_on_stream(
	struct amdgpu_display_manager *dm,
	struct dm_crtc_state *new_crtc_state)
{
	struct dc_stream_state *new_stream = new_crtc_state->stream;
	struct mod_vrr_params vrr_params;
	struct mod_freesync_config config = new_crtc_state->freesync_config;
	struct amdgpu_device *adev = dm->adev;
	unsigned long flags;

	if (!new_stream)
		return;

	/*
	 * TODO: Determine why min/max totals and vrefresh can be 0 here.
	 * For now it's sufficient to just guard against these conditions.
	 */
	if (!new_stream->timing.h_total || !new_stream->timing.v_total)
		return;

	spin_lock_irqsave(&adev->ddev->event_lock, flags);
	vrr_params = new_crtc_state->vrr_params;

	if (new_crtc_state->vrr_supported &&
	    config.min_refresh_in_uhz &&
	    config.max_refresh_in_uhz) {
		config.state = new_crtc_state->base.vrr_enabled ?
			VRR_STATE_ACTIVE_VARIABLE :
			VRR_STATE_INACTIVE;
	} else {
		config.state = VRR_STATE_UNSUPPORTED;
	}

	mod_freesync_build_vrr_params(dm->freesync_module,
				      new_stream,
				      &config, &vrr_params);

	new_crtc_state->freesync_timing_changed |=
		(memcmp(&new_crtc_state->vrr_params.adjust,
			&vrr_params.adjust,
			sizeof(vrr_params.adjust)) != 0);

	new_crtc_state->vrr_params = vrr_params;
	spin_unlock_irqrestore(&adev->ddev->event_lock, flags);
}