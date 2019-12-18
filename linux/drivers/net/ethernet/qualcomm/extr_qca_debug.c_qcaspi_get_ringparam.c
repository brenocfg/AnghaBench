#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  count; } ;
struct qcaspi {TYPE_1__ txr; } ;
struct net_device {int dummy; } ;
struct ethtool_ringparam {int rx_max_pending; int rx_pending; int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  tx_max_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  TX_RING_MAX_LEN ; 
 struct qcaspi* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void
qcaspi_get_ringparam(struct net_device *dev, struct ethtool_ringparam *ring)
{
	struct qcaspi *qca = netdev_priv(dev);

	ring->rx_max_pending = 4;
	ring->tx_max_pending = TX_RING_MAX_LEN;
	ring->rx_pending = 4;
	ring->tx_pending = qca->txr.count;
}