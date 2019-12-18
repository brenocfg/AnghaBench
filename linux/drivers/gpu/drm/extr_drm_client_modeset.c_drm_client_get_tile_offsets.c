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
struct drm_display_mode {scalar_t__ vdisplay; scalar_t__ hdisplay; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct drm_connector {int tile_h_loc; int tile_v_loc; TYPE_1__ base; int /*<<< orphan*/  has_tile; } ;
struct drm_client_offset {int x; int y; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,int,...) ; 

__attribute__((used)) static int drm_client_get_tile_offsets(struct drm_connector **connectors,
				       unsigned int connector_count,
				       struct drm_display_mode **modes,
				       struct drm_client_offset *offsets,
				       int idx,
				       int h_idx, int v_idx)
{
	struct drm_connector *connector;
	int i;
	int hoffset = 0, voffset = 0;

	for (i = 0; i < connector_count; i++) {
		connector = connectors[i];
		if (!connector->has_tile)
			continue;

		if (!modes[i] && (h_idx || v_idx)) {
			DRM_DEBUG_KMS("no modes for connector tiled %d %d\n", i,
				      connector->base.id);
			continue;
		}
		if (connector->tile_h_loc < h_idx)
			hoffset += modes[i]->hdisplay;

		if (connector->tile_v_loc < v_idx)
			voffset += modes[i]->vdisplay;
	}
	offsets[idx].x = hoffset;
	offsets[idx].y = voffset;
	DRM_DEBUG_KMS("returned %d %d for %d %d\n", hoffset, voffset, h_idx, v_idx);
	return 0;
}