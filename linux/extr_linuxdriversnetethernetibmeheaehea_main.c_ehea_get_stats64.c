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
typedef  void* u64 ;
struct rtnl_link_stats64 {int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  multicast; void* rx_packets; void* tx_bytes; void* rx_bytes; void* tx_packets; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  multicast; } ;
struct ehea_port {int num_def_qps; TYPE_2__ stats; TYPE_1__* port_res; } ;
struct TYPE_3__ {scalar_t__ tx_bytes; scalar_t__ tx_packets; scalar_t__ rx_bytes; scalar_t__ rx_packets; } ;

/* Variables and functions */
 struct ehea_port* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void ehea_get_stats64(struct net_device *dev,
			     struct rtnl_link_stats64 *stats)
{
	struct ehea_port *port = netdev_priv(dev);
	u64 rx_packets = 0, tx_packets = 0, rx_bytes = 0, tx_bytes = 0;
	int i;

	for (i = 0; i < port->num_def_qps; i++) {
		rx_packets += port->port_res[i].rx_packets;
		rx_bytes   += port->port_res[i].rx_bytes;
	}

	for (i = 0; i < port->num_def_qps; i++) {
		tx_packets += port->port_res[i].tx_packets;
		tx_bytes   += port->port_res[i].tx_bytes;
	}

	stats->tx_packets = tx_packets;
	stats->rx_bytes = rx_bytes;
	stats->tx_bytes = tx_bytes;
	stats->rx_packets = rx_packets;

	stats->multicast = port->stats.multicast;
	stats->rx_errors = port->stats.rx_errors;
}