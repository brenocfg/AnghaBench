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
struct pcnet32_private {int /*<<< orphan*/  rx_ring_size; int /*<<< orphan*/  tx_ring_size; } ;
struct net_device {int dummy; } ;
struct ethtool_ringparam {int /*<<< orphan*/  rx_pending; int /*<<< orphan*/  rx_max_pending; int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  tx_max_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  RX_MAX_RING_SIZE ; 
 int /*<<< orphan*/  TX_MAX_RING_SIZE ; 
 struct pcnet32_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void pcnet32_get_ringparam(struct net_device *dev,
				  struct ethtool_ringparam *ering)
{
	struct pcnet32_private *lp = netdev_priv(dev);

	ering->tx_max_pending = TX_MAX_RING_SIZE;
	ering->tx_pending = lp->tx_ring_size;
	ering->rx_max_pending = RX_MAX_RING_SIZE;
	ering->rx_pending = lp->rx_ring_size;
}