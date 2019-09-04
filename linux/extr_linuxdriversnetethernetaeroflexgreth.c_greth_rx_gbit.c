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
struct sk_buff {int /*<<< orphan*/  protocol; int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  data; } ;
struct TYPE_4__ {int rx_bytes; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_length_errors; } ;
struct net_device {int features; TYPE_2__ stats; } ;
struct greth_private {int rx_cur; int /*<<< orphan*/  devlock; int /*<<< orphan*/  dev; struct sk_buff** rx_skbuff; TYPE_1__* regs; struct greth_bd* rx_bd_base; } ;
struct greth_bd {int /*<<< orphan*/  stat; int /*<<< orphan*/  addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int GRETH_BD_EN ; 
 int GRETH_BD_IE ; 
 int GRETH_BD_LEN ; 
 int GRETH_BD_WR ; 
 int GRETH_INT_RE ; 
 int GRETH_INT_RX ; 
 int /*<<< orphan*/  GRETH_REGSAVE (int /*<<< orphan*/ ,int) ; 
 int GRETH_RXBD_ERR_AE ; 
 int GRETH_RXBD_ERR_CRC ; 
 int GRETH_RXBD_ERR_FT ; 
 int GRETH_RXBD_ERR_LE ; 
 int GRETH_RXBD_ERR_OE ; 
 size_t GRETH_RXBD_NUM_MASK ; 
 int GRETH_RXBD_STATUS ; 
 scalar_t__ MAX_FRAME_SIZE ; 
 int NETIF_F_RXCSUM ; 
 scalar_t__ NET_IP_ALIGN ; 
 size_t NEXT_RX (size_t) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_mapping_error (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  greth_enable_rx (struct greth_private*) ; 
 int /*<<< orphan*/  greth_print_rx_packet (int /*<<< orphan*/ ,int) ; 
 int greth_read_bd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  greth_write_bd (int /*<<< orphan*/ *,int) ; 
 scalar_t__ hw_checksummed (int) ; 
 int /*<<< orphan*/  mb () ; 
 scalar_t__ net_ratelimit () ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,scalar_t__) ; 
 struct greth_private* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_msg_pktdata (struct greth_private*) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  phys_to_virt (int) ; 
 int /*<<< orphan*/  skb_checksum_none_assert (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int greth_rx_gbit(struct net_device *dev, int limit)
{
	struct greth_private *greth;
	struct greth_bd *bdp;
	struct sk_buff *skb, *newskb;
	int pkt_len;
	int bad, count = 0;
	u32 status, dma_addr;
	unsigned long flags;

	greth = netdev_priv(dev);

	for (count = 0; count < limit; ++count) {

		bdp = greth->rx_bd_base + greth->rx_cur;
		skb = greth->rx_skbuff[greth->rx_cur];
		GRETH_REGSAVE(greth->regs->status, GRETH_INT_RE | GRETH_INT_RX);
		mb();
		status = greth_read_bd(&bdp->stat);
		bad = 0;

		if (status & GRETH_BD_EN)
			break;

		/* Check status for errors. */
		if (unlikely(status & GRETH_RXBD_STATUS)) {

			if (status & GRETH_RXBD_ERR_FT) {
				dev->stats.rx_length_errors++;
				bad = 1;
			} else if (status &
				   (GRETH_RXBD_ERR_AE | GRETH_RXBD_ERR_OE | GRETH_RXBD_ERR_LE)) {
				dev->stats.rx_frame_errors++;
				bad = 1;
			} else if (status & GRETH_RXBD_ERR_CRC) {
				dev->stats.rx_crc_errors++;
				bad = 1;
			}
		}

		/* Allocate new skb to replace current, not needed if the
		 * current skb can be reused */
		if (!bad && (newskb=netdev_alloc_skb(dev, MAX_FRAME_SIZE + NET_IP_ALIGN))) {
			skb_reserve(newskb, NET_IP_ALIGN);

			dma_addr = dma_map_single(greth->dev,
						      newskb->data,
						      MAX_FRAME_SIZE + NET_IP_ALIGN,
						      DMA_FROM_DEVICE);

			if (!dma_mapping_error(greth->dev, dma_addr)) {
				/* Process the incoming frame. */
				pkt_len = status & GRETH_BD_LEN;

				dma_unmap_single(greth->dev,
						 greth_read_bd(&bdp->addr),
						 MAX_FRAME_SIZE + NET_IP_ALIGN,
						 DMA_FROM_DEVICE);

				if (netif_msg_pktdata(greth))
					greth_print_rx_packet(phys_to_virt(greth_read_bd(&bdp->addr)), pkt_len);

				skb_put(skb, pkt_len);

				if (dev->features & NETIF_F_RXCSUM && hw_checksummed(status))
					skb->ip_summed = CHECKSUM_UNNECESSARY;
				else
					skb_checksum_none_assert(skb);

				skb->protocol = eth_type_trans(skb, dev);
				dev->stats.rx_packets++;
				dev->stats.rx_bytes += pkt_len;
				netif_receive_skb(skb);

				greth->rx_skbuff[greth->rx_cur] = newskb;
				greth_write_bd(&bdp->addr, dma_addr);
			} else {
				if (net_ratelimit())
					dev_warn(greth->dev, "Could not create DMA mapping, dropping packet\n");
				dev_kfree_skb(newskb);
				/* reusing current skb, so it is a drop */
				dev->stats.rx_dropped++;
			}
		} else if (bad) {
			/* Bad Frame transfer, the skb is reused */
			dev->stats.rx_dropped++;
		} else {
			/* Failed Allocating a new skb. This is rather stupid
			 * but the current "filled" skb is reused, as if
			 * transfer failure. One could argue that RX descriptor
			 * table handling should be divided into cleaning and
			 * filling as the TX part of the driver
			 */
			if (net_ratelimit())
				dev_warn(greth->dev, "Could not allocate SKB, dropping packet\n");
			/* reusing current skb, so it is a drop */
			dev->stats.rx_dropped++;
		}

		status = GRETH_BD_EN | GRETH_BD_IE;
		if (greth->rx_cur == GRETH_RXBD_NUM_MASK) {
			status |= GRETH_BD_WR;
		}

		wmb();
		greth_write_bd(&bdp->stat, status);
		spin_lock_irqsave(&greth->devlock, flags);
		greth_enable_rx(greth);
		spin_unlock_irqrestore(&greth->devlock, flags);
		greth->rx_cur = NEXT_RX(greth->rx_cur);
	}

	return count;

}