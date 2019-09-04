#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct stats_msg_block {scalar_t__ tx_pause; scalar_t__ tx_trunc; scalar_t__ tx_underrun; scalar_t__ tx_late_col; scalar_t__ tx_2_col; scalar_t__ tx_1_col; scalar_t__ tx_defer; scalar_t__ tx_abort_col; scalar_t__ rx_sz_ov; scalar_t__ rx_rrd_ov; scalar_t__ rx_pause; scalar_t__ rx_align_err; scalar_t__ rx_fcs_err; scalar_t__ rx_len_err; scalar_t__ rx_rxf_ov; scalar_t__ rx_mcast; scalar_t__ tx_byte_cnt; scalar_t__ rx_byte_cnt; scalar_t__ tx_ok; scalar_t__ rx_ok; scalar_t__ rx_frag; } ;
struct TYPE_6__ {int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  tx_carrier_errors; int /*<<< orphan*/  tx_window_errors; int /*<<< orphan*/  tx_aborted_errors; int /*<<< orphan*/  tx_fifo_errors; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_fifo_errors; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  collisions; int /*<<< orphan*/  multicast; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  rx_bytes; } ;
struct net_device {TYPE_3__ stats; } ;
struct TYPE_5__ {int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  tx_carrier_errors; int /*<<< orphan*/  tx_window_errors; int /*<<< orphan*/  tx_aborted_errors; int /*<<< orphan*/  tx_fifo_errors; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  rx_rrd_ov; int /*<<< orphan*/  rx_fifo_errors; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  collisions; int /*<<< orphan*/  multicast; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  tx_pause; int /*<<< orphan*/  tx_trunc; int /*<<< orphan*/  tx_underun; int /*<<< orphan*/  latecol; int /*<<< orphan*/  mcc; int /*<<< orphan*/  scc; int /*<<< orphan*/  deffer; int /*<<< orphan*/  excecol; int /*<<< orphan*/  rx_trunc; int /*<<< orphan*/  rx_pause; } ;
struct TYPE_4__ {struct stats_msg_block* smb; } ;
struct atl1_adapter {TYPE_2__ soft_stats; TYPE_1__ smb; struct net_device* netdev; } ;

/* Variables and functions */

__attribute__((used)) static void atl1_inc_smb(struct atl1_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	struct stats_msg_block *smb = adapter->smb.smb;

	u64 new_rx_errors = smb->rx_frag +
			    smb->rx_fcs_err +
			    smb->rx_len_err +
			    smb->rx_sz_ov +
			    smb->rx_rxf_ov +
			    smb->rx_rrd_ov +
			    smb->rx_align_err;
	u64 new_tx_errors = smb->tx_late_col +
			    smb->tx_abort_col +
			    smb->tx_underrun +
			    smb->tx_trunc;

	/* Fill out the OS statistics structure */
	adapter->soft_stats.rx_packets += smb->rx_ok + new_rx_errors;
	adapter->soft_stats.tx_packets += smb->tx_ok + new_tx_errors;
	adapter->soft_stats.rx_bytes += smb->rx_byte_cnt;
	adapter->soft_stats.tx_bytes += smb->tx_byte_cnt;
	adapter->soft_stats.multicast += smb->rx_mcast;
	adapter->soft_stats.collisions += smb->tx_1_col +
					  smb->tx_2_col +
					  smb->tx_late_col +
					  smb->tx_abort_col;

	/* Rx Errors */
	adapter->soft_stats.rx_errors += new_rx_errors;
	adapter->soft_stats.rx_fifo_errors += smb->rx_rxf_ov;
	adapter->soft_stats.rx_length_errors += smb->rx_len_err;
	adapter->soft_stats.rx_crc_errors += smb->rx_fcs_err;
	adapter->soft_stats.rx_frame_errors += smb->rx_align_err;

	adapter->soft_stats.rx_pause += smb->rx_pause;
	adapter->soft_stats.rx_rrd_ov += smb->rx_rrd_ov;
	adapter->soft_stats.rx_trunc += smb->rx_sz_ov;

	/* Tx Errors */
	adapter->soft_stats.tx_errors += new_tx_errors;
	adapter->soft_stats.tx_fifo_errors += smb->tx_underrun;
	adapter->soft_stats.tx_aborted_errors += smb->tx_abort_col;
	adapter->soft_stats.tx_window_errors += smb->tx_late_col;

	adapter->soft_stats.excecol += smb->tx_abort_col;
	adapter->soft_stats.deffer += smb->tx_defer;
	adapter->soft_stats.scc += smb->tx_1_col;
	adapter->soft_stats.mcc += smb->tx_2_col;
	adapter->soft_stats.latecol += smb->tx_late_col;
	adapter->soft_stats.tx_underun += smb->tx_underrun;
	adapter->soft_stats.tx_trunc += smb->tx_trunc;
	adapter->soft_stats.tx_pause += smb->tx_pause;

	netdev->stats.rx_bytes = adapter->soft_stats.rx_bytes;
	netdev->stats.tx_bytes = adapter->soft_stats.tx_bytes;
	netdev->stats.multicast = adapter->soft_stats.multicast;
	netdev->stats.collisions = adapter->soft_stats.collisions;
	netdev->stats.rx_errors = adapter->soft_stats.rx_errors;
	netdev->stats.rx_length_errors =
		adapter->soft_stats.rx_length_errors;
	netdev->stats.rx_crc_errors = adapter->soft_stats.rx_crc_errors;
	netdev->stats.rx_frame_errors =
		adapter->soft_stats.rx_frame_errors;
	netdev->stats.rx_fifo_errors = adapter->soft_stats.rx_fifo_errors;
	netdev->stats.rx_dropped = adapter->soft_stats.rx_rrd_ov;
	netdev->stats.tx_errors = adapter->soft_stats.tx_errors;
	netdev->stats.tx_fifo_errors = adapter->soft_stats.tx_fifo_errors;
	netdev->stats.tx_aborted_errors =
		adapter->soft_stats.tx_aborted_errors;
	netdev->stats.tx_window_errors =
		adapter->soft_stats.tx_window_errors;
	netdev->stats.tx_carrier_errors =
		adapter->soft_stats.tx_carrier_errors;

	netdev->stats.rx_packets = adapter->soft_stats.rx_packets;
	netdev->stats.tx_packets = adapter->soft_stats.tx_packets;
}