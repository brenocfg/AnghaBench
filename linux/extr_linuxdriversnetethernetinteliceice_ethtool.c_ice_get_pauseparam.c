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
struct net_device {int dummy; } ;
struct TYPE_7__ {scalar_t__ current_mode; } ;
struct TYPE_5__ {int an_info; } ;
struct TYPE_6__ {TYPE_1__ link_info; } ;
struct ice_port_info {TYPE_3__ fc; TYPE_2__ phy; } ;
struct ice_netdev_priv {TYPE_4__* vsi; } ;
struct ethtool_pauseparam {int rx_pause; int tx_pause; int /*<<< orphan*/  autoneg; } ;
struct TYPE_8__ {struct ice_port_info* port_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int ICE_AQ_AN_COMPLETED ; 
 scalar_t__ ICE_FC_FULL ; 
 scalar_t__ ICE_FC_RX_PAUSE ; 
 scalar_t__ ICE_FC_TX_PAUSE ; 
 struct ice_netdev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void
ice_get_pauseparam(struct net_device *netdev, struct ethtool_pauseparam *pause)
{
	struct ice_netdev_priv *np = netdev_priv(netdev);
	struct ice_port_info *pi;

	pi = np->vsi->port_info;
	pause->autoneg =
		((pi->phy.link_info.an_info & ICE_AQ_AN_COMPLETED) ?
		 AUTONEG_ENABLE : AUTONEG_DISABLE);

	if (pi->fc.current_mode == ICE_FC_RX_PAUSE) {
		pause->rx_pause = 1;
	} else if (pi->fc.current_mode == ICE_FC_TX_PAUSE) {
		pause->tx_pause = 1;
	} else if (pi->fc.current_mode == ICE_FC_FULL) {
		pause->rx_pause = 1;
		pause->tx_pause = 1;
	}
}