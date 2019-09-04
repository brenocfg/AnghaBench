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
struct qede_dev {int /*<<< orphan*/  q_num_tx_buffers; int /*<<< orphan*/  q_num_rx_buffers; } ;
struct net_device {int dummy; } ;
struct ethtool_ringparam {int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  tx_max_pending; int /*<<< orphan*/  rx_pending; int /*<<< orphan*/  rx_max_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  NUM_RX_BDS_MAX ; 
 int /*<<< orphan*/  NUM_TX_BDS_MAX ; 
 struct qede_dev* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void qede_get_ringparam(struct net_device *dev,
			       struct ethtool_ringparam *ering)
{
	struct qede_dev *edev = netdev_priv(dev);

	ering->rx_max_pending = NUM_RX_BDS_MAX;
	ering->rx_pending = edev->q_num_rx_buffers;
	ering->tx_max_pending = NUM_TX_BDS_MAX;
	ering->tx_pending = edev->q_num_tx_buffers;
}