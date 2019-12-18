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
struct ftgmac100 {scalar_t__ new_rx_q_entries; scalar_t__ new_tx_q_entries; int /*<<< orphan*/  reset_task; } ;
struct ethtool_ringparam {scalar_t__ rx_pending; scalar_t__ tx_pending; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MAX_RX_QUEUE_ENTRIES ; 
 scalar_t__ MAX_TX_QUEUE_ENTRIES ; 
 scalar_t__ MIN_RX_QUEUE_ENTRIES ; 
 scalar_t__ MIN_TX_QUEUE_ENTRIES ; 
 int /*<<< orphan*/  is_power_of_2 (scalar_t__) ; 
 struct ftgmac100* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ftgmac100_set_ringparam(struct net_device *netdev,
				   struct ethtool_ringparam *ering)
{
	struct ftgmac100 *priv = netdev_priv(netdev);

	if (ering->rx_pending > MAX_RX_QUEUE_ENTRIES ||
	    ering->tx_pending > MAX_TX_QUEUE_ENTRIES ||
	    ering->rx_pending < MIN_RX_QUEUE_ENTRIES ||
	    ering->tx_pending < MIN_TX_QUEUE_ENTRIES ||
	    !is_power_of_2(ering->rx_pending) ||
	    !is_power_of_2(ering->tx_pending))
		return -EINVAL;

	priv->new_rx_q_entries = ering->rx_pending;
	priv->new_tx_q_entries = ering->tx_pending;
	if (netif_running(netdev))
		schedule_work(&priv->reset_task);

	return 0;
}