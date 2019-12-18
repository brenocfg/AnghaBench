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
struct smc_private {int /*<<< orphan*/  last_rx; } ;
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct TYPE_2__ {int rx_bytes; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  multicast; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; } ;
struct net_device {unsigned int base_addr; TYPE_1__ stats; } ;

/* Variables and functions */
 scalar_t__ DATA_1 ; 
 scalar_t__ FIFO_PORTS ; 
 int FP_RXEMPTY ; 
 int MC_RELEASE ; 
 scalar_t__ MMU_CMD ; 
 scalar_t__ POINTER ; 
 int PTR_AUTOINC ; 
 int PTR_RCV ; 
 int PTR_READ ; 
 int RS_ALGNERR ; 
 int RS_BADCRC ; 
 int RS_ERRORS ; 
 int RS_MULTICAST ; 
 int RS_ODDFRAME ; 
 int RS_TOOLONG ; 
 int RS_TOOSHORT ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  insw (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int inw (scalar_t__) ; 
 int /*<<< orphan*/  jiffies ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,int) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,...) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct smc_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

__attribute__((used)) static void smc_rx(struct net_device *dev)
{
    unsigned int ioaddr = dev->base_addr;
    int rx_status;
    int packet_length;	/* Caution: not frame length, rather words
			   to transfer from the chip. */

    /* Assertion: we are in Window 2. */

    if (inw(ioaddr + FIFO_PORTS) & FP_RXEMPTY) {
	netdev_err(dev, "smc_rx() with nothing on Rx FIFO\n");
	return;
    }

    /*  Reset the read pointer, and read the status and packet length. */
    outw(PTR_READ | PTR_RCV | PTR_AUTOINC, ioaddr + POINTER);
    rx_status = inw(ioaddr + DATA_1);
    packet_length = inw(ioaddr + DATA_1) & 0x07ff;

    netdev_dbg(dev, "Receive status %4.4x length %d.\n",
	       rx_status, packet_length);

    if (!(rx_status & RS_ERRORS)) {
	/* do stuff to make a new packet */
	struct sk_buff *skb;
	struct smc_private *smc = netdev_priv(dev);
	
	/* Note: packet_length adds 5 or 6 extra bytes here! */
	skb = netdev_alloc_skb(dev, packet_length+2);
	
	if (skb == NULL) {
	    netdev_dbg(dev, "Low memory, packet dropped.\n");
	    dev->stats.rx_dropped++;
	    outw(MC_RELEASE, ioaddr + MMU_CMD);
	    return;
	}
	
	packet_length -= (rx_status & RS_ODDFRAME ? 5 : 6);
	skb_reserve(skb, 2);
	insw(ioaddr+DATA_1, skb_put(skb, packet_length),
	     (packet_length+1)>>1);
	skb->protocol = eth_type_trans(skb, dev);
	
	netif_rx(skb);
	smc->last_rx = jiffies;
	dev->stats.rx_packets++;
	dev->stats.rx_bytes += packet_length;
	if (rx_status & RS_MULTICAST)
	    dev->stats.multicast++;
    } else {
	/* error ... */
	dev->stats.rx_errors++;
	
	if (rx_status & RS_ALGNERR)  dev->stats.rx_frame_errors++;
	if (rx_status & (RS_TOOSHORT | RS_TOOLONG))
	    dev->stats.rx_length_errors++;
	if (rx_status & RS_BADCRC)	dev->stats.rx_crc_errors++;
    }
    /* Let the MMU free the memory of this packet. */
    outw(MC_RELEASE, ioaddr + MMU_CMD);
}