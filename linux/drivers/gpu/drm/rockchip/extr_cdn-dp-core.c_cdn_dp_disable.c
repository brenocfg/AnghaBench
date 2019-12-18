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
struct TYPE_2__ {scalar_t__ num_lanes; scalar_t__ rate; } ;
struct cdn_dp_device {int active; int ports; int /*<<< orphan*/ * edid; int /*<<< orphan*/  connected; TYPE_1__ link; int /*<<< orphan*/  dev; int /*<<< orphan*/ * port; } ;

/* Variables and functions */
 int DPTX_HPD_DEL ; 
 int DPTX_HPD_SEL_MASK ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  GRF_SOC_CON26 ; 
 int /*<<< orphan*/  cdn_dp_clk_disable (struct cdn_dp_device*) ; 
 int /*<<< orphan*/  cdn_dp_disable_phy (struct cdn_dp_device*,int /*<<< orphan*/ ) ; 
 int cdn_dp_grf_write (struct cdn_dp_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cdn_dp_set_firmware_active (struct cdn_dp_device*,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cdn_dp_disable(struct cdn_dp_device *dp)
{
	int ret, i;

	if (!dp->active)
		return 0;

	for (i = 0; i < dp->ports; i++)
		cdn_dp_disable_phy(dp, dp->port[i]);

	ret = cdn_dp_grf_write(dp, GRF_SOC_CON26,
			       DPTX_HPD_SEL_MASK | DPTX_HPD_DEL);
	if (ret) {
		DRM_DEV_ERROR(dp->dev, "Failed to clear hpd sel %d\n",
			      ret);
		return ret;
	}

	cdn_dp_set_firmware_active(dp, false);
	cdn_dp_clk_disable(dp);
	dp->active = false;
	dp->link.rate = 0;
	dp->link.num_lanes = 0;
	if (!dp->connected) {
		kfree(dp->edid);
		dp->edid = NULL;
	}

	return 0;
}