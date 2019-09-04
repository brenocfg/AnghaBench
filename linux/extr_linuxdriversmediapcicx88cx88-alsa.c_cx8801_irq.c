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
struct cx88_audio_dev {struct cx88_core* core; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int MAX_IRQ_LOOP ; 
 int /*<<< orphan*/  MO_PCI_INTMSK ; 
 int /*<<< orphan*/  MO_PCI_INTSTAT ; 
 int PCI_INT_AUDINT ; 
 int /*<<< orphan*/  cx8801_aud_irq (struct cx88_audio_dev*) ; 
 int /*<<< orphan*/  cx88_core_irq (struct cx88_core*,int) ; 
 int /*<<< orphan*/  cx_clear (int /*<<< orphan*/ ,int) ; 
 int cx_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dprintk (int,char*,int,int,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static irqreturn_t cx8801_irq(int irq, void *dev_id)
{
	struct cx88_audio_dev *chip = dev_id;
	struct cx88_core *core = chip->core;
	u32 status;
	int loop, handled = 0;

	for (loop = 0; loop < MAX_IRQ_LOOP; loop++) {
		status = cx_read(MO_PCI_INTSTAT) &
			(core->pci_irqmask | PCI_INT_AUDINT);
		if (status == 0)
			goto out;
		dprintk(3, "cx8801_irq loop %d/%d, status %x\n",
			loop, MAX_IRQ_LOOP, status);
		handled = 1;
		cx_write(MO_PCI_INTSTAT, status);

		if (status & core->pci_irqmask)
			cx88_core_irq(core, status);
		if (status & PCI_INT_AUDINT)
			cx8801_aud_irq(chip);
	}

	if (loop == MAX_IRQ_LOOP) {
		pr_err("IRQ loop detected, disabling interrupts\n");
		cx_clear(MO_PCI_INTMSK, PCI_INT_AUDINT);
	}

 out:
	return IRQ_RETVAL(handled);
}