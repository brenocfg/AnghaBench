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
typedef  scalar_t__ u16 ;
struct net_device {int dummy; } ;
struct ethtool_ringparam {scalar_t__ rx_pending; scalar_t__ tx_pending; } ;

/* Variables and functions */
 scalar_t__ ALIGN (scalar_t__,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  IS_ALIGNED (scalar_t__,int) ; 
 scalar_t__ MVPP2_MAX_RXD_MAX ; 
 scalar_t__ MVPP2_MAX_SKB_DESCS ; 
 scalar_t__ MVPP2_MAX_TXD_MAX ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int mvpp2_check_ringparam_valid(struct net_device *dev,
				       struct ethtool_ringparam *ring)
{
	u16 new_rx_pending = ring->rx_pending;
	u16 new_tx_pending = ring->tx_pending;

	if (ring->rx_pending == 0 || ring->tx_pending == 0)
		return -EINVAL;

	if (ring->rx_pending > MVPP2_MAX_RXD_MAX)
		new_rx_pending = MVPP2_MAX_RXD_MAX;
	else if (!IS_ALIGNED(ring->rx_pending, 16))
		new_rx_pending = ALIGN(ring->rx_pending, 16);

	if (ring->tx_pending > MVPP2_MAX_TXD_MAX)
		new_tx_pending = MVPP2_MAX_TXD_MAX;
	else if (!IS_ALIGNED(ring->tx_pending, 32))
		new_tx_pending = ALIGN(ring->tx_pending, 32);

	/* The Tx ring size cannot be smaller than the minimum number of
	 * descriptors needed for TSO.
	 */
	if (new_tx_pending < MVPP2_MAX_SKB_DESCS)
		new_tx_pending = ALIGN(MVPP2_MAX_SKB_DESCS, 32);

	if (ring->rx_pending != new_rx_pending) {
		netdev_info(dev, "illegal Rx ring size value %d, round to %d\n",
			    ring->rx_pending, new_rx_pending);
		ring->rx_pending = new_rx_pending;
	}

	if (ring->tx_pending != new_tx_pending) {
		netdev_info(dev, "illegal Tx ring size value %d, round to %d\n",
			    ring->tx_pending, new_tx_pending);
		ring->tx_pending = new_tx_pending;
	}

	return 0;
}