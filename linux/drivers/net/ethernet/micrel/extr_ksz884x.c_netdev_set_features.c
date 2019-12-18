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
struct ksz_hw {int rx_cfg; scalar_t__ io; scalar_t__ enabled; } ;
struct dev_priv {struct dev_info* adapter; } ;
struct dev_info {int /*<<< orphan*/  lock; struct ksz_hw hw; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int DMA_RX_CSUM_IP ; 
 int DMA_RX_CSUM_TCP ; 
 scalar_t__ KS_DMA_RX_CTRL ; 
 int NETIF_F_RXCSUM ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct dev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int netdev_set_features(struct net_device *dev,
	netdev_features_t features)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_hw *hw = &hw_priv->hw;

	mutex_lock(&hw_priv->lock);

	/* see note in hw_setup() */
	if (features & NETIF_F_RXCSUM)
		hw->rx_cfg |= DMA_RX_CSUM_TCP | DMA_RX_CSUM_IP;
	else
		hw->rx_cfg &= ~(DMA_RX_CSUM_TCP | DMA_RX_CSUM_IP);

	if (hw->enabled)
		writel(hw->rx_cfg, hw->io + KS_DMA_RX_CTRL);

	mutex_unlock(&hw_priv->lock);

	return 0;
}