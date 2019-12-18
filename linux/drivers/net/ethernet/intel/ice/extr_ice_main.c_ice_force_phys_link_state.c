#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ice_vsi {scalar_t__ type; int /*<<< orphan*/  vsi_num; TYPE_4__* back; struct ice_port_info* port_info; } ;
struct TYPE_6__ {int link_info; } ;
struct TYPE_7__ {TYPE_2__ link_info; } ;
struct ice_port_info {int /*<<< orphan*/  lport; TYPE_3__ phy; } ;
struct ice_aqc_set_phy_cfg_data {int caps; int /*<<< orphan*/  link_fec_options; int /*<<< orphan*/  link_fec_opt; int /*<<< orphan*/  eeer_value; int /*<<< orphan*/  eee_cap; int /*<<< orphan*/  low_power_ctrl; int /*<<< orphan*/  phy_type_high; int /*<<< orphan*/  phy_type_low; } ;
struct ice_aqc_get_phy_caps_data {int caps; int /*<<< orphan*/  link_fec_options; int /*<<< orphan*/  link_fec_opt; int /*<<< orphan*/  eeer_value; int /*<<< orphan*/  eee_cap; int /*<<< orphan*/  low_power_ctrl; int /*<<< orphan*/  phy_type_high; int /*<<< orphan*/  phy_type_low; } ;
struct device {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  hw; TYPE_1__* pdev; } ;
struct TYPE_5__ {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ICE_AQC_PHY_EN_LINK ; 
 int /*<<< orphan*/  ICE_AQC_REPORT_SW_CFG ; 
 int ICE_AQ_LINK_UP ; 
 int ICE_AQ_PHY_ENA_AUTO_LINK_UPDT ; 
 int ICE_AQ_PHY_ENA_LINK ; 
 scalar_t__ ICE_VSI_PF ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  devm_kfree (struct device*,struct ice_aqc_set_phy_cfg_data*) ; 
 struct ice_aqc_set_phy_cfg_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int ice_aq_get_phy_caps (struct ice_port_info*,int,int /*<<< orphan*/ ,struct ice_aqc_set_phy_cfg_data*,int /*<<< orphan*/ *) ; 
 int ice_aq_set_phy_cfg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ice_aqc_set_phy_cfg_data*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ice_force_phys_link_state(struct ice_vsi *vsi, bool link_up)
{
	struct ice_aqc_get_phy_caps_data *pcaps;
	struct ice_aqc_set_phy_cfg_data *cfg;
	struct ice_port_info *pi;
	struct device *dev;
	int retcode;

	if (!vsi || !vsi->port_info || !vsi->back)
		return -EINVAL;
	if (vsi->type != ICE_VSI_PF)
		return 0;

	dev = &vsi->back->pdev->dev;

	pi = vsi->port_info;

	pcaps = devm_kzalloc(dev, sizeof(*pcaps), GFP_KERNEL);
	if (!pcaps)
		return -ENOMEM;

	retcode = ice_aq_get_phy_caps(pi, false, ICE_AQC_REPORT_SW_CFG, pcaps,
				      NULL);
	if (retcode) {
		dev_err(dev,
			"Failed to get phy capabilities, VSI %d error %d\n",
			vsi->vsi_num, retcode);
		retcode = -EIO;
		goto out;
	}

	/* No change in link */
	if (link_up == !!(pcaps->caps & ICE_AQC_PHY_EN_LINK) &&
	    link_up == !!(pi->phy.link_info.link_info & ICE_AQ_LINK_UP))
		goto out;

	cfg = devm_kzalloc(dev, sizeof(*cfg), GFP_KERNEL);
	if (!cfg) {
		retcode = -ENOMEM;
		goto out;
	}

	cfg->phy_type_low = pcaps->phy_type_low;
	cfg->phy_type_high = pcaps->phy_type_high;
	cfg->caps = pcaps->caps | ICE_AQ_PHY_ENA_AUTO_LINK_UPDT;
	cfg->low_power_ctrl = pcaps->low_power_ctrl;
	cfg->eee_cap = pcaps->eee_cap;
	cfg->eeer_value = pcaps->eeer_value;
	cfg->link_fec_opt = pcaps->link_fec_options;
	if (link_up)
		cfg->caps |= ICE_AQ_PHY_ENA_LINK;
	else
		cfg->caps &= ~ICE_AQ_PHY_ENA_LINK;

	retcode = ice_aq_set_phy_cfg(&vsi->back->hw, pi->lport, cfg, NULL);
	if (retcode) {
		dev_err(dev, "Failed to set phy config, VSI %d error %d\n",
			vsi->vsi_num, retcode);
		retcode = -EIO;
	}

	devm_kfree(dev, cfg);
out:
	devm_kfree(dev, pcaps);
	return retcode;
}