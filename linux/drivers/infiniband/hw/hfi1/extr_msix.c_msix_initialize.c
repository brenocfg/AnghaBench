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
typedef  scalar_t__ u32 ;
struct hfi1_msix_entry {int dummy; } ;
struct TYPE_2__ {scalar_t__ max_requested; int /*<<< orphan*/  in_use_msix; int /*<<< orphan*/  msix_lock; struct hfi1_msix_entry* msix_entries; } ;
struct hfi1_devdata {scalar_t__ num_sdma; scalar_t__ n_krcv_queues; scalar_t__ num_vnic_contexts; TYPE_1__ msix_info; int /*<<< orphan*/  pcidev; } ;

/* Variables and functions */
 scalar_t__ CCE_NUM_MSIX_VECTORS ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PCI_IRQ_MSIX ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dd_dev_err (struct hfi1_devdata*,char*,int) ; 
 int /*<<< orphan*/  dd_dev_info (struct hfi1_devdata*,char*,scalar_t__) ; 
 struct hfi1_msix_entry* kcalloc (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int pci_alloc_irq_vectors (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int msix_initialize(struct hfi1_devdata *dd)
{
	u32 total;
	int ret;
	struct hfi1_msix_entry *entries;

	/*
	 * MSIx interrupt count:
	 *	one for the general, "slow path" interrupt
	 *	one per used SDMA engine
	 *	one per kernel receive context
	 *	one for each VNIC context
	 *      ...any new IRQs should be added here.
	 */
	total = 1 + dd->num_sdma + dd->n_krcv_queues + dd->num_vnic_contexts;

	if (total >= CCE_NUM_MSIX_VECTORS)
		return -EINVAL;

	ret = pci_alloc_irq_vectors(dd->pcidev, total, total, PCI_IRQ_MSIX);
	if (ret < 0) {
		dd_dev_err(dd, "pci_alloc_irq_vectors() failed: %d\n", ret);
		return ret;
	}

	entries = kcalloc(total, sizeof(*dd->msix_info.msix_entries),
			  GFP_KERNEL);
	if (!entries) {
		pci_free_irq_vectors(dd->pcidev);
		return -ENOMEM;
	}

	dd->msix_info.msix_entries = entries;
	spin_lock_init(&dd->msix_info.msix_lock);
	bitmap_zero(dd->msix_info.in_use_msix, total);
	dd->msix_info.max_requested = total;
	dd_dev_info(dd, "%u MSI-X interrupts allocated\n", total);

	return 0;
}