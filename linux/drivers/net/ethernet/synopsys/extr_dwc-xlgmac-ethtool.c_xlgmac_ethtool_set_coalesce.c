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
struct xlgmac_hw_ops {unsigned int (* usec_to_riwt ) (struct xlgmac_pdata*,unsigned int) ;int /*<<< orphan*/  (* config_tx_coalesce ) (struct xlgmac_pdata*) ;int /*<<< orphan*/  (* config_rx_coalesce ) (struct xlgmac_pdata*) ;} ;
struct xlgmac_pdata {unsigned int rx_desc_count; unsigned int tx_desc_count; unsigned int rx_riwt; unsigned int rx_usecs; unsigned int rx_frames; unsigned int tx_frames; struct xlgmac_hw_ops hw_ops; } ;
struct net_device {int dummy; } ;
struct ethtool_coalesce {unsigned int rx_coalesce_usecs; unsigned int rx_max_coalesced_frames; unsigned int tx_max_coalesced_frames; scalar_t__ rate_sample_interval; scalar_t__ tx_max_coalesced_frames_high; scalar_t__ rx_max_coalesced_frames_high; scalar_t__ rx_coalesce_usecs_high; scalar_t__ pkt_rate_high; scalar_t__ tx_max_coalesced_frames_low; scalar_t__ tx_coalesce_usecs_low; scalar_t__ rx_coalesce_usecs_low; scalar_t__ rx_max_coalesced_frames_low; scalar_t__ use_adaptive_tx_coalesce; scalar_t__ use_adaptive_rx_coalesce; scalar_t__ pkt_rate_low; scalar_t__ stats_block_coalesce_usecs; scalar_t__ tx_coalesce_usecs_irq; scalar_t__ tx_max_coalesced_frames_irq; scalar_t__ tx_coalesce_usecs_high; scalar_t__ tx_coalesce_usecs; scalar_t__ rx_max_coalesced_frames_irq; scalar_t__ rx_coalesce_usecs_irq; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 unsigned int XLGMAC_MAX_DMA_RIWT ; 
 unsigned int XLGMAC_MIN_DMA_RIWT ; 
 struct xlgmac_pdata* netdev_priv (struct net_device*) ; 
 unsigned int stub1 (struct xlgmac_pdata*,unsigned int) ; 
 int /*<<< orphan*/  stub2 (struct xlgmac_pdata*) ; 
 int /*<<< orphan*/  stub3 (struct xlgmac_pdata*) ; 

__attribute__((used)) static int xlgmac_ethtool_set_coalesce(struct net_device *netdev,
				       struct ethtool_coalesce *ec)
{
	struct xlgmac_pdata *pdata = netdev_priv(netdev);
	struct xlgmac_hw_ops *hw_ops = &pdata->hw_ops;
	unsigned int rx_frames, rx_riwt, rx_usecs;
	unsigned int tx_frames;

	/* Check for not supported parameters */
	if ((ec->rx_coalesce_usecs_irq) || (ec->rx_max_coalesced_frames_irq) ||
	    (ec->tx_coalesce_usecs) || (ec->tx_coalesce_usecs_high) ||
	    (ec->tx_max_coalesced_frames_irq) || (ec->tx_coalesce_usecs_irq) ||
	    (ec->stats_block_coalesce_usecs) ||  (ec->pkt_rate_low) ||
	    (ec->use_adaptive_rx_coalesce) || (ec->use_adaptive_tx_coalesce) ||
	    (ec->rx_max_coalesced_frames_low) || (ec->rx_coalesce_usecs_low) ||
	    (ec->tx_coalesce_usecs_low) || (ec->tx_max_coalesced_frames_low) ||
	    (ec->pkt_rate_high) || (ec->rx_coalesce_usecs_high) ||
	    (ec->rx_max_coalesced_frames_high) ||
	    (ec->tx_max_coalesced_frames_high) ||
	    (ec->rate_sample_interval))
		return -EOPNOTSUPP;

	rx_usecs = ec->rx_coalesce_usecs;
	rx_riwt = hw_ops->usec_to_riwt(pdata, rx_usecs);
	rx_frames = ec->rx_max_coalesced_frames;
	tx_frames = ec->tx_max_coalesced_frames;

	if ((rx_riwt > XLGMAC_MAX_DMA_RIWT) ||
	    (rx_riwt < XLGMAC_MIN_DMA_RIWT) ||
	    (rx_frames > pdata->rx_desc_count))
		return -EINVAL;

	if (tx_frames > pdata->tx_desc_count)
		return -EINVAL;

	pdata->rx_riwt = rx_riwt;
	pdata->rx_usecs = rx_usecs;
	pdata->rx_frames = rx_frames;
	hw_ops->config_rx_coalesce(pdata);

	pdata->tx_frames = tx_frames;
	hw_ops->config_tx_coalesce(pdata);

	return 0;
}