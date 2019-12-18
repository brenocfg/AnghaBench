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
struct stmmac_priv {int dummy; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int init_dma_rx_desc_rings (struct net_device*,int /*<<< orphan*/ ) ; 
 int init_dma_tx_desc_rings (struct net_device*) ; 
 struct stmmac_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_msg_hw (struct stmmac_priv*) ; 
 int /*<<< orphan*/  stmmac_clear_descriptors (struct stmmac_priv*) ; 
 int /*<<< orphan*/  stmmac_display_rings (struct stmmac_priv*) ; 

__attribute__((used)) static int init_dma_desc_rings(struct net_device *dev, gfp_t flags)
{
	struct stmmac_priv *priv = netdev_priv(dev);
	int ret;

	ret = init_dma_rx_desc_rings(dev, flags);
	if (ret)
		return ret;

	ret = init_dma_tx_desc_rings(dev);

	stmmac_clear_descriptors(priv);

	if (netif_msg_hw(priv))
		stmmac_display_rings(priv);

	return ret;
}