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
union extcon_property_value {int /*<<< orphan*/  intval; } ;
struct cdn_dp_port {int phy_enabled; int /*<<< orphan*/  phy; int /*<<< orphan*/  id; int /*<<< orphan*/  lanes; int /*<<< orphan*/  extcon; } ;
struct cdn_dp_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  active_port; } ;

/* Variables and functions */
 int DPTX_HPD_DEL ; 
 int DPTX_HPD_SEL ; 
 int DPTX_HPD_SEL_MASK ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  EXTCON_DISP_DP ; 
 int /*<<< orphan*/  EXTCON_PROP_USB_TYPEC_POLARITY ; 
 int /*<<< orphan*/  GRF_SOC_CON26 ; 
 int cdn_dp_get_hpd_status (struct cdn_dp_device*) ; 
 int /*<<< orphan*/  cdn_dp_get_port_lanes (struct cdn_dp_port*) ; 
 int cdn_dp_grf_write (struct cdn_dp_device*,int /*<<< orphan*/ ,int) ; 
 int cdn_dp_set_host_cap (struct cdn_dp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int extcon_get_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union extcon_property_value*) ; 
 scalar_t__ phy_power_off (int /*<<< orphan*/ ) ; 
 int phy_power_on (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cdn_dp_enable_phy(struct cdn_dp_device *dp, struct cdn_dp_port *port)
{
	union extcon_property_value property;
	int ret;

	if (!port->phy_enabled) {
		ret = phy_power_on(port->phy);
		if (ret) {
			DRM_DEV_ERROR(dp->dev, "phy power on failed: %d\n",
				      ret);
			goto err_phy;
		}
		port->phy_enabled = true;
	}

	ret = cdn_dp_grf_write(dp, GRF_SOC_CON26,
			       DPTX_HPD_SEL_MASK | DPTX_HPD_SEL);
	if (ret) {
		DRM_DEV_ERROR(dp->dev, "Failed to write HPD_SEL %d\n", ret);
		goto err_power_on;
	}

	ret = cdn_dp_get_hpd_status(dp);
	if (ret <= 0) {
		if (!ret)
			DRM_DEV_ERROR(dp->dev, "hpd does not exist\n");
		goto err_power_on;
	}

	ret = extcon_get_property(port->extcon, EXTCON_DISP_DP,
				  EXTCON_PROP_USB_TYPEC_POLARITY, &property);
	if (ret) {
		DRM_DEV_ERROR(dp->dev, "get property failed\n");
		goto err_power_on;
	}

	port->lanes = cdn_dp_get_port_lanes(port);
	ret = cdn_dp_set_host_cap(dp, port->lanes, property.intval);
	if (ret) {
		DRM_DEV_ERROR(dp->dev, "set host capabilities failed: %d\n",
			      ret);
		goto err_power_on;
	}

	dp->active_port = port->id;
	return 0;

err_power_on:
	if (phy_power_off(port->phy))
		DRM_DEV_ERROR(dp->dev, "phy power off failed: %d", ret);
	else
		port->phy_enabled = false;

err_phy:
	cdn_dp_grf_write(dp, GRF_SOC_CON26,
			 DPTX_HPD_SEL_MASK | DPTX_HPD_DEL);
	return ret;
}