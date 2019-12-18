#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_13__ ;
typedef  struct TYPE_16__   TYPE_12__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct rtnl_link_stats64 {scalar_t__ tx_dropped; scalar_t__ rx_dropped; scalar_t__ tx_errors; scalar_t__ rx_errors; scalar_t__ tx_bytes; scalar_t__ rx_bytes; scalar_t__ tx_packets; scalar_t__ rx_packets; } ;
struct TYPE_24__ {scalar_t__ fw_total_bcast_sent; scalar_t__ fw_total_mcast_sent; scalar_t__ fw_err_drop; } ;
struct TYPE_23__ {scalar_t__ fw_total_bcast; scalar_t__ fw_total_mcast; } ;
struct TYPE_25__ {TYPE_7__ fromhost; TYPE_6__ fromwire; } ;
struct octeon_device {int num_iqs; int num_oqs; TYPE_4__** droq; TYPE_12__** instr_queue; TYPE_8__ link_stats; } ;
struct net_device {TYPE_5__* netdev_ops; } ;
struct TYPE_15__ {TYPE_2__* rxpciq; TYPE_10__* txpciq; } ;
struct lio {TYPE_11__ linfo; scalar_t__ link_changes; struct octeon_device* oct_dev; } ;
struct ethtool_stats {int dummy; } ;
struct TYPE_26__ {int q_no; } ;
struct TYPE_22__ {int /*<<< orphan*/  (* ndo_get_stats64 ) (struct net_device*,struct rtnl_link_stats64*) ;} ;
struct TYPE_20__ {scalar_t__ rx_alloc_failure; scalar_t__ rx_vxlan; scalar_t__ dropped_nodispatch; scalar_t__ bytes_received; scalar_t__ pkts_received; scalar_t__ rx_dropped; scalar_t__ dropped_toomany; scalar_t__ dropped_nomem; scalar_t__ rx_bytes_received; scalar_t__ rx_pkts_received; } ;
struct TYPE_21__ {TYPE_3__ stats; } ;
struct TYPE_18__ {int q_no; } ;
struct TYPE_19__ {TYPE_1__ s; } ;
struct TYPE_17__ {scalar_t__ tx_restart; scalar_t__ tx_vxlan; scalar_t__ tx_gso; scalar_t__ bytes_sent; scalar_t__ instr_dropped; scalar_t__ instr_processed; scalar_t__ instr_posted; scalar_t__ sgentry_sent; scalar_t__ tx_iq_busy; scalar_t__ tx_dropped; scalar_t__ tx_tot_bytes; scalar_t__ tx_done; } ;
struct TYPE_16__ {TYPE_13__ stats; } ;
struct TYPE_14__ {TYPE_9__ s; } ;

/* Variables and functions */
 scalar_t__ CVM_CAST64 (scalar_t__) ; 
 struct lio* GET_LIO (struct net_device*) ; 
 int /*<<< orphan*/  LIO_IFSTATE_RESETTING ; 
 scalar_t__ ifstate_check (struct lio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,struct rtnl_link_stats64*) ; 

