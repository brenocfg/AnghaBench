#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u_int ;
struct net_device {int base_addr; int /*<<< orphan*/  name; } ;
struct hp100_private {int mode; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int HP100_MISC_ERROR ; 
 int HP100_RX_ERROR ; 
 int HP100_RX_PACKET ; 
 int HP100_RX_PDA_ZERO ; 
 int HP100_RX_PDL_FILL_COMPL ; 
 int HP100_TX_COMPLETE ; 
 int HP100_TX_ERROR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  IRQ_STATUS ; 
 int /*<<< orphan*/  RX_PDL ; 
 int /*<<< orphan*/  RX_PKT_CNT ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  TX_PDL ; 
 int /*<<< orphan*/  TX_PKT_CNT ; 
 int /*<<< orphan*/  hp100_clean_txring (struct net_device*) ; 
 int /*<<< orphan*/  hp100_inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hp100_ints_off () ; 
 int /*<<< orphan*/  hp100_ints_on () ; 
 int hp100_inw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hp100_misc_interrupt (struct net_device*) ; 
 int /*<<< orphan*/  hp100_outw (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hp100_rx (struct net_device*) ; 
 int /*<<< orphan*/  hp100_rx_bm (struct net_device*) ; 
 int /*<<< orphan*/  hp100_rxfill (struct net_device*) ; 
 int /*<<< orphan*/  hp100_update_stats (struct net_device*) ; 
 struct hp100_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t hp100_interrupt(int irq, void *dev_id)
{
	struct net_device *dev = (struct net_device *) dev_id;
	struct hp100_private *lp = netdev_priv(dev);

	int ioaddr;
	u_int val;

	if (dev == NULL)
		return IRQ_NONE;
	ioaddr = dev->base_addr;

	spin_lock(&lp->lock);

	hp100_ints_off();

#ifdef HP100_DEBUG_B
	hp100_outw(0x4219, TRACE);
#endif

	/*  hp100_page( PERFORMANCE ); */
	val = hp100_inw(IRQ_STATUS);
#ifdef HP100_DEBUG_IRQ
	printk("hp100: %s: mode=%x,IRQ_STAT=0x%.4x,RXPKTCNT=0x%.2x RXPDL=0x%.2x TXPKTCNT=0x%.2x TXPDL=0x%.2x\n",
			     dev->name, lp->mode, (u_int) val, hp100_inb(RX_PKT_CNT),
			     hp100_inb(RX_PDL), hp100_inb(TX_PKT_CNT), hp100_inb(TX_PDL));
#endif

	if (val == 0) {		/* might be a shared interrupt */
		spin_unlock(&lp->lock);
		hp100_ints_on();
		return IRQ_NONE;
	}
	/* We're only interested in those interrupts we really enabled. */
	/* val &= hp100_inw( IRQ_MASK ); */

	/*
	 * RX_PDL_FILL_COMPL is set whenever a RX_PDL has been executed. A RX_PDL
	 * is considered executed whenever the RX_PDL data structure is no longer
	 * needed.
	 */
	if (val & HP100_RX_PDL_FILL_COMPL) {
		if (lp->mode == 1)
			hp100_rx_bm(dev);
		else {
			printk("hp100: %s: rx_pdl_fill_compl interrupt although not busmaster?\n", dev->name);
		}
	}

	/*
	 * The RX_PACKET interrupt is set, when the receive packet counter is
	 * non zero. We use this interrupt for receiving in slave mode. In
	 * busmaster mode, we use it to make sure we did not miss any rx_pdl_fill
	 * interrupts. If rx_pdl_fill_compl is not set and rx_packet is set, then
	 * we somehow have missed a rx_pdl_fill_compl interrupt.
	 */

	if (val & HP100_RX_PACKET) {	/* Receive Packet Counter is non zero */
		if (lp->mode != 1)	/* non busmaster */
			hp100_rx(dev);
		else if (!(val & HP100_RX_PDL_FILL_COMPL)) {
			/* Shouldn't happen - maybe we missed a RX_PDL_FILL Interrupt?  */
			hp100_rx_bm(dev);
		}
	}

	/*
	 * Ack. that we have noticed the interrupt and thereby allow next one.
	 * Note that this is now done after the slave rx function, since first
	 * acknowledging and then setting ADV_NXT_PKT caused an extra interrupt
	 * on the J2573.
	 */
	hp100_outw(val, IRQ_STATUS);

	/*
	 * RX_ERROR is set when a packet is dropped due to no memory resources on
	 * the card or when a RCV_ERR occurs.
	 * TX_ERROR is set when a TX_ABORT condition occurs in the MAC->exists
	 * only in the 802.3 MAC and happens when 16 collisions occur during a TX
	 */
	if (val & (HP100_TX_ERROR | HP100_RX_ERROR)) {
#ifdef HP100_DEBUG_IRQ
		printk("hp100: %s: TX/RX Error IRQ\n", dev->name);
#endif
		hp100_update_stats(dev);
		if (lp->mode == 1) {
			hp100_rxfill(dev);
			hp100_clean_txring(dev);
		}
	}

	/*
	 * RX_PDA_ZERO is set when the PDA count goes from non-zero to zero.
	 */
	if ((lp->mode == 1) && (val & (HP100_RX_PDA_ZERO)))
		hp100_rxfill(dev);

	/*
	 * HP100_TX_COMPLETE interrupt occurs when packet transmitted on wire
	 * is completed
	 */
	if ((lp->mode == 1) && (val & (HP100_TX_COMPLETE)))
		hp100_clean_txring(dev);

	/*
	 * MISC_ERROR is set when either the LAN link goes down or a detected
	 * bus error occurs.
	 */
	if (val & HP100_MISC_ERROR) {	/* New for J2585B */
#ifdef HP100_DEBUG_IRQ
		printk
		    ("hp100: %s: Misc. Error Interrupt - Check cabling.\n",
		     dev->name);
#endif
		if (lp->mode == 1) {
			hp100_clean_txring(dev);
			hp100_rxfill(dev);
		}
		hp100_misc_interrupt(dev);
	}

	spin_unlock(&lp->lock);
	hp100_ints_on();
	return IRQ_HANDLED;
}