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
typedef  int u32 ;
struct cx88_core {int pci_irqmask; } ;
struct cx8802_dev {struct cx88_core* core; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int MAX_IRQ_LOOP ; 
 int /*<<< orphan*/  MO_PCI_INTMSK ; 
 int /*<<< orphan*/  MO_PCI_INTSTAT ; 
 int PCI_INT_TSINT ; 
 int /*<<< orphan*/  cx8802_mpeg_irq (struct cx8802_dev*) ; 
 int /*<<< orphan*/  cx88_core_irq (struct cx88_core*,int) ; 
 int cx_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dprintk (int,char*,...) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static irqreturn_t cx8802_irq(int irq, void *dev_id)
{
	struct cx8802_dev *dev = dev_id;
	struct cx88_core *core = dev->core;
	u32 status;
	int loop, handled = 0;

	for (loop = 0; loop < MAX_IRQ_LOOP; loop++) {
		status = cx_read(MO_PCI_INTSTAT) &
			(core->pci_irqmask | PCI_INT_TSINT);
		if (status == 0)
			goto out;
		dprintk(1, "cx8802_irq\n");
		dprintk(1, "    loop: %d/%d\n", loop, MAX_IRQ_LOOP);
		dprintk(1, "    status: %d\n", status);
		handled = 1;
		cx_write(MO_PCI_INTSTAT, status);

		if (status & core->pci_irqmask)
			cx88_core_irq(core, status);
		if (status & PCI_INT_TSINT)
			cx8802_mpeg_irq(dev);
	}
	if (loop == MAX_IRQ_LOOP) {
		dprintk(0, "clearing mask\n");
		pr_warn("irq loop -- clearing mask\n");
		cx_write(MO_PCI_INTMSK, 0);
	}

 out:
	return IRQ_RETVAL(handled);
}