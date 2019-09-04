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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct net_device {scalar_t__ phydev; } ;
struct hnae3_handle {TYPE_4__* ae_algo; } ;
struct TYPE_6__ {int /*<<< orphan*/  mdio_support; int /*<<< orphan*/  eth_tp_mdix; int /*<<< orphan*/  eth_tp_mdix_ctrl; int /*<<< orphan*/  port; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  autoneg; } ;
struct TYPE_5__ {int /*<<< orphan*/  advertising; int /*<<< orphan*/  supported; } ;
struct ethtool_link_ksettings {TYPE_2__ base; TYPE_1__ link_modes; } ;
struct TYPE_8__ {TYPE_3__* ops; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* get_flowctrl_adv ) (struct hnae3_handle*,int*) ;int /*<<< orphan*/  (* get_mdix_mode ) (struct hnae3_handle*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* get_port_type ) (struct hnae3_handle*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* get_link_mode ) (struct hnae3_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* get_ksettings_an_result ) (struct hnae3_handle*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int ADVERTISED_Asym_Pause ; 
 int ADVERTISED_Pause ; 
 int /*<<< orphan*/  Asym_Pause ; 
 int /*<<< orphan*/  DUPLEX_UNKNOWN ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ETH_MDIO_SUPPORTS_C22 ; 
 int /*<<< orphan*/  PORT_NONE ; 
 int /*<<< orphan*/  Pause ; 
 int /*<<< orphan*/  SPEED_UNKNOWN ; 
 int /*<<< orphan*/  advertising ; 
 int /*<<< orphan*/  ethtool_link_ksettings_add_link_mode (struct ethtool_link_ksettings*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hnae3_handle* hns3_get_handle (struct net_device*) ; 
 int /*<<< orphan*/  hns3_get_link (struct net_device*) ; 
 int /*<<< orphan*/  phy_ethtool_ksettings_get (scalar_t__,struct ethtool_link_ksettings*) ; 
 int /*<<< orphan*/  stub1 (struct hnae3_handle*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct hnae3_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct hnae3_handle*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (struct hnae3_handle*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub5 (struct hnae3_handle*,int*) ; 

__attribute__((used)) static int hns3_get_link_ksettings(struct net_device *netdev,
				   struct ethtool_link_ksettings *cmd)
{
	struct hnae3_handle *h = hns3_get_handle(netdev);
	u32 flowctrl_adv = 0;
	u8 link_stat;

	if (!h->ae_algo || !h->ae_algo->ops)
		return -EOPNOTSUPP;

	/* 1.auto_neg & speed & duplex from cmd */
	if (netdev->phydev) {
		phy_ethtool_ksettings_get(netdev->phydev, cmd);

		return 0;
	}

	if (h->ae_algo->ops->get_ksettings_an_result)
		h->ae_algo->ops->get_ksettings_an_result(h,
							 &cmd->base.autoneg,
							 &cmd->base.speed,
							 &cmd->base.duplex);
	else
		return -EOPNOTSUPP;

	link_stat = hns3_get_link(netdev);
	if (!link_stat) {
		cmd->base.speed = SPEED_UNKNOWN;
		cmd->base.duplex = DUPLEX_UNKNOWN;
	}

	/* 2.get link mode and port type*/
	if (h->ae_algo->ops->get_link_mode)
		h->ae_algo->ops->get_link_mode(h,
					       cmd->link_modes.supported,
					       cmd->link_modes.advertising);

	cmd->base.port = PORT_NONE;
	if (h->ae_algo->ops->get_port_type)
		h->ae_algo->ops->get_port_type(h,
					       &cmd->base.port);

	/* 3.mdix_ctrl&mdix get from phy reg */
	if (h->ae_algo->ops->get_mdix_mode)
		h->ae_algo->ops->get_mdix_mode(h, &cmd->base.eth_tp_mdix_ctrl,
					       &cmd->base.eth_tp_mdix);
	/* 4.mdio_support */
	cmd->base.mdio_support = ETH_MDIO_SUPPORTS_C22;

	/* 5.get flow control setttings */
	if (h->ae_algo->ops->get_flowctrl_adv)
		h->ae_algo->ops->get_flowctrl_adv(h, &flowctrl_adv);

	if (flowctrl_adv & ADVERTISED_Pause)
		ethtool_link_ksettings_add_link_mode(cmd, advertising,
						     Pause);

	if (flowctrl_adv & ADVERTISED_Asym_Pause)
		ethtool_link_ksettings_add_link_mode(cmd, advertising,
						     Asym_Pause);

	return 0;
}