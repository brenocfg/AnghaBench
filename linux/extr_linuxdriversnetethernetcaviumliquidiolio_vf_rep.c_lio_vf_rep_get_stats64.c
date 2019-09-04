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
struct rtnl_link_stats64 {int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct lio_vf_rep_desc {TYPE_1__ stats; } ;

/* Variables and functions */
 struct lio_vf_rep_desc* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void
lio_vf_rep_get_stats64(struct net_device *dev,
		       struct rtnl_link_stats64 *stats64)
{
	struct lio_vf_rep_desc *vf_rep = netdev_priv(dev);

	/* Swap tx and rx stats as VF rep is a switch port */
	stats64->tx_packets = vf_rep->stats.rx_packets;
	stats64->tx_bytes   = vf_rep->stats.rx_bytes;
	stats64->tx_dropped = vf_rep->stats.rx_dropped;

	stats64->rx_packets = vf_rep->stats.tx_packets;
	stats64->rx_bytes   = vf_rep->stats.tx_bytes;
	stats64->rx_dropped = vf_rep->stats.tx_dropped;
}