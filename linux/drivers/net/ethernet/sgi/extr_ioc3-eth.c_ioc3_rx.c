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
struct sk_buff {scalar_t__ data; int /*<<< orphan*/  protocol; } ;
struct TYPE_3__ {int rx_bytes; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; } ;
struct net_device {int features; TYPE_1__ stats; } ;
struct ioc3_private {unsigned long* rxr; int rx_ci; int rx_pi; TYPE_2__* regs; struct sk_buff** rx_skbs; int /*<<< orphan*/  dma_dev; } ;
struct ioc3_erxbuf {scalar_t__ w0; scalar_t__ err; } ;
typedef  unsigned long dma_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  erpir; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ERPIR_ARM ; 
 int ERXBUF_BYTECNT_SHIFT ; 
 int ERXBUF_CRCERR ; 
 int ERXBUF_FRAMERR ; 
 int ERXBUF_GOODPKT ; 
 int ERXBUF_IPCKSUM_MASK ; 
 int ERXBUF_V ; 
 int NETIF_F_RXCSUM ; 
 int /*<<< orphan*/  PCI64_ATTR_BAR ; 
 int /*<<< orphan*/  RX_BUF_SIZE ; 
 scalar_t__ RX_OFFSET ; 
 int RX_RING_MASK ; 
 int be32_to_cpu (scalar_t__) ; 
 unsigned long cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 scalar_t__ ioc3_alloc_skb (struct ioc3_private*,struct sk_buff**,struct ioc3_erxbuf**,unsigned long*) ; 
 int /*<<< orphan*/  ioc3_map (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioc3_tcpudp_checksum (struct sk_buff*,int,int) ; 
 scalar_t__ likely (int) ; 
 struct ioc3_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void ioc3_rx(struct net_device *dev)
{
	struct ioc3_private *ip = netdev_priv(dev);
	struct sk_buff *skb, *new_skb;
	int rx_entry, n_entry, len;
	struct ioc3_erxbuf *rxb;
	unsigned long *rxr;
	dma_addr_t d;
	u32 w0, err;

	rxr = ip->rxr;		/* Ring base */
	rx_entry = ip->rx_ci;				/* RX consume index */
	n_entry = ip->rx_pi;

	skb = ip->rx_skbs[rx_entry];
	rxb = (struct ioc3_erxbuf *)(skb->data - RX_OFFSET);
	w0 = be32_to_cpu(rxb->w0);

	while (w0 & ERXBUF_V) {
		err = be32_to_cpu(rxb->err);		/* It's valid ...  */
		if (err & ERXBUF_GOODPKT) {
			len = ((w0 >> ERXBUF_BYTECNT_SHIFT) & 0x7ff) - 4;
			skb_put(skb, len);
			skb->protocol = eth_type_trans(skb, dev);

			if (ioc3_alloc_skb(ip, &new_skb, &rxb, &d)) {
				/* Ouch, drop packet and just recycle packet
				 * to keep the ring filled.
				 */
				dev->stats.rx_dropped++;
				new_skb = skb;
				d = rxr[rx_entry];
				goto next;
			}

			if (likely(dev->features & NETIF_F_RXCSUM))
				ioc3_tcpudp_checksum(skb,
						     w0 & ERXBUF_IPCKSUM_MASK,
						     len);

			dma_unmap_single(ip->dma_dev, rxr[rx_entry],
					 RX_BUF_SIZE, DMA_FROM_DEVICE);

			netif_rx(skb);

			ip->rx_skbs[rx_entry] = NULL;	/* Poison  */

			dev->stats.rx_packets++;		/* Statistics */
			dev->stats.rx_bytes += len;
		} else {
			/* The frame is invalid and the skb never
			 * reached the network layer so we can just
			 * recycle it.
			 */
			new_skb = skb;
			d = rxr[rx_entry];
			dev->stats.rx_errors++;
		}
		if (err & ERXBUF_CRCERR)	/* Statistics */
			dev->stats.rx_crc_errors++;
		if (err & ERXBUF_FRAMERR)
			dev->stats.rx_frame_errors++;

next:
		ip->rx_skbs[n_entry] = new_skb;
		rxr[n_entry] = cpu_to_be64(ioc3_map(d, PCI64_ATTR_BAR));
		rxb->w0 = 0;				/* Clear valid flag */
		n_entry = (n_entry + 1) & RX_RING_MASK;	/* Update erpir */

		/* Now go on to the next ring entry.  */
		rx_entry = (rx_entry + 1) & RX_RING_MASK;
		skb = ip->rx_skbs[rx_entry];
		rxb = (struct ioc3_erxbuf *)(skb->data - RX_OFFSET);
		w0 = be32_to_cpu(rxb->w0);
	}
	writel((n_entry << 3) | ERPIR_ARM, &ip->regs->erpir);
	ip->rx_pi = n_entry;
	ip->rx_ci = rx_entry;
}