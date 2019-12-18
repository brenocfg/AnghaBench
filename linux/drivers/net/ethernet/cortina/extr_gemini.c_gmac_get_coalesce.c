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
struct gemini_ethernet_port {int rx_coalesce_nsecs; int /*<<< orphan*/  irq_every_tx_packets; } ;
struct ethtool_coalesce {int rx_max_coalesced_frames; int rx_coalesce_usecs; int /*<<< orphan*/  tx_max_coalesced_frames; } ;

/* Variables and functions */
 struct gemini_ethernet_port* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int gmac_get_coalesce(struct net_device *netdev,
			     struct ethtool_coalesce *ecmd)
{
	struct gemini_ethernet_port *port = netdev_priv(netdev);

	ecmd->rx_max_coalesced_frames = 1;
	ecmd->tx_max_coalesced_frames = port->irq_every_tx_packets;
	ecmd->rx_coalesce_usecs = port->rx_coalesce_nsecs / 1000;

	return 0;
}