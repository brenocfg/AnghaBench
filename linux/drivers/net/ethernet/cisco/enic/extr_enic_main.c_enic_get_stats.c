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
struct TYPE_4__ {scalar_t__ rx_drop; scalar_t__ rx_no_bufs; int /*<<< orphan*/  rx_multicast_frames_ok; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_bytes_ok; int /*<<< orphan*/  rx_frames_ok; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_drops; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_bytes_ok; int /*<<< orphan*/  tx_frames_ok; } ;
struct vnic_stats {TYPE_2__ rx; TYPE_1__ tx; } ;
struct rtnl_link_stats64 {scalar_t__ rx_dropped; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_over_errors; int /*<<< orphan*/  multicast; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {int dummy; } ;
struct enic {int /*<<< orphan*/  rq_bad_fcs; int /*<<< orphan*/  rq_truncated_pkts; } ;

/* Variables and functions */
 int ENOMEM ; 
 int enic_dev_stats_dump (struct enic*,struct vnic_stats**) ; 
 struct enic* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void enic_get_stats(struct net_device *netdev,
			   struct rtnl_link_stats64 *net_stats)
{
	struct enic *enic = netdev_priv(netdev);
	struct vnic_stats *stats;
	int err;

	err = enic_dev_stats_dump(enic, &stats);
	/* return only when pci_zalloc_consistent fails in vnic_dev_stats_dump
	 * For other failures, like devcmd failure, we return previously
	 * recorded stats.
	 */
	if (err == -ENOMEM)
		return;

	net_stats->tx_packets = stats->tx.tx_frames_ok;
	net_stats->tx_bytes = stats->tx.tx_bytes_ok;
	net_stats->tx_errors = stats->tx.tx_errors;
	net_stats->tx_dropped = stats->tx.tx_drops;

	net_stats->rx_packets = stats->rx.rx_frames_ok;
	net_stats->rx_bytes = stats->rx.rx_bytes_ok;
	net_stats->rx_errors = stats->rx.rx_errors;
	net_stats->multicast = stats->rx.rx_multicast_frames_ok;
	net_stats->rx_over_errors = enic->rq_truncated_pkts;
	net_stats->rx_crc_errors = enic->rq_bad_fcs;
	net_stats->rx_dropped = stats->rx.rx_no_bufs + stats->rx.rx_drop;
}