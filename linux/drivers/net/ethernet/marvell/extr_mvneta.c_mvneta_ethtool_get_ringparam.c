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
struct mvneta_port {int /*<<< orphan*/  tx_ring_size; int /*<<< orphan*/  rx_ring_size; } ;
struct ethtool_ringparam {int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  rx_pending; int /*<<< orphan*/  tx_max_pending; int /*<<< orphan*/  rx_max_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVNETA_MAX_RXD ; 
 int /*<<< orphan*/  MVNETA_MAX_TXD ; 
 struct mvneta_port* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void mvneta_ethtool_get_ringparam(struct net_device *netdev,
					 struct ethtool_ringparam *ring)
{
	struct mvneta_port *pp = netdev_priv(netdev);

	ring->rx_max_pending = MVNETA_MAX_RXD;
	ring->tx_max_pending = MVNETA_MAX_TXD;
	ring->rx_pending = pp->rx_ring_size;
	ring->tx_pending = pp->tx_ring_size;
}