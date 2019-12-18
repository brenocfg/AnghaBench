#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sk_buff {int /*<<< orphan*/  protocol; int /*<<< orphan*/  len; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_dropped; } ;
struct net_device {TYPE_2__ dev; TYPE_1__ stats; } ;
struct mpc52xx_fec_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  rx_dmatsk; } ;
struct bcom_fec_bd {int skb_pa; } ;
struct bcom_bd {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int BCOM_FEC_RX_BD_ERRORS ; 
 int BCOM_FEC_RX_BD_LEN_MASK ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  FEC_RX_BUFFER_SIZE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ bcom_buffer_done (int /*<<< orphan*/ ) ; 
 struct sk_buff* bcom_retrieve_buffer (int /*<<< orphan*/ ,int*,struct bcom_bd**) ; 
 int /*<<< orphan*/  dev_notice (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  mpc52xx_fec_rx_submit (struct net_device*,struct sk_buff*) ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,int /*<<< orphan*/ ) ; 
 struct mpc52xx_fec_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_defer_rx_timestamp (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t mpc52xx_fec_rx_interrupt(int irq, void *dev_id)
{
	struct net_device *dev = dev_id;
	struct mpc52xx_fec_priv *priv = netdev_priv(dev);
	struct sk_buff *rskb; /* received sk_buff */
	struct sk_buff *skb;  /* new sk_buff to enqueue in its place */
	struct bcom_fec_bd *bd;
	u32 status, physaddr;
	int length;

	spin_lock(&priv->lock);

	while (bcom_buffer_done(priv->rx_dmatsk)) {

		rskb = bcom_retrieve_buffer(priv->rx_dmatsk, &status,
					    (struct bcom_bd **)&bd);
		physaddr = bd->skb_pa;

		/* Test for errors in received frame */
		if (status & BCOM_FEC_RX_BD_ERRORS) {
			/* Drop packet and reuse the buffer */
			mpc52xx_fec_rx_submit(dev, rskb);
			dev->stats.rx_dropped++;
			continue;
		}

		/* skbs are allocated on open, so now we allocate a new one,
		 * and remove the old (with the packet) */
		skb = netdev_alloc_skb(dev, FEC_RX_BUFFER_SIZE);
		if (!skb) {
			/* Can't get a new one : reuse the same & drop pkt */
			dev_notice(&dev->dev, "Low memory - dropped packet.\n");
			mpc52xx_fec_rx_submit(dev, rskb);
			dev->stats.rx_dropped++;
			continue;
		}

		/* Enqueue the new sk_buff back on the hardware */
		mpc52xx_fec_rx_submit(dev, skb);

		/* Process the received skb - Drop the spin lock while
		 * calling into the network stack */
		spin_unlock(&priv->lock);

		dma_unmap_single(dev->dev.parent, physaddr, rskb->len,
				 DMA_FROM_DEVICE);
		length = status & BCOM_FEC_RX_BD_LEN_MASK;
		skb_put(rskb, length - 4);	/* length without CRC32 */
		rskb->protocol = eth_type_trans(rskb, dev);
		if (!skb_defer_rx_timestamp(rskb))
			netif_rx(rskb);

		spin_lock(&priv->lock);
	}

	spin_unlock(&priv->lock);

	return IRQ_HANDLED;
}