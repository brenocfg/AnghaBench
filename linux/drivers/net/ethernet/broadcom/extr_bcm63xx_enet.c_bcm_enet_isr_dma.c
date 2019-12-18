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
struct bcm_enet_priv {int /*<<< orphan*/  napi; int /*<<< orphan*/  tx_chan; int /*<<< orphan*/  rx_chan; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENETDMAC_IRMASK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  enet_dmac_writel (struct bcm_enet_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 struct bcm_enet_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static irqreturn_t bcm_enet_isr_dma(int irq, void *dev_id)
{
	struct net_device *dev;
	struct bcm_enet_priv *priv;

	dev = dev_id;
	priv = netdev_priv(dev);

	/* mask rx/tx interrupts */
	enet_dmac_writel(priv, 0, ENETDMAC_IRMASK, priv->rx_chan);
	enet_dmac_writel(priv, 0, ENETDMAC_IRMASK, priv->tx_chan);

	napi_schedule(&priv->napi);

	return IRQ_HANDLED;
}