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
struct hfi1_msix_entry {int dummy; } ;
struct TYPE_2__ {int max_requested; struct hfi1_msix_entry* msix_entries; } ;
struct hfi1_devdata {int /*<<< orphan*/  pcidev; TYPE_1__ msix_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct hfi1_msix_entry*) ; 
 int /*<<< orphan*/  msix_free_irq (struct hfi1_devdata*,int) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (int /*<<< orphan*/ ) ; 

void msix_clean_up_interrupts(struct hfi1_devdata *dd)
{
	int i;
	struct hfi1_msix_entry *me = dd->msix_info.msix_entries;

	/* remove irqs - must happen before disabling/turning off */
	for (i = 0; i < dd->msix_info.max_requested; i++, me++)
		msix_free_irq(dd, i);

	/* clean structures */
	kfree(dd->msix_info.msix_entries);
	dd->msix_info.msix_entries = NULL;
	dd->msix_info.max_requested = 0;

	pci_free_irq_vectors(dd->pcidev);
}