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
struct ionic_lif {int /*<<< orphan*/  nrxq_descs; int /*<<< orphan*/  ntxq_descs; } ;
struct ethtool_ringparam {int /*<<< orphan*/  rx_pending; void* rx_max_pending; int /*<<< orphan*/  tx_pending; void* tx_max_pending; } ;

/* Variables and functions */
 void* IONIC_MAX_TXRX_DESC ; 
 struct ionic_lif* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void ionic_get_ringparam(struct net_device *netdev,
				struct ethtool_ringparam *ring)
{
	struct ionic_lif *lif = netdev_priv(netdev);

	ring->tx_max_pending = IONIC_MAX_TXRX_DESC;
	ring->tx_pending = lif->ntxq_descs;
	ring->rx_max_pending = IONIC_MAX_TXRX_DESC;
	ring->rx_pending = lif->nrxq_descs;
}