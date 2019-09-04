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
struct hfi1_msix_entry {int /*<<< orphan*/  arg; } ;
struct hfi1_devdata {int num_msix_entries; int /*<<< orphan*/  pcidev; struct hfi1_msix_entry* msix_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  hfi1_put_irq_affinity (struct hfi1_devdata*,struct hfi1_msix_entry*) ; 
 int /*<<< orphan*/  kfree (struct hfi1_msix_entry*) ; 
 int /*<<< orphan*/  pci_free_irq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (int /*<<< orphan*/ ) ; 

void hfi1_clean_up_interrupts(struct hfi1_devdata *dd)
{
	int i;
	struct hfi1_msix_entry *me = dd->msix_entries;

	/* remove irqs - must happen before disabling/turning off */
	for (i = 0; i < dd->num_msix_entries; i++, me++) {
		if (!me->arg) /* => no irq, no affinity */
			continue;
		hfi1_put_irq_affinity(dd, me);
		pci_free_irq(dd->pcidev, i, me->arg);
	}

	/* clean structures */
	kfree(dd->msix_entries);
	dd->msix_entries = NULL;
	dd->num_msix_entries = 0;

	pci_free_irq_vectors(dd->pcidev);
}