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
struct net_device {int dummy; } ;
struct hip04_priv {scalar_t__ tx_coalesce_usecs; scalar_t__ tx_coalesce_frames; } ;
struct ethtool_coalesce {scalar_t__ tx_coalesce_usecs; scalar_t__ tx_max_coalesced_frames; scalar_t__ rate_sample_interval; scalar_t__ tx_max_coalesced_frames_high; scalar_t__ stats_block_coalesce_usecs; scalar_t__ tx_max_coalesced_frames_irq; scalar_t__ rx_coalesce_usecs; scalar_t__ rx_max_coalesced_frames_high; scalar_t__ rx_coalesce_usecs_high; scalar_t__ tx_coalesce_usecs_low; scalar_t__ pkt_rate_high; scalar_t__ tx_max_coalesced_frames_low; scalar_t__ tx_coalesce_usecs_high; scalar_t__ rx_max_coalesced_frames_low; scalar_t__ rx_coalesce_usecs_low; scalar_t__ pkt_rate_low; scalar_t__ use_adaptive_tx_coalesce; scalar_t__ use_adaptive_rx_coalesce; scalar_t__ tx_coalesce_usecs_irq; scalar_t__ rx_max_coalesced_frames_irq; scalar_t__ rx_coalesce_usecs_irq; scalar_t__ rx_max_coalesced_frames; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 scalar_t__ HIP04_MAX_TX_COALESCE_FRAMES ; 
 scalar_t__ HIP04_MAX_TX_COALESCE_USECS ; 
 scalar_t__ HIP04_MIN_TX_COALESCE_FRAMES ; 
 scalar_t__ HIP04_MIN_TX_COALESCE_USECS ; 
 struct hip04_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int hip04_set_coalesce(struct net_device *netdev,
			      struct ethtool_coalesce *ec)
{
	struct hip04_priv *priv = netdev_priv(netdev);

	/* Check not supported parameters  */
	if ((ec->rx_max_coalesced_frames) || (ec->rx_coalesce_usecs_irq) ||
	    (ec->rx_max_coalesced_frames_irq) || (ec->tx_coalesce_usecs_irq) ||
	    (ec->use_adaptive_rx_coalesce) || (ec->use_adaptive_tx_coalesce) ||
	    (ec->pkt_rate_low) || (ec->rx_coalesce_usecs_low) ||
	    (ec->rx_max_coalesced_frames_low) || (ec->tx_coalesce_usecs_high) ||
	    (ec->tx_max_coalesced_frames_low) || (ec->pkt_rate_high) ||
	    (ec->tx_coalesce_usecs_low) || (ec->rx_coalesce_usecs_high) ||
	    (ec->rx_max_coalesced_frames_high) || (ec->rx_coalesce_usecs) ||
	    (ec->tx_max_coalesced_frames_irq) ||
	    (ec->stats_block_coalesce_usecs) ||
	    (ec->tx_max_coalesced_frames_high) || (ec->rate_sample_interval))
		return -EOPNOTSUPP;

	if ((ec->tx_coalesce_usecs > HIP04_MAX_TX_COALESCE_USECS ||
	     ec->tx_coalesce_usecs < HIP04_MIN_TX_COALESCE_USECS) ||
	    (ec->tx_max_coalesced_frames > HIP04_MAX_TX_COALESCE_FRAMES ||
	     ec->tx_max_coalesced_frames < HIP04_MIN_TX_COALESCE_FRAMES))
		return -EINVAL;

	priv->tx_coalesce_usecs = ec->tx_coalesce_usecs;
	priv->tx_coalesce_frames = ec->tx_max_coalesced_frames;

	return 0;
}