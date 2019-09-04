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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct nb8800_tx_buf {int dma_desc; int chain_len; int /*<<< orphan*/  ready; } ;
struct nb8800_priv {size_t tx_queue; struct nb8800_tx_buf* tx_bufs; } ;

/* Variables and functions */
 int /*<<< orphan*/  NB8800_TXC_CR ; 
 int /*<<< orphan*/  NB8800_TX_DESC_ADDR ; 
 int TCR_EN ; 
 int TX_DESC_COUNT ; 
 int nb8800_readl (struct nb8800_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nb8800_writel (struct nb8800_priv*,int /*<<< orphan*/ ,int) ; 
 struct nb8800_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void __nb8800_tx_dma_start(struct net_device *dev)
{
	struct nb8800_priv *priv = netdev_priv(dev);
	struct nb8800_tx_buf *txb;
	u32 txc_cr;

	txb = &priv->tx_bufs[priv->tx_queue];
	if (!txb->ready)
		return;

	txc_cr = nb8800_readl(priv, NB8800_TXC_CR);
	if (txc_cr & TCR_EN)
		return;

	nb8800_writel(priv, NB8800_TX_DESC_ADDR, txb->dma_desc);
	wmb();		/* ensure desc addr is written before starting DMA */
	nb8800_writel(priv, NB8800_TXC_CR, txc_cr | TCR_EN);

	priv->tx_queue = (priv->tx_queue + txb->chain_len) % TX_DESC_COUNT;
}