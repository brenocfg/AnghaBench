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
typedef  int u_short ;
struct sk_buff {int /*<<< orphan*/ * data; int /*<<< orphan*/  protocol; } ;
struct TYPE_2__ {int rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_over_errors; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_length_errors; } ;
struct net_device {unsigned int base_addr; TYPE_1__ stats; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ DATAPORT ; 
 int F_ALG_ERR ; 
 int F_BUF_EMP ; 
 int F_CRC_ERR ; 
 int F_LEN_ERR ; 
 int F_OVR_FLO ; 
 int /*<<< orphan*/  F_SKP_PKT ; 
 scalar_t__ RX_MODE ; 
 scalar_t__ RX_SKIP ; 
 scalar_t__ RX_STATUS ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  insw (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int inw (scalar_t__) ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,int) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int,int) ; 
 int /*<<< orphan*/  netdev_notice (struct net_device*,char*,int) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

__attribute__((used)) static void fjn_rx(struct net_device *dev)
{
    unsigned int ioaddr = dev->base_addr;
    int boguscount = 10;	/* 5 -> 10: by agy 19940922 */

    pr_debug("%s: in rx_packet(), rx_status %02x.\n",
	  dev->name, inb(ioaddr + RX_STATUS));

    while ((inb(ioaddr + RX_MODE) & F_BUF_EMP) == 0) {
	u_short status = inw(ioaddr + DATAPORT);

	netdev_dbg(dev, "Rxing packet mode %02x status %04x.\n",
		   inb(ioaddr + RX_MODE), status);
#ifndef final_version
	if (status == 0) {
	    outb(F_SKP_PKT, ioaddr + RX_SKIP);
	    break;
	}
#endif
	if ((status & 0xF0) != 0x20) {	/* There was an error. */
	    dev->stats.rx_errors++;
	    if (status & F_LEN_ERR) dev->stats.rx_length_errors++;
	    if (status & F_ALG_ERR) dev->stats.rx_frame_errors++;
	    if (status & F_CRC_ERR) dev->stats.rx_crc_errors++;
	    if (status & F_OVR_FLO) dev->stats.rx_over_errors++;
	} else {
	    u_short pkt_len = inw(ioaddr + DATAPORT);
	    /* Malloc up new buffer. */
	    struct sk_buff *skb;

	    if (pkt_len > 1550) {
		netdev_notice(dev, "The FMV-18x claimed a very large packet, size %d\n",
			      pkt_len);
		outb(F_SKP_PKT, ioaddr + RX_SKIP);
		dev->stats.rx_errors++;
		break;
	    }
	    skb = netdev_alloc_skb(dev, pkt_len + 2);
	    if (skb == NULL) {
		outb(F_SKP_PKT, ioaddr + RX_SKIP);
		dev->stats.rx_dropped++;
		break;
	    }

	    skb_reserve(skb, 2);
	    insw(ioaddr + DATAPORT, skb_put(skb, pkt_len),
		 (pkt_len + 1) >> 1);
	    skb->protocol = eth_type_trans(skb, dev);

	    {
		int i;
		pr_debug("%s: Rxed packet of length %d: ",
			dev->name, pkt_len);
		for (i = 0; i < 14; i++)
			pr_debug(" %02x", skb->data[i]);
		pr_debug(".\n");
	    }

	    netif_rx(skb);
	    dev->stats.rx_packets++;
	    dev->stats.rx_bytes += pkt_len;
	}
	if (--boguscount <= 0)
	    break;
    }

    /* If any worth-while packets have been received, dev_rint()
	   has done a netif_wake_queue() for us and will work on them
	   when we get to the bottom-half routine. */
/*
    if (lp->cardtype != TDK) {
	int i;
	for (i = 0; i < 20; i++) {
	    if ((inb(ioaddr + RX_MODE) & F_BUF_EMP) == F_BUF_EMP)
		break;
	    (void)inw(ioaddr + DATAPORT);  /+ dummy status read +/
	    outb(F_SKP_PKT, ioaddr + RX_SKIP);
	}

	if (i > 0)
	    pr_debug("%s: Exint Rx packet with mode %02x after "
		  "%d ticks.\n", dev->name, inb(ioaddr + RX_MODE), i);
    }
*/
}