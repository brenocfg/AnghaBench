#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct isp_pipeline {int /*<<< orphan*/  external; } ;
struct isp_csiphy {int /*<<< orphan*/  mutex; int /*<<< orphan*/ * entity; int /*<<< orphan*/  vdd; TYPE_3__* isp; } ;
struct TYPE_4__ {int /*<<< orphan*/  phy_layer; } ;
struct TYPE_5__ {TYPE_1__ ccp2; } ;
struct isp_bus_cfg {TYPE_2__ bus; int /*<<< orphan*/  interface; } ;
struct TYPE_6__ {scalar_t__ revision; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISPCSI2_PHY_CFG_PWR_CMD_OFF ; 
 scalar_t__ ISP_REVISION_15_0 ; 
 int /*<<< orphan*/  csiphy_power_autoswitch_enable (struct isp_csiphy*,int) ; 
 int /*<<< orphan*/  csiphy_routing_cfg (struct isp_csiphy*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csiphy_set_power (struct isp_csiphy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 struct isp_pipeline* to_isp_pipeline (int /*<<< orphan*/ *) ; 
 struct isp_bus_cfg* v4l2_subdev_to_bus_cfg (int /*<<< orphan*/ ) ; 

void omap3isp_csiphy_release(struct isp_csiphy *phy)
{
	mutex_lock(&phy->mutex);
	if (phy->entity) {
		struct isp_pipeline *pipe = to_isp_pipeline(phy->entity);
		struct isp_bus_cfg *buscfg =
			v4l2_subdev_to_bus_cfg(pipe->external);

		csiphy_routing_cfg(phy, buscfg->interface, false,
				   buscfg->bus.ccp2.phy_layer);
		if (phy->isp->revision == ISP_REVISION_15_0) {
			csiphy_power_autoswitch_enable(phy, false);
			csiphy_set_power(phy, ISPCSI2_PHY_CFG_PWR_CMD_OFF);
		}
		regulator_disable(phy->vdd);
		phy->entity = NULL;
	}
	mutex_unlock(&phy->mutex);
}