__attribute__((used)) static void lio_vf_get_ethtool_stats(struct net_device *netdev,
				     struct ethtool_stats *stats
				     __attribute__((unused)),
				     u64 *data)
{
	struct rtnl_link_stats64 lstats;
	struct lio *lio = GET_LIO(netdev);
	struct octeon_device *oct_dev = lio->oct_dev;
	int i = 0, j, vj;

	if (ifstate_check(lio, LIO_IFSTATE_RESETTING))
		return;

	netdev->netdev_ops->ndo_get_stats64(netdev, &lstats);
	/* sum of oct->droq[oq_no]->stats->rx_pkts_received */
	data[i++] = lstats.rx_packets;
	/* sum of oct->instr_queue[iq_no]->stats.tx_done */
	data[i++] = lstats.tx_packets;
	/* sum of oct->droq[oq_no]->stats->rx_bytes_received */
	data[i++] = lstats.rx_bytes;
	/* sum of oct->instr_queue[iq_no]->stats.tx_tot_bytes */
	data[i++] = lstats.tx_bytes;
	data[i++] = lstats.rx_errors;
	data[i++] = lstats.tx_errors;
	 /* sum of oct->droq[oq_no]->stats->rx_dropped +
	  * oct->droq[oq_no]->stats->dropped_nodispatch +
	  * oct->droq[oq_no]->stats->dropped_toomany +
	  * oct->droq[oq_no]->stats->dropped_nomem
	  */
	data[i++] = lstats.rx_dropped;
	/* sum of oct->instr_queue[iq_no]->stats.tx_dropped */
	data[i++] = lstats.tx_dropped +
		oct_dev->link_stats.fromhost.fw_err_drop;

	data[i++] = oct_dev->link_stats.fromwire.fw_total_mcast;
	data[i++] = oct_dev->link_stats.fromhost.fw_total_mcast_sent;
	data[i++] = oct_dev->link_stats.fromwire.fw_total_bcast;
	data[i++] = oct_dev->link_stats.fromhost.fw_total_bcast_sent;

	/* lio->link_changes */
	data[i++] = CVM_CAST64(lio->link_changes);

	for (vj = 0; vj < oct_dev->num_iqs; vj++) {
		j = lio->linfo.txpciq[vj].s.q_no;

		/* packets to network port */
		/* # of packets tx to network */
		data[i++] = CVM_CAST64(oct_dev->instr_queue[j]->stats.tx_done);
		 /* # of bytes tx to network */
		data[i++] = CVM_CAST64(
				oct_dev->instr_queue[j]->stats.tx_tot_bytes);
		/* # of packets dropped */
		data[i++] = CVM_CAST64(
				oct_dev->instr_queue[j]->stats.tx_dropped);
		/* # of tx fails due to queue full */
		data[i++] = CVM_CAST64(
				oct_dev->instr_queue[j]->stats.tx_iq_busy);
		/* XXX gather entries sent */
		data[i++] = CVM_CAST64(
				oct_dev->instr_queue[j]->stats.sgentry_sent);

		/* instruction to firmware: data and control */
		/* # of instructions to the queue */
		data[i++] = CVM_CAST64(
				oct_dev->instr_queue[j]->stats.instr_posted);
		/* # of instructions processed */
		data[i++] =
		    CVM_CAST64(oct_dev->instr_queue[j]->stats.instr_processed);
		/* # of instructions could not be processed */
		data[i++] =
		    CVM_CAST64(oct_dev->instr_queue[j]->stats.instr_dropped);
		/* bytes sent through the queue */
		data[i++] = CVM_CAST64(
				oct_dev->instr_queue[j]->stats.bytes_sent);
		/* tso request */
		data[i++] = CVM_CAST64(oct_dev->instr_queue[j]->stats.tx_gso);
		/* vxlan request */
		data[i++] = CVM_CAST64(oct_dev->instr_queue[j]->stats.tx_vxlan);
		/* txq restart */
		data[i++] = CVM_CAST64(
				oct_dev->instr_queue[j]->stats.tx_restart);
	}

	/* RX */
	for (vj = 0; vj < oct_dev->num_oqs; vj++) {
		j = lio->linfo.rxpciq[vj].s.q_no;

		/* packets send to TCP/IP network stack */
		/* # of packets to network stack */
		data[i++] = CVM_CAST64(
				oct_dev->droq[j]->stats.rx_pkts_received);
		/* # of bytes to network stack */
		data[i++] = CVM_CAST64(
				oct_dev->droq[j]->stats.rx_bytes_received);
		data[i++] = CVM_CAST64(oct_dev->droq[j]->stats.dropped_nomem +
				       oct_dev->droq[j]->stats.dropped_toomany +
				       oct_dev->droq[j]->stats.rx_dropped);
		data[i++] = CVM_CAST64(oct_dev->droq[j]->stats.dropped_nomem);
		data[i++] = CVM_CAST64(oct_dev->droq[j]->stats.dropped_toomany);
		data[i++] = CVM_CAST64(oct_dev->droq[j]->stats.rx_dropped);

		/* control and data path */
		data[i++] = CVM_CAST64(oct_dev->droq[j]->stats.pkts_received);
		data[i++] = CVM_CAST64(oct_dev->droq[j]->stats.bytes_received);
		data[i++] =
			CVM_CAST64(oct_dev->droq[j]->stats.dropped_nodispatch);

		data[i++] = CVM_CAST64(oct_dev->droq[j]->stats.rx_vxlan);
		data[i++] =
		    CVM_CAST64(oct_dev->droq[j]->stats.rx_alloc_failure);
	}
}