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
typedef  int uint32_t ;
struct TYPE_2__ {int bpc; } ;
struct drm_connector {TYPE_1__ display_info; int /*<<< orphan*/  state; } ;
struct dm_connector_state {int max_bpc; } ;
typedef  enum dc_color_depth { ____Placeholder_dc_color_depth } dc_color_depth ;

/* Variables and functions */
 int COLOR_DEPTH_101010 ; 
 int COLOR_DEPTH_121212 ; 
 int COLOR_DEPTH_141414 ; 
 int COLOR_DEPTH_161616 ; 
 int COLOR_DEPTH_666 ; 
 int COLOR_DEPTH_888 ; 
 int COLOR_DEPTH_UNDEFINED ; 
 struct dm_connector_state* to_dm_connector_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum dc_color_depth
convert_color_depth_from_display_info(const struct drm_connector *connector)
{
	struct dm_connector_state *dm_conn_state =
		to_dm_connector_state(connector->state);
	uint32_t bpc = connector->display_info.bpc;

	/* TODO: Remove this when there's support for max_bpc in drm */
	if (dm_conn_state && bpc > dm_conn_state->max_bpc)
		/* Round down to nearest even number. */
		bpc = dm_conn_state->max_bpc - (dm_conn_state->max_bpc & 1);

	switch (bpc) {
	case 0:
		/* Temporary Work around, DRM don't parse color depth for
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