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
struct net_device {int dummy; } ;
struct ice_vsi {TYPE_3__* back; struct ice_port_info* port_info; } ;
struct TYPE_4__ {scalar_t__ pfcena; } ;
struct ice_dcbx_cfg {TYPE_1__ pfc; } ;
struct ice_port_info {struct ice_dcbx_cfg local_dcbx_cfg; } ;
struct ice_netdev_priv {struct ice_vsi* vsi; } ;
struct ice_aqc_get_phy_caps_data {int caps; } ;
struct ethtool_pauseparam {int rx_pause; int tx_pause; int /*<<< orphan*/  autoneg; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
struct TYPE_6__ {TYPE_2__* pdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ICE_AQC_PHY_AN_MODE ; 
 int ICE_AQC_PHY_EN_RX_LINK_PAUSE ; 
 int ICE_AQC_PHY_EN_TX_LINK_PAUSE ; 
 int /*<<< orphan*/  ICE_AQC_REPORT_SW_CFG ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ *,struct ice_aqc_get_phy_caps_data*) ; 
 struct ice_aqc_get_phy_caps_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int ice_aq_get_phy_caps (struct ice_port_info*,int,int /*<<< orphan*/ ,struct ice_aqc_get_phy_caps_data*,int /*<<< orphan*/ *) ; 
 struct ice_netdev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void
ice_get_pauseparam(struct net_device *netdev, struct ethtool_pauseparam *pause)
{
	struct ice_netdev_priv *np = netdev_priv(netdev);
	struct ice_port_info *pi = np->vsi->port_info;
	struct ice_aqc_get_phy_caps_data *pcaps;
	struct ice_vsi *vsi = np->vsi;
	struct ice_dcbx_cfg *dcbx_cfg;
	enum ice_status status;

	/* Initialize pause params */
	pause->rx_pause = 0;
	pause->tx_pause = 0;

	dcbx_cfg = &pi->local_dcbx_cfg;

	pcaps = devm_kzalloc(&vsi->back->pdev->dev, sizeof(*pcaps),
			     GFP_KERNEL);
	if (!pcaps)
		return;

	/* Get current PHY config */
	status = ice_aq_get_phy_caps(pi, false, ICE_AQC_REPORT_SW_CFG, pcaps,
				     NULL);
	if (status)
		goto out;

	pause->autoneg = ((pcaps->caps & ICE_AQC_PHY_AN_MODE) ?
			AUTONEG_ENABLE : AUTONEG_DISABLE);

	if (dcbx_cfg->pfc.pfcena)
		/* PFC enabled so report LFC as off */
		goto out;

	if (pcaps->caps & ICE_AQC_PHY_EN_TX_LINK_PAUSE)
		pause->tx_pause = 1;
	if (pcaps->caps & ICE_AQC_PHY_EN_RX_LINK_PAUSE)
		pause->rx_pause = 1;

out:
	devm_kfree(&vsi->back->pdev->dev, pcaps);
}