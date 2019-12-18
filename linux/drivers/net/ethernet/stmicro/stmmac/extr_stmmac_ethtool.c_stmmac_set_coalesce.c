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
typedef  int /*<<< orphan*/  u32 ;
struct stmmac_priv {unsigned int rx_riwt; scalar_t__ tx_coal_frames; scalar_t__ tx_coal_timer; int /*<<< orphan*/  rx_coal_frames; int /*<<< orphan*/  ioaddr; scalar_t__ use_riwt; TYPE_1__* plat; } ;
struct net_device {int dummy; } ;
struct ethtool_coalesce {scalar_t__ rx_coalesce_usecs; scalar_t__ tx_coalesce_usecs; scalar_t__ tx_max_coalesced_frames; int /*<<< orphan*/  rx_max_coalesced_frames; scalar_t__ rate_sample_interval; scalar_t__ tx_max_coalesced_frames_high; scalar_t__ stats_block_coalesce_usecs; scalar_t__ tx_max_coalesced_frames_irq; scalar_t__ rx_max_coalesced_frames_high; scalar_t__ rx_coalesce_usecs_high; scalar_t__ tx_coalesce_usecs_low; scalar_t__ pkt_rate_high; scalar_t__ tx_max_coalesced_frames_low; scalar_t__ tx_coalesce_usecs_high; scalar_t__ rx_max_coalesced_frames_low; scalar_t__ rx_coalesce_usecs_low; scalar_t__ pkt_rate_low; scalar_t__ use_adaptive_tx_coalesce; scalar_t__ use_adaptive_rx_coalesce; scalar_t__ tx_coalesce_usecs_irq; scalar_t__ rx_max_coalesced_frames_irq; scalar_t__ rx_coalesce_usecs_irq; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_queues_to_use; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 unsigned int MAX_DMA_RIWT ; 
 unsigned int MIN_DMA_RIWT ; 
 scalar_t__ STMMAC_MAX_COAL_TX_TICK ; 
 scalar_t__ STMMAC_TX_MAX_FRAMES ; 
 struct stmmac_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stmmac_rx_watchdog (struct stmmac_priv*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int stmmac_usec2riwt (scalar_t__,struct stmmac_priv*) ; 

__attribute__((used)) static int stmmac_set_coalesce(struct net_device *dev,
			       struct ethtool_coalesce *ec)
{
	struct stmmac_priv *priv = netdev_priv(dev);
	u32 rx_cnt = priv->plat->rx_queues_to_use;
	unsigned int rx_riwt;

	/* Check not supported parameters  */
	if ((ec->rx_coalesce_usecs_irq) ||
	    (ec->rx_max_coalesced_frames_irq) || (ec->tx_coalesce_usecs_irq) ||
	    (ec->use_adaptive_rx_coalesce) || (ec->use_adaptive_tx_coalesce) ||
	    (ec->pkt_rate_low) || (ec->rx_coalesce_usecs_low) ||
	    (ec->rx_max_coalesced_frames_low) || (ec->tx_coalesce_usecs_high) ||
	    (ec->tx_max_coalesced_frames_low) || (ec->pkt_rate_high) ||
	    (ec->tx_coalesce_usecs_low) || (ec->rx_coalesce_usecs_high) ||
	    (ec->rx_max_coalesced_frames_high) ||
	    (ec->tx_max_coalesced_frames_irq) ||
	    (ec->stats_block_coalesce_usecs) ||
	    (ec->tx_max_coalesced_frames_high) || (ec->rate_sample_interval))
		return -EOPNOTSUPP;

	if (priv->use_riwt && (ec->rx_coalesce_usecs > 0)) {
		rx_riwt = stmmac_usec2riwt(ec->rx_coalesce_usecs, priv);

		if ((rx_riwt > MAX_DMA_RIWT) || (rx_riwt < MIN_DMA_RIWT))
			return -EINVAL;

		priv->rx_riwt = rx_riwt;
		stmmac_rx_watchdog(priv, priv->ioaddr, priv->rx_riwt, rx_cnt);
	}

	if ((ec->tx_coalesce_usecs == 0) &&
	    (ec->tx_max_coalesced_frames == 0))
		return -EINVAL;

	if ((ec->tx_coalesce_usecs > STMMAC_MAX_COAL_TX_TICK) ||
	    (ec->tx_max_coalesced_frames > STMMAC_TX_MAX_FRAMES))
		return -EINVAL;

	/* Only copy relevant parameters, ignore all others. */
	priv->tx_coal_frames = ec->tx_max_coalesced_frames;
	priv->tx_coal_timer = ec->tx_coalesce_usecs;
	priv->rx_coal_frames = ec->rx_max_coalesced_frames;
	return 0;
}