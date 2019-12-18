#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_5__ {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {int /*<<< orphan*/  dev; TYPE_1__ stats; } ;
struct cpmac_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  regs; struct cpmac_desc* desc_ring; } ;
struct cpmac_desc {TYPE_2__* skb; int /*<<< orphan*/  data_mapping; scalar_t__ mapping; } ;
struct TYPE_6__ {scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPMAC_TX_ACK (int) ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 scalar_t__ __netif_subqueue_stopped (struct net_device*,int) ; 
 int /*<<< orphan*/  cpmac_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_consume_skb_irq (TYPE_2__*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (TYPE_2__*) ; 
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,TYPE_2__*,scalar_t__) ; 
 struct cpmac_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_msg_tx_done (struct cpmac_priv*) ; 
 scalar_t__ netif_msg_tx_err (struct cpmac_priv*) ; 
 int /*<<< orphan*/  netif_wake_subqueue (struct net_device*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cpmac_end_xmit(struct net_device *dev, int queue)
{
	struct cpmac_desc *desc;
	struct cpmac_priv *priv = netdev_priv(dev);

	desc = &priv->desc_ring[queue];
	cpmac_write(priv->regs, CPMAC_TX_ACK(queue), (u32)desc->mapping);
	if (likely(desc->skb)) {
		spin_lock(&priv->lock);
		dev->stats.tx_packets++;
		dev->stats.tx_bytes += desc->skb->len;
		spin_unlock(&priv->lock);
		dma_unmap_single(&dev->dev, desc->data_mapping, desc->skb->len,
				 DMA_TO_DEVICE);

		if (unlikely(netif_msg_tx_done(priv)))
			netdev_dbg(dev, "sent 0x%p, len=%d\n",
				   desc->skb, desc->skb->len);

		dev_consume_skb_irq(desc->skb);
		desc->skb = NULL;
		if (__netif_subqueue_stopped(dev, queue))
			netif_wake_subqueue(dev, queue);
	} else {
		if (netif_msg_tx_err(priv) && net_ratelimit())
			netdev_warn(dev, "end_xmit: spurious interrupt\n");
		if (__netif_subqueue_stopped(dev, queue))
			netif_wake_subqueue(dev, queue);
	}
}