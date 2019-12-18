#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct mvpp2_port {int /*<<< orphan*/  tx_time_coal; TYPE_1__** txqs; TYPE_2__** rxqs; } ;
struct ethtool_coalesce {int /*<<< orphan*/  tx_coalesce_usecs; int /*<<< orphan*/  tx_max_coalesced_frames; int /*<<< orphan*/  rx_max_coalesced_frames; int /*<<< orphan*/  rx_coalesce_usecs; } ;
struct TYPE_4__ {int /*<<< orphan*/  pkts_coal; int /*<<< orphan*/  time_coal; } ;
struct TYPE_3__ {int /*<<< orphan*/  done_pkts_coal; } ;

/* Variables and functions */
 struct mvpp2_port* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mvpp2_ethtool_get_coalesce(struct net_device *dev,
				      struct ethtool_coalesce *c)
{
	struct mvpp2_port *port = netdev_priv(dev);

	c->rx_coalesce_usecs       = port->rxqs[0]->time_coal;
	c->rx_max_coalesced_frames = port->rxqs[0]->pkts_coal;
	c->tx_max_coalesced_frames = port->txqs[0]->done_pkts_coal;
	c->tx_coalesce_usecs       = port->tx_time_coal;
	return 0;
}