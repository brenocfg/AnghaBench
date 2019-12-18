#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct rtnl_link_stats64 {scalar_t__ tx_dropped; scalar_t__ rx_dropped; scalar_t__ tx_errors; scalar_t__ rx_errors; scalar_t__ tx_bytes; scalar_t__ rx_bytes; scalar_t__ tx_packets; scalar_t__ rx_packets; } ;
struct TYPE_16__ {int iq; int oq; } ;
struct TYPE_12__ {scalar_t__ fcs_err; scalar_t__ dmac_drop; scalar_t__ fifo_err; scalar_t__ ctl_rcvd; scalar_t__ runts; scalar_t__ total_mcst; scalar_t__ total_bcst; scalar_t__ bytes_rcvd; scalar_t__ total_rcvd; scalar_t__ fwd_rate; scalar_t__ fw_lro_aborts_timer; scalar_t__ fw_lro_aborts_tsval; scalar_t__ fw_lro_aborts_seq; scalar_t__ fw_lro_aborts_port; scalar_t__ fw_lro_aborts; scalar_t__ fw_total_lro; scalar_t__ fw_lro_octs; scalar_t__ fw_lro_pkts; scalar_t__ fw_rx_vxlan_err; scalar_t__ fw_rx_vxlan; scalar_t__ fw_err_drop; scalar_t__ fw_err_link; scalar_t__ fw_err_pko; scalar_t__ frame_err; scalar_t__ l2_err; scalar_t__ jabber_err; scalar_t__ fw_total_bcast; scalar_t__ fw_total_mcast; scalar_t__ fw_total_fwd; scalar_t__ fw_total_rcvd; scalar_t__ red_drops; } ;
struct TYPE_11__ {scalar_t__ runts; scalar_t__ fifo_err; scalar_t__ max_deferral_fail; scalar_t__ max_collision_fail; scalar_t__ multi_collision_sent; scalar_t__ one_collision_sent; scalar_t__ total_collisions; scalar_t__ ctl_sent; scalar_t__ bcast_pkts_sent; scalar_t__ mcast_pkts_sent; scalar_t__ total_bytes_sent; scalar_t__ total_pkts_sent; scalar_t__ fw_total_bcast_sent; scalar_t__ fw_total_mcast_sent; scalar_t__ fw_tx_vxlan; scalar_t__ fw_err_tso; scalar_t__ fw_tso_fwd; scalar_t__ fw_tso; scalar_t__ fw_err_drop; scalar_t__ fw_err_link; scalar_t__ fw_err_pki; scalar_t__ fw_err_pko; scalar_t__ fw_total_fwd; scalar_t__ fw_total_sent; } ;
struct TYPE_13__ {TYPE_3__ fromwire; TYPE_2__ fromhost; } ;
struct octeon_device {TYPE_9__** droq; TYPE_7__ io_qmask; TYPE_6__** instr_queue; TYPE_4__ link_stats; } ;
struct net_device {TYPE_1__* netdev_ops; } ;
struct lio {scalar_t__ link_changes; struct octeon_device* oct_dev; } ;
struct ethtool_stats {int dummy; } ;
struct TYPE_17__ {scalar_t__ rx_alloc_failure; scalar_t__ rx_vxlan; scalar_t__ dropped_nodispatch; scalar_t__ bytes_received; scalar_t__ pkts_received; scalar_t__ rx_dropped; scalar_t__ dropped_toomany; scalar_t__ dropped_nomem; scalar_t__ rx_bytes_received; scalar_t__ rx_pkts_received; } ;
struct TYPE_18__ {TYPE_8__ stats; } ;
struct TYPE_14__ {scalar_t__ tx_restart; scalar_t__ tx_vxlan; scalar_t__ tx_gso; scalar_t__ bytes_sent; scalar_t__ instr_dropped; scalar_t__ instr_processed; scalar_t__ instr_posted; scalar_t__ sgentry_sent; scalar_t__ tx_iq_busy; scalar_t__ tx_dropped; scalar_t__ tx_tot_bytes; scalar_t__ tx_done; } ;
struct TYPE_15__ {TYPE_5__ stats; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* ndo_get_stats64 ) (struct net_device*,struct rtnl_link_stats64*) ;} ;

/* Variables and functions */
 int BIT_ULL (int) ; 
 scalar_t__ CVM_CAST64 (scalar_t__) ; 
 struct lio* GET_LIO (struct net_device*) ; 
 int /*<<< orphan*/  LIO_IFSTATE_RESETTING ; 
 int MAX_OCTEON_INSTR_QUEUES (struct octeon_device*) ; 
 int MAX_OCTEON_OUTPUT_QUEUES (struct octeon_device*) ; 
 scalar_t__ ifstate_check (struct lio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,struct rtnl_link_stats64*) ; 

