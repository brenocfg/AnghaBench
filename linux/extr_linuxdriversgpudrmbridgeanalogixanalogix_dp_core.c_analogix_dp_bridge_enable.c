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
struct drm_bridge {struct analogix_dp_device* driver_private; } ;
struct analogix_dp_device {scalar_t__ dpms_mode; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ DRM_MODE_DPMS_ON ; 
 int MAX_PLL_LOCK_LOOP ; 
 scalar_t__ analogix_dp_set_bridge (struct analogix_dp_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void analogix_dp_bridge_enable(struct drm_bridge *bridge)
{
	struct analogix_dp_device *dp = bridge->driver_private;
	int timeout_loop = 0;

	if (dp->dpms_mode == DRM_MODE_DPMS_ON)
		return;

	while (timeout_loop < MAX_PLL_LOCK_LOOP) {
		if (analogix_dp_set_bridge(dp) == 0) {
			dp->dpms_mode = DRM_MODE_DPMS_ON;
			return;
		}
		dev_err(dp->dev, "failed to set bridge, retry: %d\n",
			timeout_loop);
		timeout_loop++;
		usleep_range(10, 11);
	}
	dev_err(dp->dev, "too many times retry set bridge, give it up\n");
}