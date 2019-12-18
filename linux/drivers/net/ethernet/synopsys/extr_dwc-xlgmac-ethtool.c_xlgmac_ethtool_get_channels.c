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
struct xlgmac_pdata {int /*<<< orphan*/  tx_q_count; int /*<<< orphan*/  rx_q_count; } ;
struct net_device {int dummy; } ;
struct ethtool_channels {int /*<<< orphan*/  tx_count; int /*<<< orphan*/  rx_count; void* max_tx; void* max_rx; } ;

/* Variables and functions */
 void* XLGMAC_MAX_DMA_CHANNELS ; 
 struct xlgmac_pdata* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void xlgmac_ethtool_get_channels(struct net_device *netdev,
					struct ethtool_channels *channel)
{
	struct xlgmac_pdata *pdata = netdev_priv(netdev);

	channel->max_rx = XLGMAC_MAX_DMA_CHANNELS;
	channel->max_tx = XLGMAC_MAX_DMA_CHANNELS;
	channel->rx_count = pdata->rx_q_count;
	channel->tx_count = pdata->tx_q_count;
}