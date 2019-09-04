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
struct net_device {int /*<<< orphan*/  phydev; } ;
struct mtk_mac {struct mtk_eth* hw; } ;
struct mtk_eth {int /*<<< orphan*/  dma_refcnt; int /*<<< orphan*/  rx_napi; int /*<<< orphan*/  tx_napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTK_RX_DONE_INT ; 
 int /*<<< orphan*/  MTK_TX_DONE_INT ; 
 int /*<<< orphan*/  mtk_rx_irq_enable (struct mtk_eth*,int /*<<< orphan*/ ) ; 
 int mtk_start_dma (struct mtk_eth*) ; 
 int /*<<< orphan*/  mtk_tx_irq_enable (struct mtk_eth*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct mtk_mac* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  phy_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int mtk_open(struct net_device *dev)
{
	struct mtk_mac *mac = netdev_priv(dev);
	struct mtk_eth *eth = mac->hw;

	/* we run 2 netdevs on the same dma ring so we only bring it up once */
	if (!refcount_read(&eth->dma_refcnt)) {
		int err = mtk_start_dma(eth);

		if (err)
			return err;

		napi_enable(&eth->tx_napi);
		napi_enable(&eth->rx_napi);
		mtk_tx_irq_enable(eth, MTK_TX_DONE_INT);
		mtk_rx_irq_enable(eth, MTK_RX_DONE_INT);
		refcount_set(&eth->dma_refcnt, 1);
	}
	else
		refcount_inc(&eth->dma_refcnt);

	phy_start(dev->phydev);
	netif_start_queue(dev);

	return 0;
}