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
struct pci_epc {scalar_t__ max_functions; int /*<<< orphan*/  lock; TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* unmap_addr ) (struct pci_epc*,scalar_t__,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct pci_epc*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct pci_epc*,scalar_t__,int /*<<< orphan*/ ) ; 

void pci_epc_unmap_addr(struct pci_epc *epc, u8 func_no,
			phys_addr_t phys_addr)
{
	unsigned long flags;

	if (IS_ERR_OR_NULL(epc) || func_no >= epc->max_functions)
		return;

	if (!epc->ops->unmap_addr)
		return;

	spin_lock_irqsave(&epc->lock, flags);
	epc->ops->unmap_addr(epc, func_no, phys_addr);
	spin_unlock_irqrestore(&epc->lock, flags);
}