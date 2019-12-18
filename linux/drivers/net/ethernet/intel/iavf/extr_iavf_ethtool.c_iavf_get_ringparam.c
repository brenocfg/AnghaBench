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
struct iavf_adapter {int /*<<< orphan*/  tx_desc_count; int /*<<< orphan*/  rx_desc_count; } ;
struct ethtool_ringparam {int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  rx_pending; int /*<<< orphan*/  tx_max_pending; int /*<<< orphan*/  rx_max_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  IAVF_MAX_RXD ; 
 int /*<<< orphan*/  IAVF_MAX_TXD ; 
 struct iavf_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void iavf_get_ringparam(struct net_device *netdev,
			       struct ethtool_ringparam *ring)
{
	struct iavf_adapter *adapter = netdev_priv(netdev);

	ring->rx_max_pending = IAVF_MAX_RXD;
	ring->tx_max_pending = IAVF_MAX_TXD;
	ring->rx_pending = adapter->rx_desc_count;
	ring->tx_pending = adapter->tx_desc_count;
}