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
struct ionic_lif {int /*<<< orphan*/  rx_coalesce_usecs; } ;
struct ethtool_coalesce {int /*<<< orphan*/  rx_coalesce_usecs; int /*<<< orphan*/  tx_coalesce_usecs; } ;

/* Variables and functions */
 struct ionic_lif* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ionic_get_coalesce(struct net_device *netdev,
			      struct ethtool_coalesce *coalesce)
{
	struct ionic_lif *lif = netdev_priv(netdev);

	/* Tx uses Rx interrupt */
	coalesce->tx_coalesce_usecs = lif->rx_coalesce_usecs;
	coalesce->rx_coalesce_usecs = lif->rx_coalesce_usecs;

	return 0;
}