__attribute__((used)) static void
lio_get_ethtool_stats(struct net_device *netdev,
		      struct ethtool_stats *stats  __attribute__((unused)),
		      u64 *data)
{
	struct lio *lio = GET_LIO(netdev);
	struct octeon_device *oct_dev = lio->oct_dev;
	struct rtnl_link_stats64 lstats;
	int i = 0, j;

	if (ifstate_check(lio, LIO_IFSTATE_RESETTING))
		return;

	netdev->netdev_ops->ndo_get_stats64(netdev, &lstats);
	/*sum of oct->droq[oq_no]->stats->rx_pkts_received */
	data[i++] = lstats.rx_packets;
	/*sum of oct->instr_queue[iq_no]->stats.tx_done */
	data[i++] = lstats.tx_packets;
	/*sum of oct->droq[oq_no]->stats->rx_bytes_received */
	data[i++] = lstats.rx_bytes;
	/*sum of oct->instr_queue[iq_no]->stats.tx_tot_bytes */
	data[i++] = lstats.tx_bytes;
	data[i++] = lstats.rx_errors +
			oct_dev->link_stats.fromwire.fcs_err +
			oct_dev->link_stats.fromwire.jabber_err +
			oct_dev->link_stats.fromwire.l2_err +
			oct_dev->link_stats.fromwire.frame_err;
	data[i++] = lstats.tx_errors;
	/*sum of oct->droq[oq_no]->stats->rx_dropped +
	 *oct->droq[oq_no]->stats->dropped_nodispatch +
	 *oct->droq[oq_no]->stats->dropped_toomany +
	 *oct->droq[oq_no]->stats->dropped_nomem
	 */
	data[i++] = lstats.rx_dropped +
			oct_dev->link_stats.fromwire.fifo_err +
			oct_dev->link_stats.fromwire.dmac_drop +
			oct_dev->link_stats.fromwire.red_drops +
			oct_dev->link_stats.fromwire.fw_err_pko +
			oct_dev->link_stats.fromwire.fw_err_link +
			oct_dev->link_stats.fromwire.fw_err_drop;
	/*sum of oct->instr_queue[iq_no]->stats.tx_dropped */
	data[i++] = lstats.tx_dropped +
			oct_dev->link_stats.fromhost.max_collision_fail +
			oct_dev->link_stats.fromhost.max_deferral_fail +
			oct_dev->link_stats.fromhost.total_collisions +
			oct_dev->link_stats.fromhost.fw_err_pko +
			oct_dev->link_stats.fromhost.fw_err_link +
			oct_dev->link_stats.fromhost.fw_err_drop +
			oct_dev->link_stats.fromhost.fw_err_pki;

	/* firmware tx stats */
	/*per_core_stats[cvmx_get_core_num()].link_stats[mdata->from_ifidx].
	 *fromhost.fw_total_sent
	 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromhost.fw_total_sent);
	/*per_core_stats[i].link_stats[port].fromwire.fw_total_fwd */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromhost.fw_total_fwd);
	/*per_core_stats[j].link_stats[i].fromhost.fw_err_pko */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromhost.fw_err_pko);
	/*per_core_stats[j].link_stats[i].fromhost.fw_err_pki */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromhost.fw_err_pki);
	/*per_core_stats[j].link_stats[i].fromhost.fw_err_link */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromhost.fw_err_link);
	/*per_core_stats[cvmx_get_core_num()].link_stats[idx].fromhost.
	 *fw_err_drop
	 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromhost.fw_err_drop);

	/*per_core_stats[cvmx_get_core_num()].link_stats[idx].fromhost.fw_tso */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromhost.fw_tso);
	/*per_core_stats[cvmx_get_core_num()].link_stats[idx].fromhost.
	 *fw_tso_fwd
	 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromhost.fw_tso_fwd);
	/*per_core_stats[cvmx_get_core_num()].link_stats[idx].fromhost.
	 *fw_err_tso
	 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromhost.fw_err_tso);
	/*per_core_stats[cvmx_get_core_num()].link_stats[idx].fromhost.
	 *fw_tx_vxlan
	 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromhost.fw_tx_vxlan);

	/* Multicast packets sent by this port */
	data[i++] = oct_dev->link_stats.fromhost.fw_total_mcast_sent;
	data[i++] = oct_dev->link_stats.fromhost.fw_total_bcast_sent;

	/* mac tx statistics */
	/*CVMX_BGXX_CMRX_TX_STAT5 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromhost.total_pkts_sent);
	/*CVMX_BGXX_CMRX_TX_STAT4 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromhost.total_bytes_sent);
	/*CVMX_BGXX_CMRX_TX_STAT15 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromhost.mcast_pkts_sent);
	/*CVMX_BGXX_CMRX_TX_STAT14 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromhost.bcast_pkts_sent);
	/*CVMX_BGXX_CMRX_TX_STAT17 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromhost.ctl_sent);
	/*CVMX_BGXX_CMRX_TX_STAT0 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromhost.total_collisions);
	/*CVMX_BGXX_CMRX_TX_STAT3 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromhost.one_collision_sent);
	/*CVMX_BGXX_CMRX_TX_STAT2 */
	data[i++] =
		CVM_CAST64(oct_dev->link_stats.fromhost.multi_collision_sent);
	/*CVMX_BGXX_CMRX_TX_STAT0 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromhost.max_collision_fail);
	/*CVMX_BGXX_CMRX_TX_STAT1 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromhost.max_deferral_fail);
	/*CVMX_BGXX_CMRX_TX_STAT16 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromhost.fifo_err);
	/*CVMX_BGXX_CMRX_TX_STAT6 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromhost.runts);

	/* RX firmware stats */
	/*per_core_stats[cvmx_get_core_num()].link_stats[ifidx].fromwire.
	 *fw_total_rcvd
	 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromwire.fw_total_rcvd);
	/*per_core_stats[cvmx_get_core_num()].link_stats[ifidx].fromwire.
	 *fw_total_fwd
	 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromwire.fw_total_fwd);
	/* Multicast packets received on this port */
	data[i++] = oct_dev->link_stats.fromwire.fw_total_mcast;
	data[i++] = oct_dev->link_stats.fromwire.fw_total_bcast;
	/*per_core_stats[core_id].link_stats[ifidx].fromwire.jabber_err */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromwire.jabber_err);
	/*per_core_stats[core_id].link_stats[ifidx].fromwire.l2_err */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromwire.l2_err);
	/*per_core_stats[core_id].link_stats[ifidx].fromwire.frame_err */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromwire.frame_err);
	/*per_core_stats[cvmx_get_core_num()].link_stats[ifidx].fromwire.
	 *fw_err_pko
	 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromwire.fw_err_pko);
	/*per_core_stats[j].link_stats[i].fromwire.fw_err_link */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromwire.fw_err_link);
	/*per_core_stats[cvmx_get_core_num()].link_stats[lro_ctx->ifidx].
	 *fromwire.fw_err_drop
	 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromwire.fw_err_drop);

	/*per_core_stats[cvmx_get_core_num()].link_stats[lro_ctx->ifidx].
	 *fromwire.fw_rx_vxlan
	 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromwire.fw_rx_vxlan);
	/*per_core_stats[cvmx_get_core_num()].link_stats[lro_ctx->ifidx].
	 *fromwire.fw_rx_vxlan_err
	 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromwire.fw_rx_vxlan_err);

	/* LRO */
	/*per_core_stats[cvmx_get_core_num()].link_stats[ifidx].fromwire.
	 *fw_lro_pkts
	 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromwire.fw_lro_pkts);
	/*per_core_stats[cvmx_get_core_num()].link_stats[ifidx].fromwire.
	 *fw_lro_octs
	 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromwire.fw_lro_octs);
	/*per_core_stats[j].link_stats[i].fromwire.fw_total_lro */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromwire.fw_total_lro);
	/*per_core_stats[j].link_stats[i].fromwire.fw_lro_aborts */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromwire.fw_lro_aborts);
	/*per_core_stats[cvmx_get_core_num()].link_stats[ifidx].fromwire.
	 *fw_lro_aborts_port
	 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromwire.fw_lro_aborts_port);
	/*per_core_stats[cvmx_get_core_num()].link_stats[ifidx].fromwire.
	 *fw_lro_aborts_seq
	 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromwire.fw_lro_aborts_seq);
	/*per_core_stats[cvmx_get_core_num()].link_stats[ifidx].fromwire.
	 *fw_lro_aborts_tsval
	 */
	data[i++] =
		CVM_CAST64(oct_dev->link_stats.fromwire.fw_lro_aborts_tsval);
	/*per_core_stats[cvmx_get_core_num()].link_stats[ifidx].fromwire.
	 *fw_lro_aborts_timer
	 */
	/* intrmod: packet forward rate */
	data[i++] =
		CVM_CAST64(oct_dev->link_stats.fromwire.fw_lro_aborts_timer);
	/*per_core_stats[j].link_stats[i].fromwire.fw_lro_aborts */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromwire.fwd_rate);

	/* mac: link-level stats */
	/*CVMX_BGXX_CMRX_RX_STAT0 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromwire.total_rcvd);
	/*CVMX_BGXX_CMRX_RX_STAT1 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromwire.bytes_rcvd);
	/*CVMX_PKI_STATX_STAT5 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromwire.total_bcst);
	/*CVMX_PKI_STATX_STAT5 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromwire.total_mcst);
	/*wqe->word2.err_code or wqe->word2.err_level */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromwire.runts);
	/*CVMX_BGXX_CMRX_RX_STAT2 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromwire.ctl_rcvd);
	/*CVMX_BGXX_CMRX_RX_STAT6 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromwire.fifo_err);
	/*CVMX_BGXX_CMRX_RX_STAT4 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromwire.dmac_drop);
	/*wqe->word2.err_code or wqe->word2.err_level */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromwire.fcs_err);
	/*lio->link_changes*/
	data[i++] = CVM_CAST64(lio->link_changes);

	for (j = 0; j < MAX_OCTEON_INSTR_QUEUES(oct_dev); j++) {
		if (!(oct_dev->io_qmask.iq & BIT_ULL(j)))
			continue;
		/*packets to network port*/
		/*# of packets tx to network */
		data[i++] = CVM_CAST64(oct_dev->instr_queue[j]->stats.tx_done);
		/*# of bytes tx to network */
		data[i++] =
			CVM_CAST64(oct_dev->instr_queue[j]->stats.tx_tot_bytes);
		/*# of packets dropped */
		data[i++] =
			CVM_CAST64(oct_dev->instr_queue[j]->stats.tx_dropped);
		/*# of tx fails due to queue full */
		data[i++] =
			CVM_CAST64(oct_dev->instr_queue[j]->stats.tx_iq_busy);
		/*XXX gather entries sent */
		data[i++] =
			CVM_CAST64(oct_dev->instr_queue[j]->stats.sgentry_sent);

		/*instruction to firmware: data and control */
		/*# of instructions to the queue */
		data[i++] =
			CVM_CAST64(oct_dev->instr_queue[j]->stats.instr_posted);
		/*# of instructions processed */
		data[i++] = CVM_CAST64(
				oct_dev->instr_queue[j]->stats.instr_processed);
		/*# of instructions could not be processed */
		data[i++] = CVM_CAST64(
				oct_dev->instr_queue[j]->stats.instr_dropped);
		/*bytes sent through the queue */
		data[i++] =
			CVM_CAST64(oct_dev->instr_queue[j]->stats.bytes_sent);

		/*tso request*/
		data[i++] = CVM_CAST64(oct_dev->instr_queue[j]->stats.tx_gso);
		/*vxlan request*/
		data[i++] = CVM_CAST64(oct_dev->instr_queue[j]->stats.tx_vxlan);
		/*txq restart*/
		data[i++] =
			CVM_CAST64(oct_dev->instr_queue[j]->stats.tx_restart);
	}

	/* RX */
	for (j = 0; j < MAX_OCTEON_OUTPUT_QUEUES(oct_dev); j++) {
		if (!(oct_dev->io_qmask.oq & BIT_ULL(j)))
			continue;

		/*packets send to TCP/IP network stack */
		/*# of packets to network stack */
		data[i++] =
			CVM_CAST64(oct_dev->droq[j]->stats.rx_pkts_received);
		/*# of bytes to network stack */
		data[i++] =
			CVM_CAST64(oct_dev->droq[j]->stats.rx_bytes_received);
		/*# of packets dropped */
		data[i++] = CVM_CAST64(oct_dev->droq[j]->stats.dropped_nomem +
				       oct_dev->droq[j]->stats.dropped_toomany +
				       oct_dev->droq[j]->stats.rx_dropped);
		data[i++] =
			CVM_CAST64(oct_dev->droq[j]->stats.dropped_nomem);
		data[i++] =
			CVM_CAST64(oct_dev->droq[j]->stats.dropped_toomany);
		data[i++] =
			CVM_CAST64(oct_dev->droq[j]->stats.rx_dropped);

		/*control and data path*/
		data[i++] =
			CVM_CAST64(oct_dev->droq[j]->stats.pkts_received);
		data[i++] =
			CVM_CAST64(oct_dev->droq[j]->stats.bytes_received);
		data[i++] =
			CVM_CAST64(oct_dev->droq[j]->stats.dropped_nodispatch);

		data[i++] =
			CVM_CAST64(oct_dev->droq[j]->stats.rx_vxlan);
		data[i++] =
			CVM_CAST64(oct_dev->droq[j]->stats.rx_alloc_failure);
	}
}