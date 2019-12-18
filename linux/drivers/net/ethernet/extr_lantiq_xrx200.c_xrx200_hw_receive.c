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
struct xrx200_priv {struct net_device* net_dev; } ;
struct TYPE_3__ {size_t desc; struct ltq_dma_desc* desc_base; } ;
struct xrx200_chan {TYPE_1__ dma; struct sk_buff** skb; struct xrx200_priv* priv; } ;
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct TYPE_4__ {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct net_device {TYPE_2__ stats; } ;
struct ltq_dma_desc {int ctl; } ;

/* Variables and functions */
 int ETH_FCS_LEN ; 
 size_t LTQ_DESC_NUM ; 
 int LTQ_DMA_SIZE_MASK ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int xrx200_alloc_skb (struct xrx200_chan*) ; 

__attribute__((used)) static int xrx200_hw_receive(struct xrx200_chan *ch)
{
	struct xrx200_priv *priv = ch->priv;
	struct ltq_dma_desc *desc = &ch->dma.desc_base[ch->dma.desc];
	struct sk_buff *skb = ch->skb[ch->dma.desc];
	int len = (desc->ctl & LTQ_DMA_SIZE_MASK);
	struct net_device *net_dev = priv->net_dev;
	int ret;

	ret = xrx200_alloc_skb(ch);

	ch->dma.desc++;
	ch->dma.desc %= LTQ_DESC_NUM;

	if (ret) {
		netdev_err(net_dev, "failed to allocate new rx buffer\n");
		return ret;
	}

	skb_put(skb, len);
	skb->protocol = eth_type_trans(skb, net_dev);
	netif_receive_skb(skb);
	net_dev->stats.rx_packets++;
	net_dev->stats.rx_bytes += len - ETH_FCS_LEN;

	return 0;
}