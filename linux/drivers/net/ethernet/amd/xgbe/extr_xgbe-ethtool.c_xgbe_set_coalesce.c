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
struct xgbe_hw_if {unsigned int (* usec_to_riwt ) (struct xgbe_prv_data*,unsigned int) ;unsigned int (* riwt_to_usec ) (struct xgbe_prv_data*,unsigned int) ;int /*<<< orphan*/  (* config_tx_coalesce ) (struct xgbe_prv_data*) ;int /*<<< orphan*/  (* config_rx_coalesce ) (struct xgbe_prv_data*) ;} ;
struct xgbe_prv_data {unsigned int rx_desc_count; unsigned int tx_desc_count; unsigned int rx_riwt; unsigned int rx_usecs; unsigned int rx_frames; unsigned int tx_frames; struct xgbe_hw_if hw_if; } ;
struct net_device {int dummy; } ;
struct ethtool_coalesce {unsigned int rx_coalesce_usecs; unsigned int rx_max_coalesced_frames; unsigned int tx_max_coalesced_frames; scalar_t__ rate_sample_interval; scalar_t__ tx_max_coalesced_frames_high; scalar_t__ tx_coalesce_usecs_high; scalar_t__ rx_max_coalesced_frames_high; scalar_t__ rx_coalesce_usecs_high; scalar_t__ pkt_rate_high; scalar_t__ tx_max_coalesced_frames_low; scalar_t__ tx_coalesce_usecs_low; scalar_t__ rx_max_coalesced_frames_low; scalar_t__ rx_coalesce_usecs_low; scalar_t__ pkt_rate_low; scalar_t__ use_adaptive_tx_coalesce; scalar_t__ use_adaptive_rx_coalesce; scalar_t__ stats_block_coalesce_usecs; scalar_t__ tx_max_coalesced_frames_irq; scalar_t__ tx_coalesce_usecs_irq; scalar_t__ tx_coalesce_usecs; scalar_t__ rx_max_coalesced_frames_irq; scalar_t__ rx_coalesce_usecs_irq; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 unsigned int XGMAC_MAX_DMA_RIWT ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,...) ; 
 struct xgbe_prv_data* netdev_priv (struct net_device*) ; 
 unsigned int stub1 (struct xgbe_prv_data*,unsigned int) ; 
 unsigned int stub2 (struct xgbe_prv_data*,unsigned int) ; 
 int /*<<< orphan*/  stub3 (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  stub4 (struct xgbe_prv_data*) ; 

__attribute__((used)) static int xgbe_set_coalesce(struct net_device *netdev,
			     struct ethtool_coalesce *ec)
{
	struct xgbe_prv_data *pdata = netdev_priv(netdev);
	struct xgbe_hw_if *hw_if = &pdata->hw_if;
	unsigned int rx_frames, rx_riwt, rx_usecs;
	unsigned int tx_frames;

	/* Check for not supported parameters  */
	if ((ec->rx_coalesce_usecs_irq) ||
	    (ec->rx_max_coalesced_frames_irq) ||
	    (ec->tx_coalesce_usecs) ||
	    (ec->tx_coalesce_usecs_irq) ||
	    (ec->tx_max_coalesced_frames_irq) ||
	    (ec->stats_block_coalesce_usecs) ||
	    (ec->use_adaptive_rx_coalesce) ||
	    (ec->use_adaptive_tx_coalesce) ||
	    (ec->pkt_rate_low) ||
	    (ec->rx_coalesce_usecs_low) ||
	    (ec->rx_max_coalesced_frames_low) ||
	    (ec->tx_coalesce_usecs_low) ||
	    (ec->tx_max_coalesced_frames_low) ||
	    (ec->pkt_rate_high) ||
	    (ec->rx_coalesce_usecs_high) ||
	    (ec->rx_max_coalesced_frames_high) ||
	    (ec->tx_coalesce_usecs_high) ||
	    (ec->tx_max_coalesced_frames_high) ||
	    (ec->rate_sample_interval)) {
		netdev_err(netdev, "unsupported coalescing parameter\n");
		return -EOPNOTSUPP;
	}

	rx_riwt = hw_if->usec_to_riwt(pdata, ec->rx_coalesce_usecs);
	rx_usecs = ec->rx_coalesce_usecs;
	rx_frames = ec->rx_max_coalesced_frames;

	/* Use smallest possible value if conversion resulted in zero */
	if (rx_usecs && !rx_riwt)
		rx_riwt = 1;

	/* Check the bounds of values for Rx */
	if (rx_riwt > XGMAC_MAX_DMA_RIWT) {
		netdev_err(netdev, "rx-usec is limited to %d usecs\n",
			   hw_if->riwt_to_usec(pdata, XGMAC_MAX_DMA_RIWT));
		return -EINVAL;
	}
	if (rx_frames > pdata->rx_desc_count) {
		netdev_err(netdev, "rx-frames is limited to %d frames\n",
			   pdata->rx_desc_count);
		return -EINVAL;
	}

	tx_frames = ec->tx_max_coalesced_frames;

	/* Check the bounds of values for Tx */
	if (tx_frames > pdata->tx_desc_count) {
		netdev_err(netdev, "tx-frames is limited to %d frames\n",
			   pdata->tx_desc_count);
		return -EINVAL;
	}

	pdata->rx_riwt = rx_riwt;
	pdata->rx_usecs = rx_usecs;
	pdata->rx_frames = rx_frames;
	hw_if->config_rx_coalesce(pdata);

	pdata->tx_frames = tx_frames;
	hw_if->config_tx_coalesce(pdata);

	return 0;
}