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
struct rtnl_link_stats64 {scalar_t__ rx_errors; scalar_t__ rx_packets; scalar_t__ tx_errors; scalar_t__ tx_packets; scalar_t__ tx_window_errors; scalar_t__ tx_fifo_errors; scalar_t__ tx_aborted_errors; scalar_t__ rx_dropped; scalar_t__ rx_frame_errors; scalar_t__ rx_crc_errors; scalar_t__ rx_length_errors; scalar_t__ rx_fifo_errors; scalar_t__ collisions; int /*<<< orphan*/  multicast; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  tx_bytes; } ;
struct net_device {int dummy; } ;
struct alx_hw_stats {scalar_t__ rx_ok; scalar_t__ tx_ok; scalar_t__ tx_late_col; scalar_t__ tx_underrun; scalar_t__ tx_abort_col; scalar_t__ tx_trunc; scalar_t__ rx_ov_rrd; scalar_t__ rx_align_err; scalar_t__ rx_fcs_err; scalar_t__ rx_len_err; scalar_t__ rx_ov_rxf; scalar_t__ rx_ov_sz; scalar_t__ rx_frag; scalar_t__ tx_multi_col; scalar_t__ tx_single_col; int /*<<< orphan*/  rx_mcast; int /*<<< orphan*/  rx_byte_cnt; int /*<<< orphan*/  tx_byte_cnt; } ;
struct TYPE_2__ {struct alx_hw_stats stats; } ;
struct alx_priv {int /*<<< orphan*/  stats_lock; TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  alx_update_hw_stats (TYPE_1__*) ; 
 struct alx_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void alx_get_stats64(struct net_device *dev,
			    struct rtnl_link_stats64 *net_stats)
{
	struct alx_priv *alx = netdev_priv(dev);
	struct alx_hw_stats *hw_stats = &alx->hw.stats;

	spin_lock(&alx->stats_lock);

	alx_update_hw_stats(&alx->hw);

	net_stats->tx_bytes   = hw_stats->tx_byte_cnt;
	net_stats->rx_bytes   = hw_stats->rx_byte_cnt;
	net_stats->multicast  = hw_stats->rx_mcast;
	net_stats->collisions = hw_stats->tx_single_col +
				hw_stats->tx_multi_col +
				hw_stats->tx_late_col +
				hw_stats->tx_abort_col;

	net_stats->rx_errors  = hw_stats->rx_frag +
				hw_stats->rx_fcs_err +
				hw_stats->rx_len_err +
				hw_stats->rx_ov_sz +
				hw_stats->rx_ov_rrd +
				hw_stats->rx_align_err +
				hw_stats->rx_ov_rxf;

	net_stats->rx_fifo_errors   = hw_stats->rx_ov_rxf;
	net_stats->rx_length_errors = hw_stats->rx_len_err;
	net_stats->rx_crc_errors    = hw_stats->rx_fcs_err;
	net_stats->rx_frame_errors  = hw_stats->rx_align_err;
	net_stats->rx_dropped       = hw_stats->rx_ov_rrd;

	net_stats->tx_errors = hw_stats->tx_late_col +
			       hw_stats->tx_abort_col +
			       hw_stats->tx_underrun +
			       hw_stats->tx_trunc;

	net_stats->tx_aborted_errors = hw_stats->tx_abort_col;
	net_stats->tx_fifo_errors    = hw_stats->tx_underrun;
	net_stats->tx_window_errors  = hw_stats->tx_late_col;

	net_stats->tx_packets = hw_stats->tx_ok + net_stats->tx_errors;
	net_stats->rx_packets = hw_stats->rx_ok + net_stats->rx_errors;

	spin_unlock(&alx->stats_lock);
}