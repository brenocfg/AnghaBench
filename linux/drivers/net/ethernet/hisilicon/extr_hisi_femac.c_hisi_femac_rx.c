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
typedef  size_t u32 ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  protocol; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  rx_errors; } ;
struct net_device {TYPE_1__ stats; } ;
struct hisi_femac_queue {size_t tail; size_t num; int /*<<< orphan*/ * dma_phys; struct sk_buff** skb; } ;
struct hisi_femac_priv {int /*<<< orphan*/  napi; int /*<<< orphan*/  dev; scalar_t__ glb_base; scalar_t__ port_base; struct hisi_femac_queue rxq; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 scalar_t__ ETH_FCS_LEN ; 
 scalar_t__ GLB_IRQ_RAW ; 
 scalar_t__ IQFRM_DES ; 
 int IRQ_INT_RX_RDY ; 
 scalar_t__ MAX_FRAME_SIZE ; 
 size_t RX_FRAME_LEN_MASK ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  hisi_femac_rx_refill (struct hisi_femac_priv*) ; 
 int /*<<< orphan*/  napi_gro_receive (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,size_t) ; 
 struct hisi_femac_priv* netdev_priv (struct net_device*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,size_t) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int hisi_femac_rx(struct net_device *dev, int limit)
{
	struct hisi_femac_priv *priv = netdev_priv(dev);
	struct hisi_femac_queue *rxq = &priv->rxq;
	struct sk_buff *skb;
	dma_addr_t addr;
	u32 rx_pkt_info, pos, len, rx_pkts_num = 0;

	pos = rxq->tail;
	while (readl(priv->glb_base + GLB_IRQ_RAW) & IRQ_INT_RX_RDY) {
		rx_pkt_info = readl(priv->port_base + IQFRM_DES);
		len = rx_pkt_info & RX_FRAME_LEN_MASK;
		len -= ETH_FCS_LEN;

		/* tell hardware we will deal with this packet */
		writel(IRQ_INT_RX_RDY, priv->glb_base + GLB_IRQ_RAW);

		rx_pkts_num++;

		skb = rxq->skb[pos];
		if (unlikely(!skb)) {
			netdev_err(dev, "rx skb NULL. pos=%d\n", pos);
			break;
		}
		rxq->skb[pos] = NULL;

		addr = rxq->dma_phys[pos];
		dma_unmap_single(priv->dev, addr, MAX_FRAME_SIZE,
				 DMA_FROM_DEVICE);
		skb_put(skb, len);
		if (unlikely(skb->len > MAX_FRAME_SIZE)) {
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
		pos = (pos + 1) % rxq->num;
		if (rx_pkts_num >= limit)
			break;
	}
	rxq->tail = pos;

	hisi_femac_rx_refill(priv);

	return rx_pkts_num;
}