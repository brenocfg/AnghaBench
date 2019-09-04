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
struct hfi1_msix_entry {int /*<<< orphan*/ * arg; } ;
struct hfi1_devdata {int /*<<< orphan*/  pcidev; struct hfi1_msix_entry* msix_entries; } ;
struct hfi1_ctxtdata {size_t msix_intr; struct hfi1_devdata* dd; } ;

/* Variables and functions */
 int /*<<< orphan*/  hfi1_put_irq_affinity (struct hfi1_devdata*,struct hfi1_msix_entry*) ; 
 int /*<<< orphan*/  pci_free_irq (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 

void hfi1_reset_vnic_msix_info(struct hfi1_ctxtdata *rcd)
{
	struct hfi1_devdata *dd = rcd->dd;
	struct hfi1_msix_entry *me = &dd->msix_entries[rcd->msix_intr];

	if (!me->arg) /* => no irq, no affinity */
		return;

	hfi1_put_irq_affinity(dd, me);
	pci_free_irq(dd->pcidev, rcd->msix_intr, me->arg);

	me->arg = NULL;
}