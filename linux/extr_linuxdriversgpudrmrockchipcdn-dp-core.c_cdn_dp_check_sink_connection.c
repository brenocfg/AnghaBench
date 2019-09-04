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
typedef  scalar_t__ u8 ;
struct cdn_dp_port {int /*<<< orphan*/  extcon; } ;
struct cdn_dp_device {size_t active_port; size_t ports; int /*<<< orphan*/  dev; struct cdn_dp_port** port; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDN_DPCD_TIMEOUT_MS ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  EXTCON_DISP_DP ; 
 int /*<<< orphan*/  cdn_dp_get_sink_count (struct cdn_dp_device*,scalar_t__*) ; 
 int /*<<< orphan*/  extcon_get_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static bool cdn_dp_check_sink_connection(struct cdn_dp_device *dp)
{
	unsigned long timeout = jiffies + msecs_to_jiffies(CDN_DPCD_TIMEOUT_MS);
	struct cdn_dp_port *port;
	u8 sink_count = 0;

	if (dp->active_port < 0 || dp->active_port >= dp->ports) {
		DRM_DEV_ERROR(dp->dev, "active_port is wrong!\n");
		return false;
	}

	port = dp->port[dp->active_port];

	/*
	 * Attempt to read sink count, retry in case the sink may not be ready.
	 *
	 * Sinks are *supposed* to come up within 1ms from an off state, but
	 * some docks need more time to power up.
	 */
	while (time_before(jiffies, timeout)) {
		if (!extcon_get_state(port->extcon, EXTCON_DISP_DP))
			return false;

		if (!cdn_dp_get_sink_count(dp, &sink_count))
			return sink_count ? true : false;

		usleep_range(5000, 10000);
	}

	DRM_DEV_ERROR(dp->dev, "Get sink capability timed out\n");
	return false;
}