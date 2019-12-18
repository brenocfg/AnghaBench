#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ice_vsi {int current_isup; int /*<<< orphan*/  netdev; TYPE_5__* back; TYPE_6__* port_info; } ;
struct ice_aqc_get_phy_caps_data {int link_fec_options; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
struct TYPE_8__ {int link_speed; int fec_info; int an_info; } ;
struct TYPE_9__ {TYPE_2__ link_info; } ;
struct TYPE_7__ {int current_mode; } ;
struct TYPE_12__ {TYPE_3__ phy; TYPE_1__ fc; } ;
struct TYPE_11__ {TYPE_4__* pdev; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ICE_AQC_PHY_FEC_10G_KR_40G_KR4_REQ ; 
 int ICE_AQC_PHY_FEC_25G_KR_REQ ; 
 int ICE_AQC_PHY_FEC_25G_RS_528_REQ ; 
 int ICE_AQC_PHY_FEC_25G_RS_544_REQ ; 
 int /*<<< orphan*/  ICE_AQC_REPORT_SW_CFG ; 
 int ICE_AQ_AN_COMPLETED ; 
#define  ICE_AQ_LINK_25G_KR_FEC_EN 144 
#define  ICE_AQ_LINK_25G_RS_528_FEC_EN 143 
#define  ICE_AQ_LINK_25G_RS_544_FEC_EN 142 
#define  ICE_AQ_LINK_SPEED_1000MB 141 
#define  ICE_AQ_LINK_SPEED_100GB 140 
#define  ICE_AQ_LINK_SPEED_100MB 139 
#define  ICE_AQ_LINK_SPEED_10GB 138 
#define  ICE_AQ_LINK_SPEED_20GB 137 
#define  ICE_AQ_LINK_SPEED_2500MB 136 
#define  ICE_AQ_LINK_SPEED_25GB 135 
#define  ICE_AQ_LINK_SPEED_40GB 134 
#define  ICE_AQ_LINK_SPEED_50GB 133 
#define  ICE_AQ_LINK_SPEED_5GB 132 
#define  ICE_FC_FULL 131 
#define  ICE_FC_NONE 130 
#define  ICE_FC_RX_PAUSE 129 
#define  ICE_FC_TX_PAUSE 128 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ *,struct ice_aqc_get_phy_caps_data*) ; 
 struct ice_aqc_get_phy_caps_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int ice_aq_get_phy_caps (TYPE_6__*,int,int /*<<< orphan*/ ,struct ice_aqc_get_phy_caps_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_print_topo_conflict (struct ice_vsi*) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,...) ; 

void ice_print_link_msg(struct ice_vsi *vsi, bool isup)
{
	struct ice_aqc_get_phy_caps_data *caps;
	enum ice_status status;
	const char *fec_req;
	const char *speed;
	const char *fec;
	const char *fc;
	const char *an;

	if (!vsi)
		return;

	if (vsi->current_isup == isup)
		return;

	vsi->current_isup = isup;

	if (!isup) {
		netdev_info(vsi->netdev, "NIC Link is Down\n");
		return;
	}

	switch (vsi->port_info->phy.link_info.link_speed) {
	case ICE_AQ_LINK_SPEED_100GB:
		speed = "100 G";
		break;
	case ICE_AQ_LINK_SPEED_50GB:
		speed = "50 G";
		break;
	case ICE_AQ_LINK_SPEED_40GB:
		speed = "40 G";
		break;
	case ICE_AQ_LINK_SPEED_25GB:
		speed = "25 G";
		break;
	case ICE_AQ_LINK_SPEED_20GB:
		speed = "20 G";
		break;
	case ICE_AQ_LINK_SPEED_10GB:
		speed = "10 G";
		break;
	case ICE_AQ_LINK_SPEED_5GB:
		speed = "5 G";
		break;
	case ICE_AQ_LINK_SPEED_2500MB:
		speed = "2.5 G";
		break;
	case ICE_AQ_LINK_SPEED_1000MB:
		speed = "1 G";
		break;
	case ICE_AQ_LINK_SPEED_100MB:
		speed = "100 M";
		break;
	default:
		speed = "Unknown";
		break;
	}

	switch (vsi->port_info->fc.current_mode) {
	case ICE_FC_FULL:
		fc = "Rx/Tx";
		break;
	case ICE_FC_TX_PAUSE:
		fc = "Tx";
		break;
	case ICE_FC_RX_PAUSE:
		fc = "Rx";
		break;
	case ICE_FC_NONE:
		fc = "None";
		break;
	default:
		fc = "Unknown";
		break;
	}

	/* Get FEC mode based on negotiated link info */
	switch (vsi->port_info->phy.link_info.fec_info) {
	case ICE_AQ_LINK_25G_RS_528_FEC_EN:
		/* fall through */
	case ICE_AQ_LINK_25G_RS_544_FEC_EN:
		fec = "RS-FEC";
		break;
	case ICE_AQ_LINK_25G_KR_FEC_EN:
		fec = "FC-FEC/BASE-R";
		break;
	default:
		fec = "NONE";
		break;
	}

	/* check if autoneg completed, might be false due to not supported */
	if (vsi->port_info->phy.link_info.an_info & ICE_AQ_AN_COMPLETED)
		an = "True";
	else
		an = "False";

	/* Get FEC mode requested based on PHY caps last SW configuration */
	caps = devm_kzalloc(&vsi->back->pdev->dev, sizeof(*caps), GFP_KERNEL);
	if (!caps) {
		fec_req = "Unknown";
		goto done;
	}

	status = ice_aq_get_phy_caps(vsi->port_info, false,
				     ICE_AQC_REPORT_SW_CFG, caps, NULL);
	if (status)
		netdev_info(vsi->netdev, "Get phy capability failed.\n");

	if (caps->link_fec_options & ICE_AQC_PHY_FEC_25G_RS_528_REQ ||
	    caps->link_fec_options & ICE_AQC_PHY_FEC_25G_RS_544_REQ)
		fec_req = "RS-FEC";
	else if (caps->link_fec_options & ICE_AQC_PHY_FEC_10G_KR_40G_KR4_REQ ||
		 caps->link_fec_options & ICE_AQC_PHY_FEC_25G_KR_REQ)
		fec_req = "FC-FEC/BASE-R";
	else
		fec_req = "NONE";

	devm_kfree(&vsi->back->pdev->dev, caps);

done:
	netdev_info(vsi->netdev, "NIC Link is up %sbps, Requested FEC: %s, FEC: %s, Autoneg: %s, Flow Control: %s\n",
		    speed, fec_req, fec, an, fc);
	ice_print_topo_conflict(vsi);
}