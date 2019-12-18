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
typedef  int /*<<< orphan*/  u_long ;
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  irq; int /*<<< orphan*/  base_addr; } ;
struct TYPE_2__ {scalar_t__ lock; int /*<<< orphan*/  queue; } ;
struct de4x5_private {int irq_mask; int /*<<< orphan*/  lock; scalar_t__ interrupt; TYPE_1__ cache; scalar_t__ tx_enable; } ;
typedef  int s32 ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  DE4X5_STS ; 
 int /*<<< orphan*/  DISABLE_IRQs ; 
 int /*<<< orphan*/  ENABLE_IRQs ; 
 int IMR_LFM ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_RETVAL (unsigned int) ; 
 int /*<<< orphan*/  MASK_INTERRUPTS ; 
 int /*<<< orphan*/  STOP_DE4X5 ; 
 int STS_LNF ; 
 int STS_RI ; 
 int STS_RU ; 
 int STS_SE ; 
 int STS_TI ; 
 int STS_TU ; 
 int STS_UNF ; 
 scalar_t__ UNMASK_INTERRUPTS ; 
 int /*<<< orphan*/  de4x5_get_cache (struct net_device*) ; 
 int /*<<< orphan*/  de4x5_queue_pkt (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  de4x5_rx (struct net_device*) ; 
 int /*<<< orphan*/  de4x5_tx (struct net_device*) ; 
 int /*<<< orphan*/  de4x5_txur (struct net_device*) ; 
 int inl (int /*<<< orphan*/ ) ; 
 struct de4x5_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  outl (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static irqreturn_t
de4x5_interrupt(int irq, void *dev_id)
{
    struct net_device *dev = dev_id;
    struct de4x5_private *lp;
    s32 imr, omr, sts, limit;
    u_long iobase;
    unsigned int handled = 0;

    lp = netdev_priv(dev);
    spin_lock(&lp->lock);
    iobase = dev->base_addr;

    DISABLE_IRQs;                        /* Ensure non re-entrancy */

    if (test_and_set_bit(MASK_INTERRUPTS, (void*) &lp->interrupt))
	printk("%s: Re-entering the interrupt handler.\n", dev->name);

    synchronize_irq(dev->irq);

    for (limit=0; limit<8; limit++) {
	sts = inl(DE4X5_STS);            /* Read IRQ status */
	outl(sts, DE4X5_STS);            /* Reset the board interrupts */

	if (!(sts & lp->irq_mask)) break;/* All done */
	handled = 1;

	if (sts & (STS_RI | STS_RU))     /* Rx interrupt (packet[s] arrived) */
	  de4x5_rx(dev);

	if (sts & (STS_TI | STS_TU))     /* Tx interrupt (packet sent) */
	  de4x5_tx(dev);

	if (sts & STS_LNF) {             /* TP Link has failed */
	    lp->irq_mask &= ~IMR_LFM;
	}

	if (sts & STS_UNF) {             /* Transmit underrun */
	    de4x5_txur(dev);
	}

	if (sts & STS_SE) {              /* Bus Error */
	    STOP_DE4X5;
	    printk("%s: Fatal bus error occurred, sts=%#8x, device stopped.\n",
		   dev->name, sts);
	    spin_unlock(&lp->lock);
	    return IRQ_HANDLED;
	}
    }

    /* Load the TX ring with any locally stored packets */
    if (!test_and_set_bit(0, (void *)&lp->cache.lock)) {
	while (!skb_queue_empty(&lp->cache.queue) && !netif_queue_stopped(dev) && lp->tx_enable) {
	    de4x5_queue_pkt(de4x5_get_cache(dev), dev);
	}
	lp->cache.lock = 0;
    }

    lp->interrupt = UNMASK_INTERRUPTS;
    ENABLE_IRQs;
    spin_unlock(&lp->lock);

    return IRQ_RETVAL(handled);
}