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
struct pci_epf {int func_no; int /*<<< orphan*/  list; struct pci_epc* epc; } ;
struct pci_epc {int max_functions; int /*<<< orphan*/  lock; int /*<<< orphan*/  pci_epf; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct pci_epc*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int pci_epc_add_epf(struct pci_epc *epc, struct pci_epf *epf)
{
	unsigned long flags;

	if (epf->epc)
		return -EBUSY;

	if (IS_ERR(epc))
		return -EINVAL;

	if (epf->func_no > epc->max_functions - 1)
		return -EINVAL;

	epf->epc = epc;

	spin_lock_irqsave(&epc->lock, flags);
	list_add_tail(&epf->list, &epc->pci_epf);
	spin_unlock_irqrestore(&epc->lock, flags);

	return 0;
}