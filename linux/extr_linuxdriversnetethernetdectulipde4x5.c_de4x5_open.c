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
typedef  int /*<<< orphan*/  u_long ;
struct net_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  base_addr; } ;
struct de4x5_private {int rxRingSize; int /*<<< orphan*/  interrupt; int /*<<< orphan*/  state; int /*<<< orphan*/  adapter_name; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  CLOSED ; 
 int /*<<< orphan*/  DE4X5_BMR ; 
 int /*<<< orphan*/  DE4X5_IMR ; 
 int /*<<< orphan*/  DE4X5_OMR ; 
 int /*<<< orphan*/  DE4X5_SICR ; 
 int /*<<< orphan*/  DE4X5_SIGR ; 
 int /*<<< orphan*/  DE4X5_SISR ; 
 int /*<<< orphan*/  DE4X5_STRR ; 
 int /*<<< orphan*/  DE4X5_STS ; 
 int DEBUG_OPEN ; 
 int EAGAIN ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  OPEN ; 
 int /*<<< orphan*/  SLEEP ; 
 int /*<<< orphan*/  START_DE4X5 ; 
 int /*<<< orphan*/  UNMASK_INTERRUPTS ; 
 int /*<<< orphan*/  WAKEUP ; 
 int /*<<< orphan*/ * de4x5_alloc_rx_buff (struct net_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  de4x5_dbg_open (struct net_device*) ; 
 int de4x5_debug ; 
 int /*<<< orphan*/  de4x5_free_rx_buffs (struct net_device*) ; 
 int /*<<< orphan*/  de4x5_free_tx_buffs (struct net_device*) ; 
 int de4x5_init (struct net_device*) ; 
 int /*<<< orphan*/  de4x5_interrupt ; 
 int /*<<< orphan*/  de4x5_setup_intr (struct net_device*) ; 
 int /*<<< orphan*/  disable_ast (struct net_device*) ; 
 int /*<<< orphan*/  inl (int /*<<< orphan*/ ) ; 
 struct de4x5_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_trans_update (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 scalar_t__ request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yawn (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
de4x5_open(struct net_device *dev)
{
    struct de4x5_private *lp = netdev_priv(dev);
    u_long iobase = dev->base_addr;
    int i, status = 0;
    s32 omr;

    /* Allocate the RX buffers */
    for (i=0; i<lp->rxRingSize; i++) {
	if (de4x5_alloc_rx_buff(dev, i, 0) == NULL) {
	    de4x5_free_rx_buffs(dev);
	    return -EAGAIN;
	}
    }

    /*
    ** Wake up the adapter
    */
    yawn(dev, WAKEUP);

    /*
    ** Re-initialize the DE4X5...
    */
    status = de4x5_init(dev);
    spin_lock_init(&lp->lock);
    lp->state = OPEN;
    de4x5_dbg_open(dev);

    if (request_irq(dev->irq, de4x5_interrupt, IRQF_SHARED,
		                                     lp->adapter_name, dev)) {
	printk("de4x5_open(): Requested IRQ%d is busy - attempting FAST/SHARE...", dev->irq);
	if (request_irq(dev->irq, de4x5_interrupt, IRQF_SHARED,
			                             lp->adapter_name, dev)) {
	    printk("\n              Cannot get IRQ- reconfigure your hardware.\n");
	    disable_ast(dev);
	    de4x5_free_rx_buffs(dev);
	    de4x5_free_tx_buffs(dev);
	    yawn(dev, SLEEP);
	    lp->state = CLOSED;
	    return -EAGAIN;
	} else {
	    printk("\n              Succeeded, but you should reconfigure your hardware to avoid this.\n");
	    printk("WARNING: there may be IRQ related problems in heavily loaded systems.\n");
	}
    }

    lp->interrupt = UNMASK_INTERRUPTS;
    netif_trans_update(dev); /* prevent tx timeout */

    START_DE4X5;

    de4x5_setup_intr(dev);

    if (de4x5_debug & DEBUG_OPEN) {
	printk("\tsts:  0x%08x\n", inl(DE4X5_STS));
	printk("\tbmr:  0x%08x\n", inl(DE4X5_BMR));
	printk("\timr:  0x%08x\n", inl(DE4X5_IMR));
	printk("\tomr:  0x%08x\n", inl(DE4X5_OMR));
	printk("\tsisr: 0x%08x\n", inl(DE4X5_SISR));
	printk("\tsicr: 0x%08x\n", inl(DE4X5_SICR));
	printk("\tstrr: 0x%08x\n", inl(DE4X5_STRR));
	printk("\tsigr: 0x%08x\n", inl(DE4X5_SIGR));
    }

    return status;
}