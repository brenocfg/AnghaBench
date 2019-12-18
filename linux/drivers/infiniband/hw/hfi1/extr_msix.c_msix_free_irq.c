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
typedef  size_t u8 ;
struct hfi1_msix_entry {int /*<<< orphan*/ * arg; } ;
struct TYPE_2__ {size_t max_requested; int /*<<< orphan*/  msix_lock; int /*<<< orphan*/  in_use_msix; struct hfi1_msix_entry* msix_entries; } ;
struct hfi1_devdata {TYPE_1__ msix_info; int /*<<< orphan*/  pcidev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __clear_bit (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfi1_put_irq_affinity (struct hfi1_devdata*,struct hfi1_msix_entry*) ; 
 int /*<<< orphan*/  pci_free_irq (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void msix_free_irq(struct hfi1_devdata *dd, u8 msix_intr)
{
	struct hfi1_msix_entry *me;

	if (msix_intr >= dd->msix_info.max_requested)
		return;

	me = &dd->msix_info.msix_entries[msix_intr];

	if (!me->arg) /* => no irq, no affinity */
		return;

	hfi1_put_irq_affinity(dd, me);
	pci_free_irq(dd->pcidev, msix_intr, me->arg);

	me->arg = NULL;

	spin_lock(&dd->msix_info.msix_lock);
	__clear_bit(msix_intr, dd->msix_info.in_use_msix);
	spin_unlock(&dd->msix_info.msix_lock);
}