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
typedef  scalar_t__ u8 ;
struct pci_epf_bar {int flags; scalar_t__ barno; int /*<<< orphan*/  size; } ;
struct pci_epc {scalar_t__ max_functions; int /*<<< orphan*/  lock; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* set_bar ) (struct pci_epc*,scalar_t__,struct pci_epf_bar*) ;} ;

/* Variables and functions */
 scalar_t__ BAR_5 ; 
 int EINVAL ; 
 scalar_t__ IS_ERR_OR_NULL (struct pci_epc*) ; 
 int PCI_BASE_ADDRESS_IO_MASK ; 
 int PCI_BASE_ADDRESS_MEM_TYPE_64 ; 
 int PCI_BASE_ADDRESS_SPACE_IO ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct pci_epc*,scalar_t__,struct pci_epf_bar*) ; 
 scalar_t__ upper_32_bits (int /*<<< orphan*/ ) ; 

int pci_epc_set_bar(struct pci_epc *epc, u8 func_no,
		    struct pci_epf_bar *epf_bar)
{
	int ret;
	unsigned long irq_flags;
	int flags = epf_bar->flags;

	if (IS_ERR_OR_NULL(epc) || func_no >= epc->max_functions ||
	    (epf_bar->barno == BAR_5 &&
	     flags & PCI_BASE_ADDRESS_MEM_TYPE_64) ||
	    (flags & PCI_BASE_ADDRESS_SPACE_IO &&
	     flags & PCI_BASE_ADDRESS_IO_MASK) ||
	    (upper_32_bits(epf_bar->size) &&
	     !(flags & PCI_BASE_ADDRESS_MEM_TYPE_64)))
		return -EINVAL;

	if (!epc->ops->set_bar)
		return 0;

	spin_lock_irqsave(&epc->lock, irq_flags);
	ret = epc->ops->set_bar(epc, func_no, epf_bar);
	spin_unlock_irqrestore(&epc->lock, irq_flags);

	return ret;
}