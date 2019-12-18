#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct drm_dp_mst_topology_mgr {int /*<<< orphan*/  mst_state; } ;
struct drm_dp_mst_port {int dummy; } ;
struct dp_mst_stream_allocation_table {int dummy; } ;
struct TYPE_4__ {int pix_clk_100hz; int display_color_depth; } ;
struct dc_stream_state {TYPE_2__ timing; scalar_t__ dm_stream_context; } ;
struct dc_context {int dummy; } ;
struct amdgpu_dm_connector {struct drm_dp_mst_port* port; TYPE_1__* mst_port; } ;
struct TYPE_3__ {struct drm_dp_mst_topology_mgr mst_mgr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
#define  COLOR_DEPTH_101010 133 
#define  COLOR_DEPTH_121212 132 
#define  COLOR_DEPTH_141414 131 
#define  COLOR_DEPTH_161616 130 
#define  COLOR_DEPTH_666 129 
#define  COLOR_DEPTH_888 128 
 int drm_dp_calc_pbn_mode (int,int) ; 
 int drm_dp_find_vcpi_slots (struct drm_dp_mst_topology_mgr*,int) ; 
 int drm_dp_mst_allocate_vcpi (struct drm_dp_mst_topology_mgr*,struct drm_dp_mst_port*,int,int) ; 
 int /*<<< orphan*/  drm_dp_mst_reset_vcpi_slots (struct drm_dp_mst_topology_mgr*,struct drm_dp_mst_port*) ; 
 int drm_dp_update_payload_part1 (struct drm_dp_mst_topology_mgr*) ; 
 int /*<<< orphan*/  get_payload_table (struct amdgpu_dm_connector*,struct dp_mst_stream_allocation_table*) ; 

bool dm_helpers_dp_mst_write_payload_allocation_table(
		struct dc_context *ctx,
		const struct dc_stream_state *stream,
		struct dp_mst_stream_allocation_table *proposed_table,
		bool enable)
{
	struct amdgpu_dm_connector *aconnector;
	struct drm_dp_mst_topology_mgr *mst_mgr;
	struct drm_dp_mst_port *mst_port;
	int slots = 0;
	bool ret;
	int clock;
	int bpp = 0;
	int pbn = 0;

	aconnector = (struct amdgpu_dm_connector *)stream->dm_stream_context;

	if (!aconnector || !aconnector->mst_port)
		return false;

	mst_mgr = &aconnector->mst_port->mst_mgr;

	if (!mst_mgr->mst_state)
		return false;

	mst_port = aconnector->port;

	if (enable) {
		clock = stream->timing.pix_clk_100hz / 10;

		switch (stream->timing.display_color_depth) {

		case COLOR_DEPTH_666:
			bpp = 6;
			break;
		case COLOR_DEPTH_888:
			bpp = 8;
			break;
		case COLOR_DEPTH_101010:
			bpp = 10;
			break;
		case COLOR_DEPTH_121212:
			bpp = 12;
			break;
		case COLOR_DEPTH_141414:
			bpp = 14;
			break;
		case COLOR_DEPTH_161616:
			bpp = 16;
			break;
		default:
			ASSERT(bpp != 0);
			break;
		}

		bpp = bpp * 3;

		/* TODO need to know link rate */

		pbn = drm_dp_calc_pbn_mode(clock, bpp);

		slots = drm_dp_find_vcpi_slots(mst_mgr, pbn);
		ret = drm_dp_mst_allocate_vcpi(mst_mgr, mst_port, pbn, slots);

		if (!ret)
			return false;

	} else {
		drm_dp_mst_reset_vcpi_slots(mst_mgr, mst_port);
	}

	ret = drm_dp_update_payload_part1(mst_mgr);

	/* mst_mgr->->payloads are VC payload notify MST branch using DPCD or
	 * AUX message. The sequence is slot 1-63 allocated sequence for each
	 * stream. AMD ASIC stream slot allocation should follow the same
	 * sequence. copy DRM MST allocation to dc */

	get_payload_table(aconnector, proposed_table);

	if (ret)
		return false;

	return true;
}