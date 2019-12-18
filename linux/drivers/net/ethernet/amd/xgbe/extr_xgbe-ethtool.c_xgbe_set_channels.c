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
struct TYPE_2__ {unsigned int rx_ch_cnt; unsigned int tx_ch_cnt; } ;
struct xgbe_prv_data {unsigned int rx_max_channel_count; unsigned int channel_irq_count; unsigned int tx_max_channel_count; unsigned int tx_max_q_count; int new_rx_ring_count; unsigned int rx_ring_count; int new_tx_ring_count; unsigned int tx_ring_count; TYPE_1__ hw_feat; } ;
struct net_device {int dummy; } ;
struct ethtool_channels {unsigned int combined_count; unsigned int rx_count; unsigned int tx_count; scalar_t__ other_count; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,...) ; 
 struct xgbe_prv_data* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  xgbe_full_restart_dev (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_print_set_channels_input (struct net_device*,struct ethtool_channels*) ; 

__attribute__((used)) static int xgbe_set_channels(struct net_device *netdev,
			     struct ethtool_channels *channels)
{
	struct xgbe_prv_data *pdata = netdev_priv(netdev);
	unsigned int rx, rx_curr, tx, tx_curr, combined;

	/* Calculate maximums allowed:
	 *   - Take into account the number of available IRQs
	 *   - Do not take into account the number of online CPUs so that
	 *     the user can over-subscribe if desired
	 *   - Tx is additionally limited by the number of hardware queues
	 */
	rx = min(pdata->hw_feat.rx_ch_cnt, pdata->rx_max_channel_count);
	rx = min(rx, pdata->channel_irq_count);
	tx = min(pdata->hw_feat.tx_ch_cnt, pdata->tx_max_channel_count);
	tx = min(tx, pdata->tx_max_q_count);
	tx = min(tx, pdata->channel_irq_count);

	combined = min(rx, tx);

	/* Should not be setting other count */
	if (channels->other_count) {
		netdev_err(netdev,
			   "other channel count must be zero\n");
		return -EINVAL;
	}

	/* Require at least one Combined (Rx and Tx) channel */
	if (!channels->combined_count) {
		netdev_err(netdev,
			   "at least one combined Rx/Tx channel is required\n");
		xgbe_print_set_channels_input(netdev, channels);
		return -EINVAL;
	}

	/* Check combined channels */
	if (channels->combined_count > combined) {
		netdev_err(netdev,
			   "combined channel count cannot exceed %u\n",
			   combined);
		xgbe_print_set_channels_input(netdev, channels);
		return -EINVAL;
	}

	/* Can have some Rx-only or Tx-only channels, but not both */
	if (channels->rx_count && channels->tx_count) {
		netdev_err(netdev,
			   "cannot specify both Rx-only and Tx-only channels\n");
		xgbe_print_set_channels_input(netdev, channels);
		return -EINVAL;
	}

	/* Check that we don't exceed the maximum number of channels */
	if ((channels->combined_count + channels->rx_count) > rx) {
		netdev_err(netdev,
			   "total Rx channels (%u) requested exceeds maximum available (%u)\n",
			   channels->combined_count + channels->rx_count, rx);
		xgbe_print_set_channels_input(netdev, channels);
		return -EINVAL;
	}

	if ((channels->combined_count + channels->tx_count) > tx) {
		netdev_err(netdev,
			   "total Tx channels (%u) requested exceeds maximum available (%u)\n",
			   channels->combined_count + channels->tx_count, tx);
		xgbe_print_set_channels_input(netdev, channels);
		return -EINVAL;
	}

	rx = channels->combined_count + channels->rx_count;
	tx = channels->combined_count + channels->tx_count;

	rx_curr = pdata->new_rx_ring_count ? : pdata->rx_ring_count;
	tx_curr = pdata->new_tx_ring_count ? : pdata->tx_ring_count;

	if ((rx == rx_curr) && (tx == tx_curr))
		goto out;

	pdata->new_rx_ring_count = rx;
	pdata->new_tx_ring_count = tx;

	xgbe_full_restart_dev(pdata);

out:
	return 0;
}