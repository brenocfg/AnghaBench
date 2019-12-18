#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_4__ {scalar_t__ fpga_base_addr; } ;
struct TYPE_3__ {scalar_t__ plx9054_base_addr; } ;
struct net2272 {int /*<<< orphan*/  lock; TYPE_2__ rdk2; int /*<<< orphan*/ * ep; TYPE_1__ rdk1; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int CHANNEL_CLEAR_INTERRUPT ; 
 int CHANNEL_ENABLE ; 
 scalar_t__ DMACSR0 ; 
 int /*<<< orphan*/  DMAREQ ; 
 int DMA_CHANNEL_0_TEST ; 
 scalar_t__ INTCSR ; 
 int /*<<< orphan*/  IRQSTAT0 ; 
 int /*<<< orphan*/  IRQSTAT1 ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int LOCAL_INTERRUPT_TEST ; 
 int NET2272_PCI_IRQ ; 
 int PCI_INTERRUPT_ENABLE ; 
 scalar_t__ RDK2_IRQSTAT ; 
 int /*<<< orphan*/  net2272_handle_dma (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  net2272_handle_stat0_irqs (struct net2272*,int) ; 
 int /*<<< orphan*/  net2272_handle_stat1_irqs (struct net2272*,int) ; 
 int net2272_read (struct net2272*,int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t net2272_irq(int irq, void *_dev)
{
	struct net2272 *dev = _dev;
#if defined(PLX_PCI_RDK) || defined(PLX_PCI_RDK2)
	u32 intcsr;
#endif
#if defined(PLX_PCI_RDK)
	u8 dmareq;
#endif
	spin_lock(&dev->lock);
#if defined(PLX_PCI_RDK)
	intcsr = readl(dev->rdk1.plx9054_base_addr + INTCSR);

	if ((intcsr & LOCAL_INTERRUPT_TEST) == LOCAL_INTERRUPT_TEST) {
		writel(intcsr & ~(1 << PCI_INTERRUPT_ENABLE),
				dev->rdk1.plx9054_base_addr + INTCSR);
		net2272_handle_stat1_irqs(dev, net2272_read(dev, IRQSTAT1));
		net2272_handle_stat0_irqs(dev, net2272_read(dev, IRQSTAT0));
		intcsr = readl(dev->rdk1.plx9054_base_addr + INTCSR);
		writel(intcsr | (1 << PCI_INTERRUPT_ENABLE),
			dev->rdk1.plx9054_base_addr + INTCSR);
	}
	if ((intcsr & DMA_CHANNEL_0_TEST) == DMA_CHANNEL_0_TEST) {
		writeb((1 << CHANNEL_CLEAR_INTERRUPT | (0 << CHANNEL_ENABLE)),
				dev->rdk1.plx9054_base_addr + DMACSR0);

		dmareq = net2272_read(dev, DMAREQ);
		if (dmareq & 0x01)
			net2272_handle_dma(&dev->ep[2]);
		else
			net2272_handle_dma(&dev->ep[1]);
	}
#endif
#if defined(PLX_PCI_RDK2)
	/* see if PCI int for us by checking irqstat */
	intcsr = readl(dev->rdk2.fpga_base_addr + RDK2_IRQSTAT);
	if (!(intcsr & (1 << NET2272_PCI_IRQ))) {
		spin_unlock(&dev->lock);
		return IRQ_NONE;
	}
	/* check dma interrupts */
#endif
	/* Platform/devcice interrupt handler */
#if !defined(PLX_PCI_RDK)
	net2272_handle_stat1_irqs(dev, net2272_read(dev, IRQSTAT1));
	net2272_handle_stat0_irqs(dev, net2272_read(dev, IRQSTAT0));
#endif
	spin_unlock(&dev->lock);

	return IRQ_HANDLED;
}