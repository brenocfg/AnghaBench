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
typedef  int uint8_t ;
struct drm_connector_state {int /*<<< orphan*/  max_requested_bpc; } ;
struct TYPE_2__ {int /*<<< orphan*/  bpc; } ;
struct drm_connector {struct drm_connector_state* state; TYPE_1__ display_info; } ;
typedef  enum dc_color_depth { ____Placeholder_dc_color_depth } dc_color_depth ;

/* Variables and functions */
 int COLOR_DEPTH_101010 ; 
 int COLOR_DEPTH_121212 ; 
 int COLOR_DEPTH_141414 ; 
 int COLOR_DEPTH_161616 ; 
 int COLOR_DEPTH_666 ; 
 int COLOR_DEPTH_888 ; 
 int COLOR_DEPTH_UNDEFINED ; 
 int min (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum dc_color_depth
convert_color_depth_from_display_info(const struct drm_connector *connector,
				      const struct drm_connector_state *state)
{
	uint8_t bpc = (uint8_t)connector->display_info.bpc;

	/* Assume 8 bpc by default if no bpc is specified. */
	bpc = bpc ? bpc : 8;

	if (!state)
		state = connector->state;

	if (state) {
		/*
		 * Cap display bpc based on the user requested value.
		 *
		 * The value for state->max_bpc may not correctly updated
		 * depending on when the connector gets added to the state
		 * or if this was called outside of atomic check, so it
		 * can't be used directly.
		 */
		bpc = min(bpc, state->max_requested_bpc);

		/* Round down to the nearest even number. */
		bpc = bpc - (bpc & 1);
	}

	switch (bpc) {
	case 0:
		/*
		 * Temporary Work around, DRM doesn't parse color depth for
		 * EDID revision before 1.4
		 * TODO: Fix edid parsing
		 */
		return COLOR_DEPTH_888;
	case 6:
		return COLOR_DEPTH_666;
	case 8:
		return COLOR_DEPTH_888;
	case 10:
		return COLOR_DEPTH_101010;
	case 12:
		return COLOR_DEPTH_121212;
	case 14:
		return COLOR_DEPTH_141414;
	case 16:
		return COLOR_DEPTH_161616;
	default:
		return COLOR_DEPTH_UNDEFINED;
	}
}