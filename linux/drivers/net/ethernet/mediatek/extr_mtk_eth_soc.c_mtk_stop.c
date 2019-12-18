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
struct net_device {int dummy; } ;
struct mtk_mac {int /*<<< orphan*/  phylink; struct mtk_eth* hw; } ;
struct mtk_eth {TYPE_1__* soc; int /*<<< orphan*/  rx_napi; int /*<<< orphan*/  tx_napi; int /*<<< orphan*/  dma_refcnt; } ;
struct TYPE_2__ {int /*<<< orphan*/  caps; } ;

/* Variables and functions */
 scalar_t__ MTK_HAS_CAPS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTK_PDMA_GLO_CFG ; 
 int /*<<< orphan*/  MTK_QDMA ; 
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
 int /*<<< orphan*/  phylink_disconnect_phy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phylink_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_dec_and_test (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mtk_stop(struct net_device *dev)
{
	struct mtk_mac *mac = netdev_priv(dev);
	struct mtk_eth *eth = mac->hw;

	phylink_stop(mac->phylink);

	netif_tx_disable(dev);

	phylink_disconnect_phy(mac->phylink);

	/* only shutdown DMA if this is the last user */
	if (!refcount_dec_and_test(&eth->dma_refcnt))
		return 0;

	mtk_tx_irq_disable(eth, MTK_TX_DONE_INT);
	mtk_rx_irq_disable(eth, MTK_RX_DONE_INT);
	napi_disable(&eth->tx_napi);
	napi_disable(&eth->rx_napi);

	if (MTK_HAS_CAPS(eth->soc->caps, MTK_QDMA))
		mtk_stop_dma(eth, MTK_QDMA_GLO_CFG);
	mtk_stop_dma(eth, MTK_PDMA_GLO_CFG);

	mtk_dma_free(eth);

	return 0;
}