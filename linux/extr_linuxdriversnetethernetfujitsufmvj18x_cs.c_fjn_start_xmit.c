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
struct sk_buff {short len; unsigned char* data; } ;
struct TYPE_2__ {short tx_bytes; } ;
struct net_device {unsigned int base_addr; TYPE_1__ stats; } ;
struct local_info {int tx_queue; int tx_queue_len; int tx_started; int sent; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 scalar_t__ DATAPORT ; 
 int DO_TX ; 
 int D_RX_INTR ; 
 int D_TX_INTR ; 
 short ETH_FRAME_LEN ; 
 short ETH_ZLEN ; 
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 scalar_t__ RX_INTR ; 
 scalar_t__ TX_INTR ; 
 scalar_t__ TX_START ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,unsigned long) ; 
 int /*<<< orphan*/  netdev_notice (struct net_device*,char*,short) ; 
 struct local_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  outsw (scalar_t__,unsigned char*,short) ; 
 int /*<<< orphan*/  outw (short,scalar_t__) ; 
 scalar_t__ skb_padto (struct sk_buff*,short) ; 
 scalar_t__ sram_config ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static netdev_tx_t fjn_start_xmit(struct sk_buff *skb,
					struct net_device *dev)
{
    struct local_info *lp = netdev_priv(dev);
    unsigned int ioaddr = dev->base_addr;
    short length = skb->len;
    
    if (length < ETH_ZLEN)
    {
    	if (skb_padto(skb, ETH_ZLEN))
    		return NETDEV_TX_OK;
    	length = ETH_ZLEN;
    }

    netif_stop_queue(dev);

    {
	unsigned char *buf = skb->data;

	if (length > ETH_FRAME_LEN) {
	    netdev_notice(dev, "Attempting to send a large packet (%d bytes)\n",
			  length);
	    return NETDEV_TX_BUSY;
	}

	netdev_dbg(dev, "Transmitting a packet of length %lu\n",
		   (unsigned long)skb->len);
	dev->stats.tx_bytes += skb->len;

	/* Disable both interrupts. */
	outw(0x0000, ioaddr + TX_INTR);

	/* wait for a while */
	udelay(1);

	outw(length, ioaddr + DATAPORT);
	outsw(ioaddr + DATAPORT, buf, (length + 1) >> 1);

	lp->tx_queue++;
	lp->tx_queue_len += ((length+3) & ~1);

	if (lp->tx_started == 0) {
	    /* If the Tx is idle, always trigger a transmit. */
	    outb(DO_TX | lp->tx_queue, ioaddr + TX_START);
	    lp->sent = lp->tx_queue ;
	    lp->tx_queue = 0;
	    lp->tx_queue_len = 0;
	    lp->tx_started = 1;
	    netif_start_queue(dev);
	} else {
	    if( sram_config == 0 ) {
		if (lp->tx_queue_len < (4096 - (ETH_FRAME_LEN +2)) )
		    /* Yes, there is room for one more packet. */
		    netif_start_queue(dev);
	    } else {
		if (lp->tx_queue_len < (8192 - (ETH_FRAME_LEN +2)) && 
						lp->tx_queue < 127 )
		    /* Yes, there is room for one more packet. */
		    netif_start_queue(dev);
	    }
	}

	/* Re-enable interrupts */
	outb(D_TX_INTR, ioaddr + TX_INTR);
	outb(D_RX_INTR, ioaddr + RX_INTR);
    }
    dev_kfree_skb (skb);

    return NETDEV_TX_OK;
}