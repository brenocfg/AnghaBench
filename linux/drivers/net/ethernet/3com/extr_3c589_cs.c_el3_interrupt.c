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
typedef  int u16 ;
struct net_device {unsigned int base_addr; } ;
struct el3_private {int /*<<< orphan*/  lock; int /*<<< orphan*/  last_irq; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  int __u16 ;

/* Variables and functions */
 int AckIntr ; 
 int AdapterFailure ; 
 int /*<<< orphan*/  EL3WINDOW (int) ; 
 scalar_t__ EL3_CMD ; 
 unsigned int EL3_STATUS ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int IntLatch ; 
 int IntReq ; 
 int RxComplete ; 
 int RxEarly ; 
 int RxEnable ; 
 int /*<<< orphan*/  RxReset ; 
 int StatsFull ; 
 int TxAvailable ; 
 int TxComplete ; 
 int TxEnable ; 
 int /*<<< orphan*/  TxReset ; 
 int /*<<< orphan*/  el3_rx (struct net_device*) ; 
 int inw (unsigned int) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,...) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 
 struct el3_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*,int) ; 
 int /*<<< orphan*/  netif_device_present (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int /*<<< orphan*/  pop_tx_status (struct net_device*) ; 
 int /*<<< orphan*/  set_rx_mode (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tc589_wait_for_completion (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_stats (struct net_device*) ; 

__attribute__((used)) static irqreturn_t el3_interrupt(int irq, void *dev_id)
{
	struct net_device *dev = (struct net_device *) dev_id;
	struct el3_private *lp = netdev_priv(dev);
	unsigned int ioaddr;
	__u16 status;
	int i = 0, handled = 1;

	if (!netif_device_present(dev))
		return IRQ_NONE;

	ioaddr = dev->base_addr;

	netdev_dbg(dev, "interrupt, status %4.4x.\n", inw(ioaddr + EL3_STATUS));

	spin_lock(&lp->lock);
	while ((status = inw(ioaddr + EL3_STATUS)) &
	(IntLatch | RxComplete | StatsFull)) {
		if ((status & 0xe000) != 0x2000) {
			netdev_dbg(dev, "interrupt from dead card\n");
			handled = 0;
			break;
		}
		if (status & RxComplete)
			el3_rx(dev);
		if (status & TxAvailable) {
			netdev_dbg(dev, "    TX room bit was handled.\n");
			/* There's room in the FIFO for a full-sized packet. */
			outw(AckIntr | TxAvailable, ioaddr + EL3_CMD);
			netif_wake_queue(dev);
		}
		if (status & TxComplete)
			pop_tx_status(dev);
		if (status & (AdapterFailure | RxEarly | StatsFull)) {
			/* Handle all uncommon interrupts. */
			if (status & StatsFull)		/* Empty statistics. */
				update_stats(dev);
			if (status & RxEarly) {
				/* Rx early is unused. */
				el3_rx(dev);
				outw(AckIntr | RxEarly, ioaddr + EL3_CMD);
			}
			if (status & AdapterFailure) {
				u16 fifo_diag;
				EL3WINDOW(4);
				fifo_diag = inw(ioaddr + 4);
				EL3WINDOW(1);
				netdev_warn(dev, "adapter failure, FIFO diagnostic register %04x.\n",
			    fifo_diag);
				if (fifo_diag & 0x0400) {
					/* Tx overrun */
					tc589_wait_for_completion(dev, TxReset);
					outw(TxEnable, ioaddr + EL3_CMD);
				}
				if (fifo_diag & 0x2000) {
					/* Rx underrun */
					tc589_wait_for_completion(dev, RxReset);
					set_rx_mode(dev);
					outw(RxEnable, ioaddr + EL3_CMD);
				}
				outw(AckIntr | AdapterFailure, ioaddr + EL3_CMD);
			}
		}
		if (++i > 10) {
			netdev_err(dev, "infinite loop in interrupt, status %4.4x.\n",
					status);
			/* Clear all interrupts */
			outw(AckIntr | 0xFF, ioaddr + EL3_CMD);
			break;
		}
		/* Acknowledge the IRQ. */
		outw(AckIntr | IntReq | IntLatch, ioaddr + EL3_CMD);
	}
	lp->last_irq = jiffies;
	spin_unlock(&lp->lock);
	netdev_dbg(dev, "exiting interrupt, status %4.4x.\n",
			inw(ioaddr + EL3_STATUS));
	return IRQ_RETVAL(handled);
}