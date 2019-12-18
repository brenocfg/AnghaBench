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
typedef  int ulong ;
typedef  int u_long ;
typedef  int u_char ;
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct TYPE_2__ {unsigned int rx_bytes; int tx_packets; int /*<<< orphan*/  tx_aborted_errors; int /*<<< orphan*/  rx_over_errors; int /*<<< orphan*/  rx_fifo_errors; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  multicast; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; } ;
struct net_device {unsigned int base_addr; unsigned int name; TYPE_1__ stats; } ;
struct local_info {scalar_t__ silicon; unsigned int last_ptr_value; scalar_t__ mohawk; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 unsigned int AlignErr ; 
 unsigned int CRCErr ; 
 unsigned int ClearRxOvrun ; 
 unsigned int EnableIntr ; 
 unsigned int FullPktRcvd ; 
 int GetByte (unsigned int) ; 
 unsigned int GetWord (int /*<<< orphan*/ ) ; 
 int HZ ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned int PhyPkt ; 
 unsigned int PktRxOk ; 
 unsigned int PktTooLong ; 
 unsigned int PktTxed ; 
 int /*<<< orphan*/  PutByte (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  PutWord (int /*<<< orphan*/ ,int) ; 
 unsigned int RestartTx ; 
 int /*<<< orphan*/  SelectPage (int) ; 
 int /*<<< orphan*/  XIRCREG0_DO ; 
 unsigned int XIRCREG0_PTR ; 
 int /*<<< orphan*/  XIRCREG0_RBC ; 
 unsigned int XIRCREG0_RSR ; 
 unsigned int XIRCREG40_RXST0 ; 
 unsigned int XIRCREG40_TXST0 ; 
 unsigned int XIRCREG40_TXST1 ; 
 int /*<<< orphan*/  XIRCREG5_RHSA0 ; 
 unsigned int XIRCREG_CR ; 
 unsigned int XIRCREG_EDP ; 
 unsigned int XIRCREG_ESR ; 
 unsigned int XIRCREG_ISR ; 
 unsigned int XIRCREG_PR ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int inl (unsigned int) ; 
 int /*<<< orphan*/  insw (unsigned int,int*,unsigned int) ; 
 int jiffies ; 
 unsigned int len ; 
 scalar_t__ lockup_hack ; 
 unsigned int maxrx_bytes ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,unsigned int) ; 
 struct local_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_present (struct net_device*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int* skb_put (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

__attribute__((used)) static irqreturn_t
xirc2ps_interrupt(int irq, void *dev_id)
{
    struct net_device *dev = (struct net_device *)dev_id;
    struct local_info *lp = netdev_priv(dev);
    unsigned int ioaddr;
    u_char saved_page;
    unsigned bytes_rcvd;
    unsigned int_status, eth_status, rx_status, tx_status;
    unsigned rsr, pktlen;
    ulong start_ticks = jiffies; /* fixme: jiffies rollover every 497 days
				  * is this something to worry about?
				  * -- on a laptop?
				  */

    if (!netif_device_present(dev))
	return IRQ_HANDLED;

    ioaddr = dev->base_addr;
    if (lp->mohawk) { /* must disable the interrupt */
	PutByte(XIRCREG_CR, 0);
    }

    pr_debug("%s: interrupt %d at %#x.\n", dev->name, irq, ioaddr);

    saved_page = GetByte(XIRCREG_PR);
    /* Read the ISR to see whats the cause for the interrupt.
     * This also clears the interrupt flags on CE2 cards
     */
    int_status = GetByte(XIRCREG_ISR);
    bytes_rcvd = 0;
  loop_entry:
    if (int_status == 0xff) { /* card may be ejected */
	pr_debug("%s: interrupt %d for dead card\n", dev->name, irq);
	goto leave;
    }
    eth_status = GetByte(XIRCREG_ESR);

    SelectPage(0x40);
    rx_status  = GetByte(XIRCREG40_RXST0);
    PutByte(XIRCREG40_RXST0, (~rx_status & 0xff));
    tx_status = GetByte(XIRCREG40_TXST0);
    tx_status |= GetByte(XIRCREG40_TXST1) << 8;
    PutByte(XIRCREG40_TXST0, 0);
    PutByte(XIRCREG40_TXST1, 0);

    pr_debug("%s: ISR=%#2.2x ESR=%#2.2x RSR=%#2.2x TSR=%#4.4x\n",
	  dev->name, int_status, eth_status, rx_status, tx_status);

    /***** receive section ******/
    SelectPage(0);
    while (eth_status & FullPktRcvd) {
	rsr = GetByte(XIRCREG0_RSR);
	if (bytes_rcvd > maxrx_bytes && (rsr & PktRxOk)) {
	    /* too many bytes received during this int, drop the rest of the
	     * packets */
	    dev->stats.rx_dropped++;
	    pr_debug("%s: RX drop, too much done\n", dev->name);
	} else if (rsr & PktRxOk) {
	    struct sk_buff *skb;

	    pktlen = GetWord(XIRCREG0_RBC);
	    bytes_rcvd += pktlen;

	    pr_debug("rsr=%#02x packet_length=%u\n", rsr, pktlen);

	    /* 1 extra so we can use insw */
	    skb = netdev_alloc_skb(dev, pktlen + 3);
	    if (!skb) {
		dev->stats.rx_dropped++;
	    } else { /* okay get the packet */
		skb_reserve(skb, 2);
		if (lp->silicon == 0 ) { /* work around a hardware bug */
		    unsigned rhsa; /* receive start address */

		    SelectPage(5);
		    rhsa = GetWord(XIRCREG5_RHSA0);
		    SelectPage(0);
		    rhsa += 3; /* skip control infos */
		    if (rhsa >= 0x8000)
			rhsa = 0;
		    if (rhsa + pktlen > 0x8000) {
			unsigned i;
			u_char *buf = skb_put(skb, pktlen);
			for (i=0; i < pktlen ; i++, rhsa++) {
			    buf[i] = GetByte(XIRCREG_EDP);
			    if (rhsa == 0x8000) {
				rhsa = 0;
				i--;
			    }
			}
		    } else {
			insw(ioaddr+XIRCREG_EDP,
				skb_put(skb, pktlen), (pktlen+1)>>1);
		    }
		}
	      #if 0
		else if (lp->mohawk) {
		    /* To use this 32 bit access we should use
		     * a manual optimized loop
		     * Also the words are swapped, we can get more
		     * performance by using 32 bit access and swapping
		     * the words in a register. Will need this for cardbus
		     *
		     * Note: don't forget to change the ALLOC_SKB to .. +3
		     */
		    unsigned i;
		    u_long *p = skb_put(skb, pktlen);
		    register u_long a;
		    unsigned int edpreg = ioaddr+XIRCREG_EDP-2;
		    for (i=0; i < len ; i += 4, p++) {
			a = inl(edpreg);
			__asm__("rorl $16,%0\n\t"
				:"=q" (a)
				: "0" (a));
			*p = a;
		    }
		}
	      #endif
		else {
		    insw(ioaddr+XIRCREG_EDP, skb_put(skb, pktlen),
			    (pktlen+1)>>1);
		}
		skb->protocol = eth_type_trans(skb, dev);
		netif_rx(skb);
		dev->stats.rx_packets++;
		dev->stats.rx_bytes += pktlen;
		if (!(rsr & PhyPkt))
		    dev->stats.multicast++;
	    }
	} else { /* bad packet */
	    pr_debug("rsr=%#02x\n", rsr);
	}
	if (rsr & PktTooLong) {
	    dev->stats.rx_frame_errors++;
	    pr_debug("%s: Packet too long\n", dev->name);
	}
	if (rsr & CRCErr) {
	    dev->stats.rx_crc_errors++;
	    pr_debug("%s: CRC error\n", dev->name);
	}
	if (rsr & AlignErr) {
	    dev->stats.rx_fifo_errors++; /* okay ? */
	    pr_debug("%s: Alignment error\n", dev->name);
	}

	/* clear the received/dropped/error packet */
	PutWord(XIRCREG0_DO, 0x8000); /* issue cmd: skip_rx_packet */

	/* get the new ethernet status */
	eth_status = GetByte(XIRCREG_ESR);
    }
    if (rx_status & 0x10) { /* Receive overrun */
	dev->stats.rx_over_errors++;
	PutByte(XIRCREG_CR, ClearRxOvrun);
	pr_debug("receive overrun cleared\n");
    }

    /***** transmit section ******/
    if (int_status & PktTxed) {
	unsigned n, nn;

	n = lp->last_ptr_value;
	nn = GetByte(XIRCREG0_PTR);
	lp->last_ptr_value = nn;
	if (nn < n) /* rollover */
	    dev->stats.tx_packets += 256 - n;
	else if (n == nn) { /* happens sometimes - don't know why */
	    pr_debug("PTR not changed?\n");
	} else
	    dev->stats.tx_packets += lp->last_ptr_value - n;
	netif_wake_queue(dev);
    }
    if (tx_status & 0x0002) {	/* Excessive collisions */
	pr_debug("tx restarted due to excessive collisions\n");
	PutByte(XIRCREG_CR, RestartTx);  /* restart transmitter process */
    }
    if (tx_status & 0x0040)
	dev->stats.tx_aborted_errors++;

    /* recalculate our work chunk so that we limit the duration of this
     * ISR to about 1/10 of a second.
     * Calculate only if we received a reasonable amount of bytes.
     */
    if (bytes_rcvd > 1000) {
	u_long duration = jiffies - start_ticks;

	if (duration >= HZ/10) { /* if more than about 1/10 second */
	    maxrx_bytes = (bytes_rcvd * (HZ/10)) / duration;
	    if (maxrx_bytes < 2000)
		maxrx_bytes = 2000;
	    else if (maxrx_bytes > 22000)
		maxrx_bytes = 22000;
	    pr_debug("set maxrx=%u (rcvd=%u ticks=%lu)\n",
		  maxrx_bytes, bytes_rcvd, duration);
	} else if (!duration && maxrx_bytes < 22000) {
	    /* now much faster */
	    maxrx_bytes += 2000;
	    if (maxrx_bytes > 22000)
		maxrx_bytes = 22000;
	    pr_debug("set maxrx=%u\n", maxrx_bytes);
	}
    }

  leave:
    if (lockup_hack) {
	if (int_status != 0xff && (int_status = GetByte(XIRCREG_ISR)) != 0)
	    goto loop_entry;
    }
    SelectPage(saved_page);
    PutByte(XIRCREG_CR, EnableIntr);  /* re-enable interrupts */
    /* Instead of dropping packets during a receive, we could
     * force an interrupt with this command:
     *	  PutByte(XIRCREG_CR, EnableIntr|ForceIntr);
     */
    return IRQ_HANDLED;
}