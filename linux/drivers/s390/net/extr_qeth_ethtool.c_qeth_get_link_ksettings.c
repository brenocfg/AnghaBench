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
struct TYPE_3__ {int link_type; } ;
struct qeth_card {TYPE_1__ info; } ;
struct net_device {struct qeth_card* ml_priv; } ;
struct TYPE_4__ {void* speed; void* duplex; void* port; void* eth_tp_mdix_ctrl; void* eth_tp_mdix; scalar_t__ mdio_support; scalar_t__ phy_address; int /*<<< orphan*/  autoneg; } ;
struct ethtool_link_ksettings {TYPE_2__ base; } ;
struct carrier_info {int card_type; int port_mode; int port_speed; } ;
typedef  enum qeth_link_types { ____Placeholder_qeth_link_types } qeth_link_types ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
#define  CARD_INFO_PORTM_FULLDUPLEX 146 
#define  CARD_INFO_PORTM_HALFDUPLEX 145 
#define  CARD_INFO_PORTS_100M 144 
#define  CARD_INFO_PORTS_10G 143 
#define  CARD_INFO_PORTS_10M 142 
#define  CARD_INFO_PORTS_1G 141 
#define  CARD_INFO_PORTS_25G 140 
#define  CARD_INFO_TYPE_10G_FIBRE_A 139 
#define  CARD_INFO_TYPE_10G_FIBRE_B 138 
#define  CARD_INFO_TYPE_1G_COPPER_A 137 
#define  CARD_INFO_TYPE_1G_COPPER_B 136 
#define  CARD_INFO_TYPE_1G_FIBRE_A 135 
#define  CARD_INFO_TYPE_1G_FIBRE_B 134 
 void* DUPLEX_FULL ; 
 void* DUPLEX_HALF ; 
 int EOPNOTSUPP ; 
 void* ETH_TP_MDI_INVALID ; 
 scalar_t__ IS_IQD (struct qeth_card*) ; 
 scalar_t__ IS_VM_NIC (struct qeth_card*) ; 
 void* PORT_FIBRE ; 
 void* PORT_TP ; 
#define  QETH_LINK_TYPE_10GBIT_ETH 133 
#define  QETH_LINK_TYPE_25GBIT_ETH 132 
#define  QETH_LINK_TYPE_FAST_ETH 131 
#define  QETH_LINK_TYPE_GBIT_ETH 130 
#define  QETH_LINK_TYPE_LANE_ETH100 129 
#define  QETH_LINK_TYPE_LANE_ETH1000 128 
 void* SPEED_10 ; 
 void* SPEED_100 ; 
 void* SPEED_1000 ; 
 void* SPEED_10000 ; 
 void* SPEED_25000 ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int,int,int) ; 
 int qeth_query_card_info (struct qeth_card*,struct carrier_info*) ; 
 int /*<<< orphan*/  qeth_set_cmd_adv_sup (struct ethtool_link_ksettings*,void*,void*) ; 

__attribute__((used)) static int qeth_get_link_ksettings(struct net_device *netdev,
				   struct ethtool_link_ksettings *cmd)
{
	struct qeth_card *card = netdev->ml_priv;
	enum qeth_link_types link_type;
	struct carrier_info carrier_info;
	int rc;

	if (IS_IQD(card) || IS_VM_NIC(card))
		link_type = QETH_LINK_TYPE_10GBIT_ETH;
	else
		link_type = card->info.link_type;

	cmd->base.duplex = DUPLEX_FULL;
	cmd->base.autoneg = AUTONEG_ENABLE;
	cmd->base.phy_address = 0;
	cmd->base.mdio_support = 0;
	cmd->base.eth_tp_mdix = ETH_TP_MDI_INVALID;
	cmd->base.eth_tp_mdix_ctrl = ETH_TP_MDI_INVALID;

	switch (link_type) {
	case QETH_LINK_TYPE_FAST_ETH:
	case QETH_LINK_TYPE_LANE_ETH100:
		cmd->base.speed = SPEED_100;
		cmd->base.port = PORT_TP;
		break;
	case QETH_LINK_TYPE_GBIT_ETH:
	case QETH_LINK_TYPE_LANE_ETH1000:
		cmd->base.speed = SPEED_1000;
		cmd->base.port = PORT_FIBRE;
		break;
	case QETH_LINK_TYPE_10GBIT_ETH:
		cmd->base.speed = SPEED_10000;
		cmd->base.port = PORT_FIBRE;
		break;
	case QETH_LINK_TYPE_25GBIT_ETH:
		cmd->base.speed = SPEED_25000;
		cmd->base.port = PORT_FIBRE;
		break;
	default:
		cmd->base.speed = SPEED_10;
		cmd->base.port = PORT_TP;
	}
	qeth_set_cmd_adv_sup(cmd, cmd->base.speed, cmd->base.port);

	/* Check if we can obtain more accurate information.	 */
	/* If QUERY_CARD_INFO command is not supported or fails, */
	/* just return the heuristics that was filled above.	 */
	rc = qeth_query_card_info(card, &carrier_info);
	if (rc == -EOPNOTSUPP) /* for old hardware, return heuristic */
		return 0;
	if (rc) /* report error from the hardware operation */
		return rc;
	/* on success, fill in the information got from the hardware */

	netdev_dbg(netdev,
	"card info: card_type=0x%02x, port_mode=0x%04x, port_speed=0x%08x\n",
			carrier_info.card_type,
			carrier_info.port_mode,
			carrier_info.port_speed);

	/* Update attributes for which we've obtained more authoritative */
	/* information, leave the rest the way they where filled above.  */
	switch (carrier_info.card_type) {
	case CARD_INFO_TYPE_1G_COPPER_A:
	case CARD_INFO_TYPE_1G_COPPER_B:
		cmd->base.port = PORT_TP;
		qeth_set_cmd_adv_sup(cmd, SPEED_1000, cmd->base.port);
		break;
	case CARD_INFO_TYPE_1G_FIBRE_A:
	case CARD_INFO_TYPE_1G_FIBRE_B:
		cmd->base.port = PORT_FIBRE;
		qeth_set_cmd_adv_sup(cmd, SPEED_1000, cmd->base.port);
		break;
	case CARD_INFO_TYPE_10G_FIBRE_A:
	case CARD_INFO_TYPE_10G_FIBRE_B:
		cmd->base.port = PORT_FIBRE;
		qeth_set_cmd_adv_sup(cmd, SPEED_10000, cmd->base.port);
		break;
	}

	switch (carrier_info.port_mode) {
	case CARD_INFO_PORTM_FULLDUPLEX:
		cmd->base.duplex = DUPLEX_FULL;
		break;
	case CARD_INFO_PORTM_HALFDUPLEX:
		cmd->base.duplex = DUPLEX_HALF;
		break;
	}

	switch (carrier_info.port_speed) {
	case CARD_INFO_PORTS_10M:
		cmd->base.speed = SPEED_10;
		break;
	case CARD_INFO_PORTS_100M:
		cmd->base.speed = SPEED_100;
		break;
	case CARD_INFO_PORTS_1G:
		cmd->base.speed = SPEED_1000;
		break;
	case CARD_INFO_PORTS_10G:
		cmd->base.speed = SPEED_10000;
		break;
	case CARD_INFO_PORTS_25G:
		cmd->base.speed = SPEED_25000;
		break;
	}

	return 0;
}