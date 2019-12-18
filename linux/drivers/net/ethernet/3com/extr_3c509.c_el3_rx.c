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
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct TYPE_2__ {short rx_bytes; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  rx_over_errors; int /*<<< orphan*/  rx_errors; } ;
struct net_device {int base_addr; int /*<<< orphan*/  name; TYPE_1__ stats; } ;

/* Variables and functions */
 scalar_t__ EL3_CMD ; 
 scalar_t__ EL3_STATUS ; 
 scalar_t__ RX_FIFO ; 
 scalar_t__ RX_STATUS ; 
 int /*<<< orphan*/  RxDiscard ; 
 int el3_debug ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  insl (scalar_t__,int /*<<< orphan*/ ,short) ; 
 int inw (scalar_t__) ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,short) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,int,...) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,short) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

__attribute__((used)) static int
el3_rx(struct net_device *dev)
{
	int ioaddr = dev->base_addr;
	short rx_status;

	if (el3_debug > 5)
		pr_debug("   In rx_packet(), status %4.4x, rx_status %4.4x.\n",
			   inw(ioaddr+EL3_STATUS), inw(ioaddr+RX_STATUS));
	while ((rx_status = inw(ioaddr + RX_STATUS)) > 0) {
		if (rx_status & 0x4000) { /* Error, update stats. */
			short error = rx_status & 0x3800;

			outw(RxDiscard, ioaddr + EL3_CMD);
			dev->stats.rx_errors++;
			switch (error) {
			case 0x0000:		dev->stats.rx_over_errors++; break;
			case 0x0800:		dev->stats.rx_length_errors++; break;
			case 0x1000:		dev->stats.rx_frame_errors++; break;
			case 0x1800:		dev->stats.rx_length_errors++; break;
			case 0x2000:		dev->stats.rx_frame_errors++; break;
			case 0x2800:		dev->stats.rx_crc_errors++; break;
			}
		} else {
			short pkt_len = rx_status & 0x7ff;
			struct sk_buff *skb;

			skb = netdev_alloc_skb(dev, pkt_len + 5);
			if (el3_debug > 4)
				pr_debug("Receiving packet size %d status %4.4x.\n",
					   pkt_len, rx_status);
			if (skb != NULL) {
				skb_reserve(skb, 2);     /* Align IP on 16 byte */

				/* 'skb->data' points to the start of sk_buff data area. */
				insl(ioaddr + RX_FIFO, skb_put(skb,pkt_len),
					 (pkt_len + 3) >> 2);

				outw(RxDiscard, ioaddr + EL3_CMD); /* Pop top Rx packet. */
				skb->protocol = eth_type_trans(skb,dev);
				netif_rx(skb);
				dev->stats.rx_bytes += pkt_len;
				dev->stats.rx_packets++;
				continue;
			}
			outw(RxDiscard, ioaddr + EL3_CMD);
			dev->stats.rx_dropped++;
			if (el3_debug)
				pr_debug("%s: Couldn't allocate a sk_buff of size %d.\n",
					   dev->name, pkt_len);
		}
		inw(ioaddr + EL3_STATUS); 				/* Delay. */
		while (inw(ioaddr + EL3_STATUS) & 0x1000)
			pr_debug("	Waiting for 3c509 to discard packet, status %x.\n",
				   inw(ioaddr + EL3_STATUS) );
	}

	return 0;
}