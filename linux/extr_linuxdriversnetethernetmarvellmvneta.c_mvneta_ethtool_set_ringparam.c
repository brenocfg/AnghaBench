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
struct mvneta_port {int /*<<< orphan*/  tx_ring_size; scalar_t__ rx_ring_size; } ;
struct ethtool_ringparam {scalar_t__ rx_pending; int /*<<< orphan*/  tx_pending; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ MVNETA_MAX_RXD ; 
 int MVNETA_MAX_SKB_DESCS ; 
 int /*<<< orphan*/  MVNETA_MAX_TXD ; 
 int /*<<< orphan*/  clamp_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ mvneta_open (struct net_device*) ; 
 int /*<<< orphan*/  mvneta_stop (struct net_device*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct mvneta_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  u16 ; 

__attribute__((used)) static int mvneta_ethtool_set_ringparam(struct net_device *dev,
					struct ethtool_ringparam *ring)
{
	struct mvneta_port *pp = netdev_priv(dev);

	if ((ring->rx_pending == 0) || (ring->tx_pending == 0))
		return -EINVAL;
	pp->rx_ring_size = ring->rx_pending < MVNETA_MAX_RXD ?
		ring->rx_pending : MVNETA_MAX_RXD;

	pp->tx_ring_size = clamp_t(u16, ring->tx_pending,
				   MVNETA_MAX_SKB_DESCS * 2, MVNETA_MAX_TXD);
	if (pp->tx_ring_size != ring->tx_pending)
		netdev_warn(dev, "TX queue size set to %u (requested %u)\n",
			    pp->tx_ring_size, ring->tx_pending);

	if (netif_running(dev)) {
		mvneta_stop(dev);
		if (mvneta_open(dev)) {
			netdev_err(dev,
				   "error on opening device after ring param change\n");
			return -ENOMEM;
		}
	}

	return 0;
}