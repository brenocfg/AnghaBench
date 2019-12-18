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
struct pci_epf {int /*<<< orphan*/ * epc; int /*<<< orphan*/  list; } ;
struct pci_epc {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct pci_epc*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void pci_epc_remove_epf(struct pci_epc *epc, struct pci_epf *epf)
{
	unsigned long flags;

	if (!epc || IS_ERR(epc) || !epf)
		return;

	spin_lock_irqsave(&epc->lock, flags);
	list_del(&epf->list);
	epf->epc = NULL;
	spin_unlock_irqrestore(&epc->lock, flags);
}