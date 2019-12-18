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
struct ethtool_pauseparam {int dummy; } ;
struct axienet_local {int /*<<< orphan*/  phylink; } ;

/* Variables and functions */
 struct axienet_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phylink_ethtool_get_pauseparam (int /*<<< orphan*/ ,struct ethtool_pauseparam*) ; 

__attribute__((used)) static void
axienet_ethtools_get_pauseparam(struct net_device *ndev,
				struct ethtool_pauseparam *epauseparm)
{
	struct axienet_local *lp = netdev_priv(ndev);

	phylink_ethtool_get_pauseparam(lp->phylink, epauseparm);
}