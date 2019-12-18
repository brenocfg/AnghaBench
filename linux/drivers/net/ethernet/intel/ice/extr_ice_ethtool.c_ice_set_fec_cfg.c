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
typedef  scalar_t__ u8 ;
struct net_device {int dummy; } ;
struct ice_vsi {scalar_t__ type; TYPE_2__* back; struct ice_port_info* port_info; } ;
struct ice_port_info {int /*<<< orphan*/  lport; int /*<<< orphan*/  hw; } ;
struct ice_netdev_priv {struct ice_vsi* vsi; } ;
struct ice_aqc_set_phy_cfg_data {scalar_t__ caps; scalar_t__ link_fec_opt; int /*<<< orphan*/  member_0; } ;
struct ice_aqc_get_phy_caps_data {scalar_t__ caps; scalar_t__ link_fec_options; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
typedef  enum ice_fec_mode { ____Placeholder_ice_fec_mode } ice_fec_mode ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ICE_AQC_PHY_AN_MODE ; 
 scalar_t__ ICE_AQC_PHY_EN_AUTO_FEC ; 
 int /*<<< orphan*/  ICE_AQC_REPORT_SW_CFG ; 
 int /*<<< orphan*/  ICE_AQC_REPORT_TOPO_CAP ; 
 scalar_t__ ICE_AQ_PHY_ENA_AUTO_FEC ; 
 scalar_t__ ICE_AQ_PHY_ENA_AUTO_LINK_UPDT ; 
 scalar_t__ ICE_VSI_PF ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ *,struct ice_aqc_get_phy_caps_data*) ; 
 struct ice_aqc_get_phy_caps_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int ice_aq_get_phy_caps (struct ice_port_info*,int,int /*<<< orphan*/ ,struct ice_aqc_get_phy_caps_data*,int /*<<< orphan*/ *) ; 
 int ice_aq_set_phy_cfg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ice_aqc_set_phy_cfg_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_cfg_phy_fec (struct ice_aqc_set_phy_cfg_data*,int) ; 
 int /*<<< orphan*/  ice_copy_phy_caps_to_cfg (struct ice_aqc_get_phy_caps_data*,struct ice_aqc_set_phy_cfg_data*) ; 
 int /*<<< orphan*/  memset (struct ice_aqc_get_phy_caps_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 struct ice_netdev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ice_set_fec_cfg(struct net_device *netdev, enum ice_fec_mode req_fec)
{
	struct ice_netdev_priv *np = netdev_priv(netdev);
	struct ice_aqc_set_phy_cfg_data config = { 0 };
	struct ice_aqc_get_phy_caps_data *caps;
	struct ice_vsi *vsi = np->vsi;
	u8 sw_cfg_caps, sw_cfg_fec;
	struct ice_port_info *pi;
	enum ice_status status;
	int err = 0;

	pi = vsi->port_info;
	if (!pi)
		return -EOPNOTSUPP;

	/* Changing the FEC parameters is not supported if not the PF VSI */
	if (vsi->type != ICE_VSI_PF) {
		netdev_info(netdev, "Changing FEC parameters only supported for PF VSI\n");
		return -EOPNOTSUPP;
	}

	/* Get last SW configuration */
	caps = devm_kzalloc(&vsi->back->pdev->dev, sizeof(*caps), GFP_KERNEL);
	if (!caps)
		return -ENOMEM;

	status = ice_aq_get_phy_caps(pi, false, ICE_AQC_REPORT_SW_CFG,
				     caps, NULL);
	if (status) {
		err = -EAGAIN;
		goto done;
	}

	/* Copy SW configuration returned from PHY caps to PHY config */
	ice_copy_phy_caps_to_cfg(caps, &config);
	sw_cfg_caps = caps->caps;
	sw_cfg_fec = caps->link_fec_options;

	/* Get toloplogy caps, then copy PHY FEC topoloy caps to PHY config */
	memset(caps, 0, sizeof(*caps));

	status = ice_aq_get_phy_caps(pi, false, ICE_AQC_REPORT_TOPO_CAP,
				     caps, NULL);
	if (status) {
		err = -EAGAIN;
		goto done;
	}

	config.caps |= (caps->caps & ICE_AQC_PHY_EN_AUTO_FEC);
	config.link_fec_opt = caps->link_fec_options;

	ice_cfg_phy_fec(&config, req_fec);

	/* If FEC mode has changed, then set PHY configuration and enable AN. */
	if ((config.caps & ICE_AQ_PHY_ENA_AUTO_FEC) !=
	    (sw_cfg_caps & ICE_AQC_PHY_EN_AUTO_FEC) ||
	    config.link_fec_opt != sw_cfg_fec) {
		if (caps->caps & ICE_AQC_PHY_AN_MODE)
			config.caps |= ICE_AQ_PHY_ENA_AUTO_LINK_UPDT;

		status = ice_aq_set_phy_cfg(pi->hw, pi->lport, &config, NULL);

		if (status)
			err = -EAGAIN;
	}

done:
	devm_kfree(&vsi->back->pdev->dev, caps);
	return err;
}