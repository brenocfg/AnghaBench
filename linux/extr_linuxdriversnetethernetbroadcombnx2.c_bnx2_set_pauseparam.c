#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct net_device {int dummy; } ;
struct ethtool_pauseparam {scalar_t__ autoneg; scalar_t__ tx_pause; scalar_t__ rx_pause; } ;
struct bnx2 {int /*<<< orphan*/  phy_lock; int /*<<< orphan*/  phy_port; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  req_flow_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_FLOW_CTRL ; 
 int /*<<< orphan*/  FLOW_CTRL_RX ; 
 int /*<<< orphan*/  FLOW_CTRL_TX ; 
 int /*<<< orphan*/  bnx2_setup_phy (struct bnx2*,int /*<<< orphan*/ ) ; 
 struct bnx2* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bnx2_set_pauseparam(struct net_device *dev, struct ethtool_pauseparam *epause)
{
	struct bnx2 *bp = netdev_priv(dev);

	bp->req_flow_ctrl = 0;
	if (epause->rx_pause)
		bp->req_flow_ctrl |= FLOW_CTRL_RX;
	if (epause->tx_pause)
		bp->req_flow_ctrl |= FLOW_CTRL_TX;

	if (epause->autoneg) {
		bp->autoneg |= AUTONEG_FLOW_CTRL;
	}
	else {
		bp->autoneg &= ~AUTONEG_FLOW_CTRL;
	}

	if (netif_running(dev)) {
		spin_lock_bh(&bp->phy_lock);
		bnx2_setup_phy(bp, bp->phy_port);
		spin_unlock_bh(&bp->phy_lock);
	}

	return 0;
}