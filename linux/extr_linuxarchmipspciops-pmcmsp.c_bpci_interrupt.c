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
struct msp_pci_regs {unsigned int if_status; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ PCI_BASE_REG ; 

__attribute__((used)) static irqreturn_t bpci_interrupt(int irq, void *dev_id)
{
	struct msp_pci_regs *preg = (void *)PCI_BASE_REG;
	unsigned int stat = preg->if_status;

#if defined(CONFIG_PROC_FS) && defined(PCI_COUNTERS)
	int i;
	for (i = 0; i < 32; ++i) {
		if ((1 << i) & stat)
			++pci_int_count[i];
	}
#endif /* PROC_FS && PCI_COUNTERS */

	/* printk("PCI ISR: Status=%08X\n", stat); */

	/* write to clear all asserted interrupts */
	preg->if_status = stat;

	return IRQ_HANDLED;
}