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
typedef  void* u16 ;
struct net_device {int dummy; } ;
struct ethtool_coalesce {scalar_t__ tx_coalesce_usecs; scalar_t__ rx_coalesce_usecs; } ;
struct bnx2x {scalar_t__ rx_ticks; scalar_t__ tx_ticks; } ;

/* Variables and functions */
 scalar_t__ BNX2X_MAX_COALESCE_TOUT ; 
 int /*<<< orphan*/  bnx2x_update_coalesce (struct bnx2x*) ; 
 struct bnx2x* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 

__attribute__((used)) static int bnx2x_set_coalesce(struct net_device *dev,
			      struct ethtool_coalesce *coal)
{
	struct bnx2x *bp = netdev_priv(dev);

	bp->rx_ticks = (u16)coal->rx_coalesce_usecs;
	if (bp->rx_ticks > BNX2X_MAX_COALESCE_TOUT)
		bp->rx_ticks = BNX2X_MAX_COALESCE_TOUT;

	bp->tx_ticks = (u16)coal->tx_coalesce_usecs;
	if (bp->tx_ticks > BNX2X_MAX_COALESCE_TOUT)
		bp->tx_ticks = BNX2X_MAX_COALESCE_TOUT;

	if (netif_running(dev))
		bnx2x_update_coalesce(bp);

	return 0;
}