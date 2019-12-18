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
struct mod_freesync_config {int min_refresh_in_uhz; int max_refresh_in_uhz; int vsif_supported; int btr; int /*<<< orphan*/  state; int /*<<< orphan*/  member_0; } ;
struct drm_display_mode {int dummy; } ;
struct TYPE_6__ {scalar_t__ vrr_enabled; struct drm_display_mode mode; } ;
struct dm_crtc_state {int vrr_supported; struct mod_freesync_config freesync_config; TYPE_3__ base; TYPE_2__* stream; } ;
struct TYPE_4__ {int /*<<< orphan*/  connector; } ;
struct dm_connector_state {scalar_t__ freesync_capable; TYPE_1__ base; } ;
struct amdgpu_dm_connector {int min_vfreq; int max_vfreq; } ;
struct TYPE_5__ {int ignore_msa_timing_param; } ;

/* Variables and functions */
 int /*<<< orphan*/  VRR_STATE_ACTIVE_VARIABLE ; 
 int /*<<< orphan*/  VRR_STATE_INACTIVE ; 
 int drm_mode_vrefresh (struct drm_display_mode*) ; 
 struct amdgpu_dm_connector* to_amdgpu_dm_connector (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_freesync_config_for_crtc(
	struct dm_crtc_state *new_crtc_state,
	struct dm_connector_state *new_con_state)
{
	struct mod_freesync_config config = {0};
	struct amdgpu_dm_connector *aconnector =
			to_amdgpu_dm_connector(new_con_state->base.connector);
	struct drm_display_mode *mode = &new_crtc_state->base.mode;
	int vrefresh = drm_mode_vrefresh(mode);

	new_crtc_state->vrr_supported = new_con_state->freesync_capable &&
					vrefresh >= aconnector->min_vfreq &&
					vrefresh <= aconnector->max_vfreq;

	if (new_crtc_state->vrr_supported) {
		new_crtc_state->stream->ignore_msa_timing_param = true;
		config.state = new_crtc_state->base.vrr_enabled ?
				VRR_STATE_ACTIVE_VARIABLE :
				VRR_STATE_INACTIVE;
		config.min_refresh_in_uhz =
				aconnector->min_vfreq * 1000000;
		config.max_refresh_in_uhz =
				aconnector->max_vfreq * 1000000;
		config.vsif_supported = true;
		config.btr = true;
	}

	new_crtc_state->freesync_config = config;
}