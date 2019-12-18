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
struct sk_buff {int /*<<< orphan*/  len; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct net_device {TYPE_1__ dev; } ;
struct mpc52xx_fec_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  tx_dmatsk; } ;
struct bcom_fec_bd {int /*<<< orphan*/  skb_pa; } ;
struct bcom_bd {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ bcom_buffer_done (int /*<<< orphan*/ ) ; 
 struct sk_buff* bcom_retrieve_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct bcom_bd**) ; 
 int /*<<< orphan*/  dev_consume_skb_irq (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mpc52xx_fec_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t mpc52xx_fec_tx_interrupt(int irq, void *dev_id)
{
	struct net_device *dev = dev_id;
	struct mpc52xx_fec_priv *priv = netdev_priv(dev);

	spin_lock(&priv->lock);
	while (bcom_buffer_done(priv->tx_dmatsk)) {
		struct sk_buff *skb;
		struct bcom_fec_bd *bd;
		skb = bcom_retrieve_buffer(priv->tx_dmatsk, NULL,
				(struct bcom_bd **)&bd);
		dma_unmap_single(dev->dev.parent, bd->skb_pa, skb->len,
				 DMA_TO_DEVICE);

		dev_consume_skb_irq(skb);
	}
	spin_unlock(&priv->lock);

	netif_wake_queue(dev);

	return IRQ_HANDLED;
}