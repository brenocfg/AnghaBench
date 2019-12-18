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
typedef  size_t u8 ;
struct rtnl_link_stats64 {scalar_t__ rx_dropped; scalar_t__ rx_errors; scalar_t__ rx_fifo_errors; scalar_t__ rx_bytes; scalar_t__ rx_packets; scalar_t__ tx_dropped; scalar_t__ tx_errors; scalar_t__ tx_carrier_errors; scalar_t__ tx_fifo_errors; scalar_t__ tx_bytes; scalar_t__ tx_packets; scalar_t__ rx_nohandler; } ;
struct TYPE_3__ {int /*<<< orphan*/  mcastbcast; } ;
struct opa_vnic_stats {struct rtnl_link_stats64 netstats; scalar_t__ rx_runt; scalar_t__ rx_oversize; TYPE_1__ rx_grp; scalar_t__ rx_drop_state; scalar_t__ tx_dlid_zero; scalar_t__ tx_drop_state; } ;
struct TYPE_4__ {scalar_t__ rx_dropped; scalar_t__ rx_errors; scalar_t__ rx_length_errors; int /*<<< orphan*/  multicast; scalar_t__ rx_fifo_errors; scalar_t__ rx_bytes; scalar_t__ rx_packets; scalar_t__ tx_dropped; scalar_t__ tx_errors; scalar_t__ tx_carrier_errors; scalar_t__ tx_fifo_errors; scalar_t__ tx_bytes; scalar_t__ tx_packets; } ;
struct net_device {TYPE_2__ stats; } ;
struct hfi1_vnic_vport_info {size_t num_tx_q; size_t num_rx_q; struct opa_vnic_stats* stats; struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SUM_GRP_COUNTERS (struct opa_vnic_stats*,struct opa_vnic_stats*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rx_grp ; 
 int /*<<< orphan*/  tx_grp ; 

__attribute__((used)) static void hfi1_vnic_update_stats(struct hfi1_vnic_vport_info *vinfo,
				   struct opa_vnic_stats *stats)
{
	struct net_device *netdev = vinfo->netdev;
	u8 i;

	/* add tx counters on different queues */
	for (i = 0; i < vinfo->num_tx_q; i++) {
		struct opa_vnic_stats *qstats = &vinfo->stats[i];
		struct rtnl_link_stats64 *qnstats = &vinfo->stats[i].netstats;

		stats->netstats.tx_fifo_errors += qnstats->tx_fifo_errors;
		stats->netstats.tx_carrier_errors += qnstats->tx_carrier_errors;
		stats->tx_drop_state += qstats->tx_drop_state;
		stats->tx_dlid_zero += qstats->tx_dlid_zero;

		SUM_GRP_COUNTERS(stats, qstats, tx_grp);
		stats->netstats.tx_packets += qnstats->tx_packets;
		stats->netstats.tx_bytes += qnstats->tx_bytes;
	}

	/* add rx counters on different queues */
	for (i = 0; i < vinfo->num_rx_q; i++) {
		struct opa_vnic_stats *qstats = &vinfo->stats[i];
		struct rtnl_link_stats64 *qnstats = &vinfo->stats[i].netstats;

		stats->netstats.rx_fifo_errors += qnstats->rx_fifo_errors;
		stats->netstats.rx_nohandler += qnstats->rx_nohandler;
		stats->rx_drop_state += qstats->rx_drop_state;
		stats->rx_oversize += qstats->rx_oversize;
		stats->rx_runt += qstats->rx_runt;

		SUM_GRP_COUNTERS(stats, qstats, rx_grp);
		stats->netstats.rx_packets += qnstats->rx_packets;
		stats->netstats.rx_bytes += qnstats->rx_bytes;
	}

	stats->netstats.tx_errors = stats->netstats.tx_fifo_errors +
				    stats->netstats.tx_carrier_errors +
				    stats->tx_drop_state + stats->tx_dlid_zero;
	stats->netstats.tx_dropped = stats->netstats.tx_errors;

	stats->netstats.rx_errors = stats->netstats.rx_fifo_errors +
				    stats->netstats.rx_nohandler +
				    stats->rx_drop_state + stats->rx_oversize +
				    stats->rx_runt;
	stats->netstats.rx_dropped = stats->netstats.rx_errors;

	netdev->stats.tx_packets = stats->netstats.tx_packets;
	netdev->stats.tx_bytes = stats->netstats.tx_bytes;
	netdev->stats.tx_fifo_errors = stats->netstats.tx_fifo_errors;
	netdev->stats.tx_carrier_errors = stats->netstats.tx_carrier_errors;
	netdev->stats.tx_errors = stats->netstats.tx_errors;
	netdev->stats.tx_dropped = stats->netstats.tx_dropped;

	netdev->stats.rx_packets = stats->netstats.rx_packets;
	netdev->stats.rx_bytes = stats->netstats.rx_bytes;
	netdev->stats.rx_fifo_errors = stats->netstats.rx_fifo_errors;
	netdev->stats.multicast = stats->rx_grp.mcastbcast;
	netdev->stats.rx_length_errors = stats->rx_oversize + stats->rx_runt;
	netdev->stats.rx_errors = stats->netstats.rx_errors;
	netdev->stats.rx_dropped = stats->netstats.rx_dropped;
}