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
struct media_entity {int dummy; } ;
struct isp_csiphy {int /*<<< orphan*/  mutex; struct media_entity* entity; int /*<<< orphan*/ * vdd; TYPE_1__* isp; int /*<<< orphan*/  csi2; } ;
struct TYPE_2__ {scalar_t__ revision; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  ISPCSI2_PHY_CFG_PWR_CMD_ON ; 
 scalar_t__ ISP_REVISION_15_0 ; 
 int /*<<< orphan*/  csiphy_power_autoswitch_enable (struct isp_csiphy*,int) ; 
 int csiphy_set_power (struct isp_csiphy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int omap3isp_csi2_reset (int /*<<< orphan*/ ) ; 
 int omap3isp_csiphy_config (struct isp_csiphy*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ *) ; 
 int regulator_enable (int /*<<< orphan*/ *) ; 

int omap3isp_csiphy_acquire(struct isp_csiphy *phy, struct media_entity *entity)
{
	int rval;

	if (phy->vdd == NULL) {
		dev_err(phy->isp->dev,
			"Power regulator for CSI PHY not available\n");
		return -ENODEV;
	}

	mutex_lock(&phy->mutex);

	rval = regulator_enable(phy->vdd);
	if (rval < 0)
		goto done;

	rval = omap3isp_csi2_reset(phy->csi2);
	if (rval < 0)
		goto done;

	phy->entity = entity;

	rval = omap3isp_csiphy_config(phy);
	if (rval < 0)
		goto done;

	if (phy->isp->revision == ISP_REVISION_15_0) {
		rval = csiphy_set_power(phy, ISPCSI2_PHY_CFG_PWR_CMD_ON);
		if (rval) {
			regulator_disable(phy->vdd);
			goto done;
		}

		csiphy_power_autoswitch_enable(phy, true);
	}
done:
	if (rval < 0)
		phy->entity = NULL;

	mutex_unlock(&phy->mutex);
	return rval;
}