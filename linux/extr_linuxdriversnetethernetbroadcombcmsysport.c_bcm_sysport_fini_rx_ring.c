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
struct bcm_sysport_priv {unsigned int num_rx_bds; int /*<<< orphan*/  netdev; struct bcm_sysport_cb* rx_cbs; TYPE_1__* pdev; } ;
struct bcm_sysport_cb {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int RDMA_DISABLED ; 
 int /*<<< orphan*/  RDMA_STATUS ; 
 int /*<<< orphan*/  RX_BUF_LENGTH ; 
 int /*<<< orphan*/  bcm_sysport_free_cb (struct bcm_sysport_cb*) ; 
 int /*<<< orphan*/  dma_addr ; 
 scalar_t__ dma_unmap_addr (struct bcm_sysport_cb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  kfree (struct bcm_sysport_cb*) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_dbg (struct bcm_sysport_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int rdma_readl (struct bcm_sysport_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm_sysport_fini_rx_ring(struct bcm_sysport_priv *priv)
{
	struct bcm_sysport_cb *cb;
	unsigned int i;
	u32 reg;

	/* Caller should ensure RDMA is disabled */
	reg = rdma_readl(priv, RDMA_STATUS);
	if (!(reg & RDMA_DISABLED))
		netdev_warn(priv->netdev, "RDMA not stopped!\n");

	for (i = 0; i < priv->num_rx_bds; i++) {
		cb = &priv->rx_cbs[i];
		if (dma_unmap_addr(cb, dma_addr))
			dma_unmap_single(&priv->pdev->dev,
					 dma_unmap_addr(cb, dma_addr),
					 RX_BUF_LENGTH, DMA_FROM_DEVICE);
		bcm_sysport_free_cb(cb);
	}

	kfree(priv->rx_cbs);
	priv->rx_cbs = NULL;

	netif_dbg(priv, hw, priv->netdev, "RDMA fini done\n");
}