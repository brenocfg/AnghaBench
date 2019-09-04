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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct ethtool_coalesce {int tx_coalesce_usecs; int tx_max_coalesced_frames; int rx_coalesce_usecs; int rx_max_coalesced_frames; int /*<<< orphan*/  use_adaptive_rx_coalesce; } ;
struct TYPE_2__ {int /*<<< orphan*/  use_dim; } ;
struct bcm_sysport_priv {TYPE_1__ dim; } ;

/* Variables and functions */
 int RDMA_INTR_THRESH_MASK ; 
 int /*<<< orphan*/  RDMA_MBDONE_INTR ; 
 int RDMA_TIMEOUT_SHIFT ; 
 int RING_INTR_THRESH_MASK ; 
 int RING_TIMEOUT_SHIFT ; 
 int /*<<< orphan*/  TDMA_DESC_RING_INTR_CONTROL (int /*<<< orphan*/ ) ; 
 struct bcm_sysport_priv* netdev_priv (struct net_device*) ; 
 int rdma_readl (struct bcm_sysport_priv*,int /*<<< orphan*/ ) ; 
 int tdma_readl (struct bcm_sysport_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm_sysport_get_coalesce(struct net_device *dev,
				    struct ethtool_coalesce *ec)
{
	struct bcm_sysport_priv *priv = netdev_priv(dev);
	u32 reg;

	reg = tdma_readl(priv, TDMA_DESC_RING_INTR_CONTROL(0));

	ec->tx_coalesce_usecs = (reg >> RING_TIMEOUT_SHIFT) * 8192 / 1000;
	ec->tx_max_coalesced_frames = reg & RING_INTR_THRESH_MASK;

	reg = rdma_readl(priv, RDMA_MBDONE_INTR);

	ec->rx_coalesce_usecs = (reg >> RDMA_TIMEOUT_SHIFT) * 8192 / 1000;
	ec->rx_max_coalesced_frames = reg & RDMA_INTR_THRESH_MASK;
	ec->use_adaptive_rx_coalesce = priv->dim.use_dim;

	return 0;
}