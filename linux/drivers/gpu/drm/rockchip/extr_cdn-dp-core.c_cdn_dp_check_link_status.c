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
typedef  int /*<<< orphan*/  u8 ;
struct cdn_dp_port {int /*<<< orphan*/  lanes; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_lanes; int /*<<< orphan*/  rate; } ;
struct cdn_dp_device {TYPE_1__ link; int /*<<< orphan*/  dpcd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_LANE0_1_STATUS ; 
 int DP_LINK_STATUS_SIZE ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 struct cdn_dp_port* cdn_dp_connected_port (struct cdn_dp_device*) ; 
 scalar_t__ cdn_dp_dpcd_read (struct cdn_dp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int drm_dp_channel_eq_ok (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_dp_max_lane_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool cdn_dp_check_link_status(struct cdn_dp_device *dp)
{
	u8 link_status[DP_LINK_STATUS_SIZE];
	struct cdn_dp_port *port = cdn_dp_connected_port(dp);
	u8 sink_lanes = drm_dp_max_lane_count(dp->dpcd);

	if (!port || !dp->link.rate || !dp->link.num_lanes)
		return false;

	if (cdn_dp_dpcd_read(dp, DP_LANE0_1_STATUS, link_status,
			     DP_LINK_STATUS_SIZE)) {
		DRM_ERROR("Failed to get link status\n");
		return false;
	}

	/* if link training is requested we should perform it always */
	return drm_dp_channel_eq_ok(link_status, min(port->lanes, sink_lanes));
}