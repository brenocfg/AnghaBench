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
struct xgbe_prv_data {unsigned int rx_max_channel_count; unsigned int channel_irq_count; unsigned int tx_max_channel_count; unsigned int tx_max_q_count; unsigned int rx_ring_count; unsigned int tx_ring_count; scalar_t__ new_tx_ring_count; scalar_t__ new_rx_ring_count; TYPE_1__ hw_feat; } ;
struct net_device {int dummy; } ;
struct ethtool_channels {unsigned int max_combined; unsigned int max_rx; unsigned int max_tx; unsigned int combined_count; unsigned int rx_count; unsigned int tx_count; } ;

/* Variables and functions */
 unsigned int min (unsigned int,unsigned int) ; 
 struct xgbe_prv_data* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void xgbe_get_channels(struct net_device *netdev,
			      struct ethtool_channels *channels)
{
	struct xgbe_prv_data *pdata = netdev_priv(netdev);
	unsigned int rx, tx, combined;

	/* Calculate maximums allowed:
	 *   - Take into account the number of available IRQs
	 *   - Do not take into account the number of online CPUs so that
	 *     the user can over-subscribe if desired
	 *   - Tx is additionally limited by the number of hardware queues
	 */
	rx = min(pdata->hw_feat.rx_ch_cnt, pdata->rx_max_channel_count);
	rx = min(rx, pdata->channel_irq_count);
	tx = min(pdata->hw_feat.tx_ch_cnt, pdata->tx_max_channel_count);
	tx = min(tx, pdata->channel_irq_count);
	tx = min(tx, pdata->tx_max_q_count);

	combined = min(rx, tx);

	channels->max_combined = combined;
	channels->max_rx = rx ? rx - 1 : 0;
	channels->max_tx = tx ? tx - 1 : 0;

	/* Get current settings based on device state */
	rx = pdata->new_rx_ring_count ? : pdata->rx_ring_count;
	tx = pdata->new_tx_ring_count ? : pdata->tx_ring_count;

	combined = min(rx, tx);
	rx -= combined;
	tx -= combined;

	channels->combined_count = combined;
	channels->rx_count = rx;
	channels->tx_count = tx;
}