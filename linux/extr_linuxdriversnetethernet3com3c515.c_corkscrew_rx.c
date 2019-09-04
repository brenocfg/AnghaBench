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
struct TYPE_2__ {short rx_bytes; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_over_errors; int /*<<< orphan*/  rx_errors; } ;
struct net_device {int base_addr; short name; TYPE_1__ stats; } ;

/* Variables and functions */
 short CmdInProgress ; 
 scalar_t__ EL3_CMD ; 
 scalar_t__ EL3_STATUS ; 
 scalar_t__ RX_FIFO ; 
 int /*<<< orphan*/  RxDiscard ; 
 scalar_t__ RxErrors ; 
 scalar_t__ RxStatus ; 
 int corkscrew_debug ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 unsigned char inb (scalar_t__) ; 
 int /*<<< orphan*/  insl (scalar_t__,int /*<<< orphan*/ ,short) ; 
 short inw (scalar_t__) ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,short) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,short,...) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,short) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

__attribute__((used)) static int corkscrew_rx(struct net_device *dev)
{
	int ioaddr = dev->base_addr;
	int i;
	short rx_status;

	if (corkscrew_debug > 5)
		pr_debug("   In rx_packet(), status %4.4x, rx_status %4.4x.\n",
		     inw(ioaddr + EL3_STATUS), inw(ioaddr + RxStatus));
	while ((rx_status = inw(ioaddr + RxStatus)) > 0) {
		if (rx_status & 0x4000) {	/* Error, update stats. */
			unsigned char rx_error = inb(ioaddr + RxErrors);
			if (corkscrew_debug > 2)
				pr_debug(" Rx error: status %2.2x.\n",
				       rx_error);
			dev->stats.rx_errors++;
			if (rx_error & 0x01)
				dev->stats.rx_over_errors++;
			if (rx_error & 0x02)
				dev->stats.rx_length_errors++;
			if (rx_error & 0x04)
				dev->stats.rx_frame_errors++;
			if (rx_error & 0x08)
				dev->stats.rx_crc_errors++;
			if (rx_error & 0x10)
				dev->stats.rx_length_errors++;
		} else {
			/* The packet length: up to 4.5K!. */
			short pkt_len = rx_status & 0x1fff;
			struct sk_buff *skb;

			skb = netdev_alloc_skb(dev, pkt_len + 5 + 2);
			if (corkscrew_debug > 4)
				pr_debug("Receiving packet size %d status %4.4x.\n",
				     pkt_len, rx_status);
			if (skb != NULL) {
				skb_reserve(skb, 2);	/* Align IP on 16 byte boundaries */
				/* 'skb_put()' points to the start of sk_buff data area. */
				insl(ioaddr + RX_FIFO,
				     skb_put(skb, pkt_len),
				     (pkt_len + 3) >> 2);
				outw(RxDiscard, ioaddr + EL3_CMD);	/* Pop top Rx packet. */
				skb->protocol = eth_type_trans(skb, dev);
				netif_rx(skb);
				dev->stats.rx_packets++;
				dev->stats.rx_bytes += pkt_len;
				/* Wait a limited time to go to next packet. */
				for (i = 200; i >= 0; i--)
					if (! (inw(ioaddr + EL3_STATUS) & CmdInProgress))
						break;
				continue;
			} else if (corkscrew_debug)
				pr_debug("%s: Couldn't allocate a sk_buff of size %d.\n", dev->name, pkt_len);
		}
		outw(RxDiscard, ioaddr + EL3_CMD);
		dev->stats.rx_dropped++;
		/* Wait a limited time to skip this packet. */
		for (i = 200; i >= 0; i--)
			if (!(inw(ioaddr + EL3_STATUS) & CmdInProgress))
				break;
	}
	return 0;
}