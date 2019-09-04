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
struct drm_crtc {int /*<<< orphan*/  index; int /*<<< orphan*/  state; } ;
struct dm_crtc_state {int crc_enabled; scalar_t__ crc_skip_count; struct dc_stream_state* stream; } ;
struct dc_stream_state {TYPE_1__* ctx; } ;
typedef  enum amdgpu_dm_pipe_crc_source { ____Placeholder_amdgpu_dm_pipe_crc_source } amdgpu_dm_pipe_crc_source ;
struct TYPE_2__ {int /*<<< orphan*/  dc; } ;

/* Variables and functions */
 int AMDGPU_DM_PIPE_CRC_SOURCE_AUTO ; 
 int /*<<< orphan*/  DITHER_OPTION_DEFAULT ; 
 int /*<<< orphan*/  DITHER_OPTION_TRUN8 ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  dc_stream_configure_crc (int /*<<< orphan*/ ,struct dc_stream_state*,int,int) ; 
 int /*<<< orphan*/  dc_stream_set_dither_option (struct dc_stream_state*,int /*<<< orphan*/ ) ; 
 int dm_parse_crc_source (char const*) ; 
 int /*<<< orphan*/  drm_crtc_vblank_get (struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_crtc_vblank_put (struct drm_crtc*) ; 
 struct dm_crtc_state* to_dm_crtc_state (int /*<<< orphan*/ ) ; 

int amdgpu_dm_crtc_set_crc_source(struct drm_crtc *crtc, const char *src_name,
			   size_t *values_cnt)
{
	struct dm_crtc_state *crtc_state = to_dm_crtc_state(crtc->state);
	struct dc_stream_state *stream_state = crtc_state->stream;
	bool enable;

	enum amdgpu_dm_pipe_crc_source source = dm_parse_crc_source(src_name);

	if (source < 0) {
		DRM_DEBUG_DRIVER("Unknown CRC source %s for CRTC%d\n",
				 src_name, crtc->index);
		return -EINVAL;
	}

	if (!stream_state) {
		DRM_ERROR("No stream state for CRTC%d\n", crtc->index);
		return -EINVAL;
	}

	enable = (source == AMDGPU_DM_PIPE_CRC_SOURCE_AUTO);

	if (!dc_stream_configure_crc(stream_state->ctx->dc, stream_state,
				     enable, enable))
		return -EINVAL;

	/* When enabling CRC, we should also disable dithering. */
	dc_stream_set_dither_option(stream_state,
				    enable ? DITHER_OPTION_TRUN8
					   : DITHER_OPTION_DEFAULT);

	/*
	 * Reading the CRC requires the vblank interrupt handler to be
	 * enabled. Keep a reference until CRC capture stops.
	 */
	if (!crtc_state->crc_enabled && enable)
		drm_crtc_vblank_get(crtc);
	else if (crtc_state->crc_enabled && !enable)
		drm_crtc_vblank_put(crtc);

	crtc_state->crc_enabled = enable;

	*values_cnt = 3;
	/* Reset crc_skipped on dm state */
	crtc_state->crc_skip_count = 0;
	return 0;
}