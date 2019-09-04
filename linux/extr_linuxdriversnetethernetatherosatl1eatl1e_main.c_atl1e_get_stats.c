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
struct net_device_stats {scalar_t__ tx_errors; scalar_t__ tx_packets; scalar_t__ rx_errors; scalar_t__ rx_packets; scalar_t__ tx_window_errors; scalar_t__ tx_aborted_errors; scalar_t__ tx_fifo_errors; scalar_t__ rx_dropped; scalar_t__ rx_frame_errors; scalar_t__ rx_crc_errors; scalar_t__ rx_length_errors; scalar_t__ rx_fifo_errors; scalar_t__ collisions; int /*<<< orphan*/  multicast; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  rx_bytes; } ;
struct net_device {struct net_device_stats stats; } ;
struct atl1e_hw_stats {scalar_t__ tx_ok; scalar_t__ rx_ok; scalar_t__ tx_late_col; scalar_t__ tx_abort_col; scalar_t__ tx_underrun; scalar_t__ tx_trunc; scalar_t__ rx_rrd_ov; scalar_t__ rx_align_err; scalar_t__ rx_fcs_err; scalar_t__ rx_len_err; scalar_t__ rx_rxf_ov; scalar_t__ rx_sz_ov; scalar_t__ rx_frag; scalar_t__ tx_2_col; scalar_t__ tx_1_col; int /*<<< orphan*/  rx_mcast; int /*<<< orphan*/  tx_byte_cnt; int /*<<< orphan*/  rx_byte_cnt; } ;
struct atl1e_adapter {struct atl1e_hw_stats hw_stats; } ;

/* Variables and functions */
 struct atl1e_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static struct net_device_stats *atl1e_get_stats(struct net_device *netdev)
{
	struct atl1e_adapter *adapter = netdev_priv(netdev);
	struct atl1e_hw_stats  *hw_stats = &adapter->hw_stats;
	struct net_device_stats *net_stats = &netdev->stats;

	net_stats->rx_bytes   = hw_stats->rx_byte_cnt;
	net_stats->tx_bytes   = hw_stats->tx_byte_cnt;
	net_stats->multicast  = hw_stats->rx_mcast;
	net_stats->collisions = hw_stats->tx_1_col +
				hw_stats->tx_2_col +
				hw_stats->tx_late_col +
				hw_stats->tx_abort_col;

	net_stats->rx_errors  = hw_stats->rx_frag +
				hw_stats->rx_fcs_err +
				hw_stats->rx_len_err +
				hw_stats->rx_sz_ov +
				hw_stats->rx_rrd_ov +
				hw_stats->rx_align_err +
				hw_stats->rx_rxf_ov;

	net_stats->rx_fifo_errors   = hw_stats->rx_rxf_ov;
	net_stats->rx_length_errors = hw_stats->rx_len_err;
	net_stats->rx_crc_errors    = hw_stats->rx_fcs_err;
	net_stats->rx_frame_errors  = hw_stats->rx_align_err;
	net_stats->rx_dropped       = hw_stats->rx_rrd_ov;

	net_stats->tx_errors = hw_stats->tx_late_col +
			       hw_stats->tx_abort_col +
			       hw_stats->tx_underrun +
			       hw_stats->tx_trunc;

	net_stats->tx_fifo_errors    = hw_stats->tx_underrun;
	net_stats->tx_aborted_errors = hw_stats->tx_abort_col;
	net_stats->tx_window_errors  = hw_stats->tx_late_col;

	net_stats->rx_packets = hw_stats->rx_ok + net_stats->rx_errors;
	net_stats->tx_packets = hw_stats->tx_ok + net_stats->tx_errors;

	return net_stats;
}