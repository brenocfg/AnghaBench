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
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  protocol; } ;
struct TYPE_4__ {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  rx_errors; } ;
struct net_device {TYPE_2__ stats; } ;
struct TYPE_3__ {struct hix5hd2_desc* desc; } ;
struct hix5hd2_priv {scalar_t__ base; int /*<<< orphan*/  napi; int /*<<< orphan*/  dev; TYPE_1__ rx_bq; struct sk_buff** rx_skb; } ;
struct hix5hd2_desc {int /*<<< orphan*/  buff_addr; int /*<<< orphan*/  cmd; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int CIRC_CNT (int,int,int /*<<< orphan*/ ) ; 
 int DESC_DATA_LEN_OFF ; 
 int DESC_DATA_MASK ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 scalar_t__ MAC_MAX_FRAME_SIZE ; 
 scalar_t__ RX_BQ_RD_ADDR ; 
 scalar_t__ RX_BQ_WR_ADDR ; 
 int /*<<< orphan*/  RX_DESC_NUM ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_byte (int) ; 
 int dma_cnt (int /*<<< orphan*/ ) ; 
 int dma_ring_incr (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  hix5hd2_rx_refill (struct hix5hd2_priv*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_gro_receive (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,...) ; 
 struct hix5hd2_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int hix5hd2_rx(struct net_device *dev, int limit)
{
	struct hix5hd2_priv *priv = netdev_priv(dev);
	struct sk_buff *skb;
	struct hix5hd2_desc *desc;
	dma_addr_t addr;
	u32 start, end, num, pos, i, len;

	/* software read pointer */
	start = dma_cnt(readl_relaxed(priv->base + RX_BQ_RD_ADDR));
	/* logic write pointer */
	end = dma_cnt(readl_relaxed(priv->base + RX_BQ_WR_ADDR));
	num = CIRC_CNT(end, start, RX_DESC_NUM);
	if (num > limit)
		num = limit;

	/* ensure get updated desc */
	rmb();
	for (i = 0, pos = start; i < num; i++) {
		skb = priv->rx_skb[pos];
		if (unlikely(!skb)) {
			netdev_err(dev, "inconsistent rx_skb\n");
			break;
		}
		priv->rx_skb[pos] = NULL;

		desc = priv->rx_bq.desc + pos;
		len = (le32_to_cpu(desc->cmd) >> DESC_DATA_LEN_OFF) &
		       DESC_DATA_MASK;
		addr = le32_to_cpu(desc->buff_addr);
		dma_unmap_single(priv->dev, addr, MAC_MAX_FRAME_SIZE,
				 DMA_FROM_DEVICE);

		skb_put(skb, len);
		if (skb->len > MAC_MAX_FRAME_SIZE) {
			netdev_err(dev, "rcv len err, len = %d\n", skb->len);
			dev->stats.rx_errors++;
			dev->stats.rx_length_errors++;
			dev_kfree_skb_any(skb);
			goto next;
		}

		skb->protocol = eth_type_trans(skb, dev);
		napi_gro_receive(&priv->napi, skb);
		dev->stats.rx_packets++;
		dev->stats.rx_bytes += skb->len;
next:
		pos = dma_ring_incr(pos, RX_DESC_NUM);
	}

	if (pos != start)
		writel_relaxed(dma_byte(pos), priv->base + RX_BQ_RD_ADDR);

	hix5hd2_rx_refill(priv);

	return num;
}