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
struct mtk_eth {int /*<<< orphan*/  rx_napi; int /*<<< orphan*/  tx_napi; int /*<<< orphan*/  dma_refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTK_PDMA_GLO_CFG ; 
 int /*<<< orphan*/  MTK_QDMA_GLO_CFG ; 
 int /*<<< orphan*/  MTK_RX_DONE_INT ; 
 int /*<<< orphan*/  MTK_TX_DONE_INT ; 
 int /*<<< orphan*/  mtk_dma_free (struct mtk_eth*) ; 
 int /*<<< orphan*/  mtk_rx_irq_disable (struct mtk_eth*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_stop_dma (struct mtk_eth*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_tx_irq_disable (struct mtk_eth*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct mtk_mac* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_disable (struct net_device*) ; 
 int /*<<< orphan*/  phy_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_dec_and_test (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mtk_stop(struct net_device *dev)
{
	struct mtk_mac *mac = netdev_priv(dev);
	struct mtk_eth *eth = mac->hw;

	netif_tx_disable(dev);
	phy_stop(dev->phydev);

	/* only shutdown DMA if this is the last user */
	if (!refcount_dec_and_test(&eth->dma_refcnt))
		return 0;

	mtk_tx_irq_disable(eth, MTK_TX_DONE_INT);
	mtk_rx_irq_disable(eth, MTK_RX_DONE_INT);
	napi_disable(&eth->tx_napi);
	napi_disable(&eth->rx_napi);

	mtk_stop_dma(eth, MTK_QDMA_GLO_CFG);
	mtk_stop_dma(eth, MTK_PDMA_GLO_CFG);

	mtk_dma_free(eth);

	return 0;
}