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
typedef  scalar_t__ u32 ;
struct sk_buff {scalar_t__ len; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {struct hix5hd2_desc* desc; } ;
struct hix5hd2_priv {int /*<<< orphan*/  netdev; scalar_t__ base; struct sk_buff** tx_skb; int /*<<< orphan*/  dev; TYPE_1__ tx_rq; } ;
struct hix5hd2_desc {int /*<<< orphan*/  buff_addr; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {scalar_t__ nr_frags; } ;

/* Variables and functions */
 scalar_t__ CIRC_CNT (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  TX_DESC_NUM ; 
 scalar_t__ TX_RQ_RD_ADDR ; 
 scalar_t__ TX_RQ_WR_ADDR ; 
 int /*<<< orphan*/  dev_consume_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_byte (scalar_t__) ; 
 scalar_t__ dma_cnt (int /*<<< orphan*/ ) ; 
 scalar_t__ dma_ring_incr (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hix5hd2_clean_sg_desc (struct hix5hd2_priv*,struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_completed_queue (struct net_device*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct hix5hd2_priv* netdev_priv (struct net_device*) ; 
 int netif_queue_stopped (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_lock (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_unlock (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void hix5hd2_xmit_reclaim(struct net_device *dev)
{
	struct sk_buff *skb;
	struct hix5hd2_desc *desc;
	struct hix5hd2_priv *priv = netdev_priv(dev);
	unsigned int bytes_compl = 0, pkts_compl = 0;
	u32 start, end, num, pos, i;
	dma_addr_t addr;

	netif_tx_lock(dev);

	/* software read */
	start = dma_cnt(readl_relaxed(priv->base + TX_RQ_RD_ADDR));
	/* logic write */
	end = dma_cnt(readl_relaxed(priv->base + TX_RQ_WR_ADDR));
	num = CIRC_CNT(end, start, TX_DESC_NUM);

	for (i = 0, pos = start; i < num; i++) {
		skb = priv->tx_skb[pos];
		if (unlikely(!skb)) {
			netdev_err(dev, "inconsistent tx_skb\n");
			break;
		}

		pkts_compl++;
		bytes_compl += skb->len;
		desc = priv->tx_rq.desc + pos;

		if (skb_shinfo(skb)->nr_frags) {
			hix5hd2_clean_sg_desc(priv, skb, pos);
		} else {
			addr = le32_to_cpu(desc->buff_addr);
			dma_unmap_single(priv->dev, addr, skb->len,
					 DMA_TO_DEVICE);
		}

		priv->tx_skb[pos] = NULL;
		dev_consume_skb_any(skb);
		pos = dma_ring_incr(pos, TX_DESC_NUM);
	}

	if (pos != start)
		writel_relaxed(dma_byte(pos), priv->base + TX_RQ_RD_ADDR);

	netif_tx_unlock(dev);

	if (pkts_compl || bytes_compl)
		netdev_completed_queue(dev, pkts_compl, bytes_compl);

	if (unlikely(netif_queue_stopped(priv->netdev)) && pkts_compl)
		netif_wake_queue(priv->netdev);
}