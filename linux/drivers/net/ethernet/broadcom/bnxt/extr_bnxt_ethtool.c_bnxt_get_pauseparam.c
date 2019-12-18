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
struct ethtool_pauseparam {int autoneg; int rx_pause; int tx_pause; } ;
struct bnxt_link_info {int autoneg; int req_flow_ctrl; } ;
struct bnxt {struct bnxt_link_info link_info; } ;

/* Variables and functions */
 int BNXT_AUTONEG_FLOW_CTRL ; 
 int BNXT_LINK_PAUSE_RX ; 
 int BNXT_LINK_PAUSE_TX ; 
 scalar_t__ BNXT_VF (struct bnxt*) ; 
 struct bnxt* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void bnxt_get_pauseparam(struct net_device *dev,
				struct ethtool_pauseparam *epause)
{
	struct bnxt *bp = netdev_priv(dev);
	struct bnxt_link_info *link_info = &bp->link_info;

	if (BNXT_VF(bp))
		return;
	epause->autoneg = !!(link_info->autoneg & BNXT_AUTONEG_FLOW_CTRL);
	epause->rx_pause = !!(link_info->req_flow_ctrl & BNXT_LINK_PAUSE_RX);
	epause->tx_pause = !!(link_info->req_flow_ctrl & BNXT_LINK_PAUSE_TX);
}