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
struct TYPE_3__ {int get; int /*<<< orphan*/  msg; } ;
union nic_mbx {TYPE_1__ pfc; } ;
struct TYPE_4__ {int /*<<< orphan*/  fc_tx; int /*<<< orphan*/  fc_rx; int /*<<< orphan*/  autoneg; } ;
struct nicvf {scalar_t__ mac_type; TYPE_2__ pfc; } ;
struct net_device {int dummy; } ;
struct ethtool_pauseparam {int /*<<< orphan*/  tx_pause; int /*<<< orphan*/  rx_pause; int /*<<< orphan*/  autoneg; } ;

/* Variables and functions */
 scalar_t__ BGX_MODE_QSGMII ; 
 scalar_t__ BGX_MODE_RGMII ; 
 scalar_t__ BGX_MODE_SGMII ; 
 int /*<<< orphan*/  NIC_MBOX_MSG_PFC ; 
 struct nicvf* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  nicvf_send_msg_to_pf (struct nicvf*,union nic_mbx*) ; 

__attribute__((used)) static void nicvf_get_pauseparam(struct net_device *dev,
				 struct ethtool_pauseparam *pause)
{
	struct nicvf *nic = netdev_priv(dev);
	union nic_mbx mbx = {};

	/* Supported only for 10G/40G interfaces */
	if ((nic->mac_type == BGX_MODE_SGMII) ||
	    (nic->mac_type == BGX_MODE_QSGMII) ||
	    (nic->mac_type == BGX_MODE_RGMII))
		return;

	mbx.pfc.msg = NIC_MBOX_MSG_PFC;
	mbx.pfc.get = 1;
	if (!nicvf_send_msg_to_pf(nic, &mbx)) {
		pause->autoneg = nic->pfc.autoneg;
		pause->rx_pause = nic->pfc.fc_rx;
		pause->tx_pause = nic->pfc.fc_tx;
	}
}