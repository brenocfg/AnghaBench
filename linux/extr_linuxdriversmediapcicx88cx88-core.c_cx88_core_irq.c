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
struct cx88_core {int /*<<< orphan*/  pci_irqmask; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int PCI_INT_IR_SMPINT ; 
 int /*<<< orphan*/  cx88_ir_irq (struct cx88_core*) ; 
 int /*<<< orphan*/  cx88_pci_irqs ; 
 int /*<<< orphan*/  cx88_print_irqbits (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int cx88_core_irq(struct cx88_core *core, u32 status)
{
	int handled = 0;

	if (status & PCI_INT_IR_SMPINT) {
		cx88_ir_irq(core);
		handled++;
	}
	if (!handled)
		cx88_print_irqbits("irq pci",
				   cx88_pci_irqs, ARRAY_SIZE(cx88_pci_irqs),
				   status, core->pci_irqmask);
	return handled;
}