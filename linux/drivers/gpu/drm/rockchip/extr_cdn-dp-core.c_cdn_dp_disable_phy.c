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
struct cdn_dp_port {int phy_enabled; scalar_t__ lanes; int /*<<< orphan*/  phy; } ;
struct cdn_dp_device {int active_port; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int phy_power_off (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cdn_dp_disable_phy(struct cdn_dp_device *dp,
			      struct cdn_dp_port *port)
{
	int ret;

	if (port->phy_enabled) {
		ret = phy_power_off(port->phy);
		if (ret) {
			DRM_DEV_ERROR(dp->dev, "phy power off failed: %d", ret);
			return ret;
		}
	}

	port->phy_enabled = false;
	port->lanes = 0;
	dp->active_port = -1;
	return 0;
}