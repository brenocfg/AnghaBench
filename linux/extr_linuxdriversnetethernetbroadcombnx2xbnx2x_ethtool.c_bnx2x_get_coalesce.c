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
struct ethtool_coalesce {int /*<<< orphan*/  tx_coalesce_usecs; int /*<<< orphan*/  rx_coalesce_usecs; } ;
struct bnx2x {int /*<<< orphan*/  tx_ticks; int /*<<< orphan*/  rx_ticks; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct ethtool_coalesce*,int /*<<< orphan*/ ,int) ; 
 struct bnx2x* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int bnx2x_get_coalesce(struct net_device *dev,
			      struct ethtool_coalesce *coal)
{
	struct bnx2x *bp = netdev_priv(dev);

	memset(coal, 0, sizeof(struct ethtool_coalesce));

	coal->rx_coalesce_usecs = bp->rx_ticks;
	coal->tx_coalesce_usecs = bp->tx_ticks;

	return 0;
}