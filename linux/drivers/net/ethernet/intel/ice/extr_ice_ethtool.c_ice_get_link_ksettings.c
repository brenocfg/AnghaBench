#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct ice_vsi {TYPE_4__* back; TYPE_5__* port_info; } ;
struct ice_netdev_priv {struct ice_vsi* vsi; } ;
struct ice_link_status {int link_info; int an_info; } ;
struct ice_aqc_get_phy_caps_data {int caps; int link_fec_options; } ;
struct TYPE_7__ {int /*<<< orphan*/  port; int /*<<< orphan*/  autoneg; } ;
struct ethtool_link_ksettings {TYPE_2__ base; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
struct TYPE_6__ {int media_type; struct ice_link_status link_info; } ;
struct TYPE_10__ {TYPE_1__ phy; } ;
struct TYPE_9__ {TYPE_3__* pdev; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int /*<<< orphan*/  Asym_Pause ; 
 int /*<<< orphan*/  Autoneg ; 
 int /*<<< orphan*/  Backplane ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FEC_BASER ; 
 int /*<<< orphan*/  FEC_NONE ; 
 int /*<<< orphan*/  FEC_RS ; 
 int /*<<< orphan*/  FIBRE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ICE_AQC_PHY_EN_RX_LINK_PAUSE ; 
 int ICE_AQC_PHY_EN_TX_LINK_PAUSE ; 
 int ICE_AQC_PHY_FEC_10G_KR_40G_KR4_EN ; 
 int ICE_AQC_PHY_FEC_10G_KR_40G_KR4_REQ ; 
 int ICE_AQC_PHY_FEC_25G_KR_CLAUSE74_EN ; 
 int ICE_AQC_PHY_FEC_25G_KR_REQ ; 
 int ICE_AQC_PHY_FEC_25G_RS_528_REQ ; 
 int ICE_AQC_PHY_FEC_25G_RS_544_REQ ; 
 int ICE_AQC_PHY_FEC_25G_RS_CLAUSE91_EN ; 
 int /*<<< orphan*/  ICE_AQC_REPORT_SW_CFG ; 
 int /*<<< orphan*/  ICE_AQC_REPORT_TOPO_CAP ; 
 int ICE_AQ_AN_COMPLETED ; 
 int ICE_AQ_LINK_UP ; 
#define  ICE_MEDIA_BACKPLANE 131 
#define  ICE_MEDIA_BASET 130 
#define  ICE_MEDIA_DA 129 
#define  ICE_MEDIA_FIBER 128 
 int /*<<< orphan*/  PORT_DA ; 
 int /*<<< orphan*/  PORT_FIBRE ; 
 int /*<<< orphan*/  PORT_NONE ; 
 int /*<<< orphan*/  PORT_OTHER ; 
 int /*<<< orphan*/  PORT_TP ; 
 int /*<<< orphan*/  Pause ; 
 int /*<<< orphan*/  TP ; 
 int /*<<< orphan*/  advertising ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ *,struct ice_aqc_get_phy_caps_data*) ; 
 struct ice_aqc_get_phy_caps_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ethtool_link_ksettings_add_link_mode (struct ethtool_link_ksettings*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ethtool_link_ksettings_del_link_mode (struct ethtool_link_ksettings*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ethtool_link_ksettings_zero_link_mode (struct ethtool_link_ksettings*,int /*<<< orphan*/ ) ; 
 int ice_aq_get_phy_caps (TYPE_5__*,int,int /*<<< orphan*/ ,struct ice_aqc_get_phy_caps_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_get_settings_link_down (struct ethtool_link_ksettings*,struct net_device*) ; 
 int /*<<< orphan*/  ice_get_settings_link_up (struct ethtool_link_ksettings*,struct net_device*) ; 
 int /*<<< orphan*/  lp_advertising ; 
 struct ice_netdev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  supported ; 

__attribute__((used)) static int
ice_get_link_ksettings(struct net_device *netdev,
		       struct ethtool_link_ksettings *ks)
{
	struct ice_netdev_priv *np = netdev_priv(netdev);
	struct ice_aqc_get_phy_caps_data *caps;
	struct ice_link_status *hw_link_info;
	struct ice_vsi *vsi = np->vsi;
	enum ice_status status;
	int err = 0;

	ethtool_link_ksettings_zero_link_mode(ks, supported);
	ethtool_link_ksettings_zero_link_mode(ks, advertising);
	ethtool_link_ksettings_zero_link_mode(ks, lp_advertising);
	hw_link_info = &vsi->port_info->phy.link_info;

	/* set speed and duplex */
	if (hw_link_info->link_info & ICE_AQ_LINK_UP)
		ice_get_settings_link_up(ks, netdev);
	else
		ice_get_settings_link_down(ks, netdev);

	/* set autoneg settings */
	ks->base.autoneg = (hw_link_info->an_info & ICE_AQ_AN_COMPLETED) ?
		AUTONEG_ENABLE : AUTONEG_DISABLE;

	/* set media type settings */
	switch (vsi->port_info->phy.media_type) {
	case ICE_MEDIA_FIBER:
		ethtool_link_ksettings_add_link_mode(ks, supported, FIBRE);
		ks->base.port = PORT_FIBRE;
		break;
	case ICE_MEDIA_BASET:
		ethtool_link_ksettings_add_link_mode(ks, supported, TP);
		ethtool_link_ksettings_add_link_mode(ks, advertising, TP);
		ks->base.port = PORT_TP;
		break;
	case ICE_MEDIA_BACKPLANE:
		ethtool_link_ksettings_add_link_mode(ks, supported, Autoneg);
		ethtool_link_ksettings_add_link_mode(ks, supported, Backplane);
		ethtool_link_ksettings_add_link_mode(ks, advertising, Autoneg);
		ethtool_link_ksettings_add_link_mode(ks, advertising,
						     Backplane);
		ks->base.port = PORT_NONE;
		break;
	case ICE_MEDIA_DA:
		ethtool_link_ksettings_add_link_mode(ks, supported, FIBRE);
		ethtool_link_ksettings_add_link_mode(ks, advertising, FIBRE);
		ks->base.port = PORT_DA;
		break;
	default:
		ks->base.port = PORT_OTHER;
		break;
	}

	/* flow control is symmetric and always supported */
	ethtool_link_ksettings_add_link_mode(ks, supported, Pause);

	caps = devm_kzalloc(&vsi->back->pdev->dev, sizeof(*caps), GFP_KERNEL);
	if (!caps)
		return -ENOMEM;

	status = ice_aq_get_phy_caps(vsi->port_info, false,
				     ICE_AQC_REPORT_SW_CFG, caps, NULL);
	if (status) {
		err = -EIO;
		goto done;
	}

	/* Set the advertised flow control based on the PHY capability */
	if ((caps->caps & ICE_AQC_PHY_EN_TX_LINK_PAUSE) &&
	    (caps->caps & ICE_AQC_PHY_EN_RX_LINK_PAUSE)) {
		ethtool_link_ksettings_add_link_mode(ks, advertising, Pause);
		ethtool_link_ksettings_add_link_mode(ks, advertising,
						     Asym_Pause);
	} else if (caps->caps & ICE_AQC_PHY_EN_TX_LINK_PAUSE) {
		ethtool_link_ksettings_add_link_mode(ks, advertising,
						     Asym_Pause);
	} else if (caps->caps & ICE_AQC_PHY_EN_RX_LINK_PAUSE) {
		ethtool_link_ksettings_add_link_mode(ks, advertising, Pause);
		ethtool_link_ksettings_add_link_mode(ks, advertising,
						     Asym_Pause);
	} else {
		ethtool_link_ksettings_del_link_mode(ks, advertising, Pause);
		ethtool_link_ksettings_del_link_mode(ks, advertising,
						     Asym_Pause);
	}

	/* Set advertised FEC modes based on PHY capability */
	ethtool_link_ksettings_add_link_mode(ks, advertising, FEC_NONE);

	if (caps->link_fec_options & ICE_AQC_PHY_FEC_10G_KR_40G_KR4_REQ ||
	    caps->link_fec_options & ICE_AQC_PHY_FEC_25G_KR_REQ)
		ethtool_link_ksettings_add_link_mode(ks, advertising,
						     FEC_BASER);
	if (caps->link_fec_options & ICE_AQC_PHY_FEC_25G_RS_528_REQ ||
	    caps->link_fec_options & ICE_AQC_PHY_FEC_25G_RS_544_REQ)
		ethtool_link_ksettings_add_link_mode(ks, advertising, FEC_RS);

	status = ice_aq_get_phy_caps(vsi->port_info, false,
				     ICE_AQC_REPORT_TOPO_CAP, caps, NULL);
	if (status) {
		err = -EIO;
		goto done;
	}

	/* Set supported FEC modes based on PHY capability */
	ethtool_link_ksettings_add_link_mode(ks, supported, FEC_NONE);

	if (caps->link_fec_options & ICE_AQC_PHY_FEC_10G_KR_40G_KR4_EN ||
	    caps->link_fec_options & ICE_AQC_PHY_FEC_25G_KR_CLAUSE74_EN)
		ethtool_link_ksettings_add_link_mode(ks, supported, FEC_BASER);
	if (caps->link_fec_options & ICE_AQC_PHY_FEC_25G_RS_CLAUSE91_EN)
		ethtool_link_ksettings_add_link_mode(ks, supported, FEC_RS);

done:
	devm_kfree(&vsi->back->pdev->dev, caps);
	return err;
}