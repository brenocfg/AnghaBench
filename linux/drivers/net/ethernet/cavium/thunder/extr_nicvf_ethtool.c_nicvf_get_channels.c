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
struct nicvf {int /*<<< orphan*/  tx_queues; int /*<<< orphan*/  rx_queues; int /*<<< orphan*/  max_queues; } ;
struct net_device {int dummy; } ;
struct ethtool_channels {int /*<<< orphan*/  tx_count; int /*<<< orphan*/  rx_count; int /*<<< orphan*/  max_tx; int /*<<< orphan*/  max_rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct ethtool_channels*,int /*<<< orphan*/ ,int) ; 
 struct nicvf* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void nicvf_get_channels(struct net_device *dev,
			       struct ethtool_channels *channel)
{
	struct nicvf *nic = netdev_priv(dev);

	memset(channel, 0, sizeof(*channel));

	channel->max_rx = nic->max_queues;
	channel->max_tx = nic->max_queues;

	channel->rx_count = nic->rx_queues;
	channel->tx_count = nic->tx_queues;
}