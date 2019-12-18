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
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {int /*<<< orphan*/  state; } ;
struct dm_crtc_state {struct drm_crtc_state base; int /*<<< orphan*/  cm_is_degamma_srgb; int /*<<< orphan*/  cm_has_degamma; int /*<<< orphan*/  crc_src; int /*<<< orphan*/  freesync_config; int /*<<< orphan*/  vrr_supported; int /*<<< orphan*/  abm_level; int /*<<< orphan*/  vrr_infopacket; int /*<<< orphan*/  vrr_params; int /*<<< orphan*/  interrupts_enabled; int /*<<< orphan*/  active_planes; scalar_t__ stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  __drm_atomic_helper_crtc_duplicate_state (struct drm_crtc*,struct drm_crtc_state*) ; 
 int /*<<< orphan*/  dc_stream_retain (scalar_t__) ; 
 struct dm_crtc_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct dm_crtc_state* to_dm_crtc_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct drm_crtc_state *
dm_crtc_duplicate_state(struct drm_crtc *crtc)
{
	struct dm_crtc_state *state, *cur;

	cur = to_dm_crtc_state(crtc->state);

	if (WARN_ON(!crtc->state))
		return NULL;

	state = kzalloc(sizeof(*state), GFP_KERNEL);
	if (!state)
		return NULL;

	__drm_atomic_helper_crtc_duplicate_state(crtc, &state->base);

	if (cur->stream) {
		state->stream = cur->stream;
		dc_stream_retain(state->stream);
	}

	state->active_planes = cur->active_planes;
	state->interrupts_enabled = cur->interrupts_enabled;
	state->vrr_params = cur->vrr_params;
	state->vrr_infopacket = cur->vrr_infopacket;
	state->abm_level = cur->abm_level;
	state->vrr_supported = cur->vrr_supported;
	state->freesync_config = cur->freesync_config;
	state->crc_src = cur->crc_src;
	state->cm_has_degamma = cur->cm_has_degamma;
	state->cm_is_degamma_srgb = cur->cm_is_degamma_srgb;

	/* TODO Duplicate dc_stream after objects are stream object is flattened */

	return &state->base;
}