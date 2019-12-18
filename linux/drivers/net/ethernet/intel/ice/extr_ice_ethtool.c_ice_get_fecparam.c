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
struct ice_link_status {int fec_info; } ;
struct TYPE_4__ {struct ice_link_status link_info; } ;
struct ice_port_info {TYPE_1__ phy; } ;
struct ice_netdev_priv {struct ice_vsi* vsi; } ;
struct ice_aqc_get_phy_caps_data {int caps; int link_fec_options; } ;
struct ethtool_fecparam {int /*<<< orphan*/  fec; int /*<<< orphan*/  active_fec; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
struct TYPE_6__ {TYPE_2__* pdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ETHTOOL_FEC_AUTO ; 
 int /*<<< orphan*/  ETHTOOL_FEC_BASER ; 
 int /*<<< orphan*/  ETHTOOL_FEC_OFF ; 
 int /*<<< orphan*/  ETHTOOL_FEC_RS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ICE_AQC_PHY_EN_AUTO_FEC ; 
 int ICE_AQC_PHY_FEC_10G_KR_40G_KR4_EN ; 
 int ICE_AQC_PHY_FEC_10G_KR_40G_KR4_REQ ; 
 int ICE_AQC_PHY_FEC_25G_KR_CLAUSE74_EN ; 
 int ICE_AQC_PHY_FEC_25G_KR_REQ ; 
 int ICE_AQC_PHY_FEC_25G_RS_528_REQ ; 
 int ICE_AQC_PHY_FEC_25G_RS_544_REQ ; 
 int ICE_AQC_PHY_FEC_25G_RS_CLAUSE91_EN ; 
 int /*<<< orphan*/  ICE_AQC_REPORT_TOPO_CAP ; 
#define  ICE_AQ_LINK_25G_KR_FEC_EN 130 
#define  ICE_AQ_LINK_25G_RS_528_FEC_EN 129 
#define  ICE_AQ_LINK_25G_RS_544_FEC_EN 128 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ *,struct ice_aqc_get_phy_caps_data*) ; 
 struct ice_aqc_get_phy_caps_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int ice_aq_get_phy_caps (struct ice_port_info*,int,int /*<<< orphan*/ ,struct ice_aqc_get_phy_caps_data*,int /*<<< orphan*/ *) ; 
 struct ice_netdev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
ice_get_fecparam(struct net_device *netdev, struct ethtool_fecparam *fecparam)
{
	struct ice_netdev_priv *np = netdev_priv(netdev);
	struct ice_aqc_get_phy_caps_data *caps;
	struct ice_link_status *link_info;
	struct ice_vsi *vsi = np->vsi;
	struct ice_port_info *pi;
	enum ice_status status;
	int err = 0;

	pi = vsi->port_info;

	if (!pi)
		return -EOPNOTSUPP;
	link_info = &pi->phy.link_info;

	/* Set FEC mode based on negotiated link info */
	switch (link_info->fec_info) {
	case ICE_AQ_LINK_25G_KR_FEC_EN:
		fecparam->active_fec = ETHTOOL_FEC_BASER;
		break;
	case ICE_AQ_LINK_25G_RS_528_FEC_EN:
		/* fall through */
	case ICE_AQ_LINK_25G_RS_544_FEC_EN:
		fecparam->active_fec = ETHTOOL_FEC_RS;
		break;
	default:
		fecparam->active_fec = ETHTOOL_FEC_OFF;
		break;
	}

	caps = devm_kzalloc(&vsi->back->pdev->dev, sizeof(*caps), GFP_KERNEL);
	if (!caps)
		return -ENOMEM;

	status = ice_aq_get_phy_caps(pi, false, ICE_AQC_REPORT_TOPO_CAP,
				     caps, NULL);
	if (status) {
		err = -EAGAIN;
		goto done;
	}

	/* Set supported/configured FEC modes based on PHY capability */
	if (caps->caps & ICE_AQC_PHY_EN_AUTO_FEC)
		fecparam->fec |= ETHTOOL_FEC_AUTO;
	if (caps->link_fec_options & ICE_AQC_PHY_FEC_10G_KR_40G_KR4_EN ||
	    caps->link_fec_options & ICE_AQC_PHY_FEC_10G_KR_40G_KR4_REQ ||
	    caps->link_fec_options & ICE_AQC_PHY_FEC_25G_KR_CLAUSE74_EN ||
	    caps->link_fec_options & ICE_AQC_PHY_FEC_25G_KR_REQ)
		fecparam->fec |= ETHTOOL_FEC_BASER;
	if (caps->link_fec_options & ICE_AQC_PHY_FEC_25G_RS_528_REQ ||
	    caps->link_fec_options & ICE_AQC_PHY_FEC_25G_RS_544_REQ ||
	    caps->link_fec_options & ICE_AQC_PHY_FEC_25G_RS_CLAUSE91_EN)
		fecparam->fec |= ETHTOOL_FEC_RS;
	if (caps->link_fec_options == 0)
		fecparam->fec |= ETHTOOL_FEC_OFF;

done:
	devm_kfree(&vsi->back->pdev->dev, caps);
	return err;
}