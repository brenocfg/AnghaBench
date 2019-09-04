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
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {unsigned int error; unsigned int error_addr; } ;
struct TYPE_4__ {TYPE_1__ pci; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned int MACEPCI_ERROR_CONFIG_ADDR ; 
 unsigned int MACEPCI_ERROR_DATA_PARITY_ERR ; 
 unsigned int MACEPCI_ERROR_ILLEGAL_CMD ; 
 unsigned int MACEPCI_ERROR_INTERRUPT_TEST ; 
 unsigned int MACEPCI_ERROR_MASTER_ABORT ; 
 unsigned int MACEPCI_ERROR_MEMORY_ADDR ; 
 unsigned int MACEPCI_ERROR_OVERRUN ; 
 unsigned int MACEPCI_ERROR_PARITY_ERR ; 
 unsigned int MACEPCI_ERROR_RETRY_ERR ; 
 unsigned int MACEPCI_ERROR_SIG_TABORT ; 
 unsigned int MACEPCI_ERROR_SYSTEM_ERR ; 
 unsigned int MACEPCI_ERROR_TARGET_ABORT ; 
 TYPE_2__* mace ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static irqreturn_t macepci_error(int irq, void *dev)
{
	char s;
	unsigned int flags = mace->pci.error;
	unsigned int addr = mace->pci.error_addr;

	if (flags & MACEPCI_ERROR_MEMORY_ADDR)
		s = 'M';
	else if (flags & MACEPCI_ERROR_CONFIG_ADDR)
		s = 'C';
	else
		s = 'X';

	if (flags & MACEPCI_ERROR_MASTER_ABORT) {
		printk("MACEPCI: Master abort at 0x%08x (%c)\n", addr, s);
		flags &= ~MACEPCI_ERROR_MASTER_ABORT;
	}
	if (flags & MACEPCI_ERROR_TARGET_ABORT) {
		printk("MACEPCI: Target abort at 0x%08x (%c)\n", addr, s);
		flags &= ~MACEPCI_ERROR_TARGET_ABORT;
	}
	if (flags & MACEPCI_ERROR_DATA_PARITY_ERR) {
		printk("MACEPCI: Data parity error at 0x%08x (%c)\n", addr, s);
		flags &= ~MACEPCI_ERROR_DATA_PARITY_ERR;
	}
	if (flags & MACEPCI_ERROR_RETRY_ERR) {
		printk("MACEPCI: Retry error at 0x%08x (%c)\n", addr, s);
		flags &= ~MACEPCI_ERROR_RETRY_ERR;
	}
	if (flags & MACEPCI_ERROR_ILLEGAL_CMD) {
		printk("MACEPCI: Illegal command at 0x%08x (%c)\n", addr, s);
		flags &= ~MACEPCI_ERROR_ILLEGAL_CMD;
	}
	if (flags & MACEPCI_ERROR_SYSTEM_ERR) {
		printk("MACEPCI: System error at 0x%08x (%c)\n", addr, s);
		flags &= ~MACEPCI_ERROR_SYSTEM_ERR;
	}
	if (flags & MACEPCI_ERROR_PARITY_ERR) {
		printk("MACEPCI: Parity error at 0x%08x (%c)\n", addr, s);
		flags &= ~MACEPCI_ERROR_PARITY_ERR;
	}
	if (flags & MACEPCI_ERROR_OVERRUN) {
		printk("MACEPCI: Overrun error at 0x%08x (%c)\n", addr, s);
		flags &= ~MACEPCI_ERROR_OVERRUN;
	}
	if (flags & MACEPCI_ERROR_SIG_TABORT) {
		printk("MACEPCI: Signaled target abort (clearing)\n");
		flags &= ~MACEPCI_ERROR_SIG_TABORT;
	}
	if (flags & MACEPCI_ERROR_INTERRUPT_TEST) {
		printk("MACEPCI: Interrupt test triggered (clearing)\n");
		flags &= ~MACEPCI_ERROR_INTERRUPT_TEST;
	}

	mace->pci.error = flags;

	return IRQ_HANDLED;
}