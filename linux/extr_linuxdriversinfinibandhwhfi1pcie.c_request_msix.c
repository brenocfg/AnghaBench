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
typedef  int /*<<< orphan*/  u32 ;
struct hfi1_devdata {int /*<<< orphan*/  pcidev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_IRQ_MSIX ; 
 int /*<<< orphan*/  dd_dev_err (struct hfi1_devdata*,char*,int) ; 
 int pci_alloc_irq_vectors (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tune_pcie_caps (struct hfi1_devdata*) ; 

int request_msix(struct hfi1_devdata *dd, u32 msireq)
{
	int nvec;

	nvec = pci_alloc_irq_vectors(dd->pcidev, msireq, msireq, PCI_IRQ_MSIX);
	if (nvec < 0) {
		dd_dev_err(dd, "pci_alloc_irq_vectors() failed: %d\n", nvec);
		return nvec;
	}

	tune_pcie_caps(dd);

	return nvec;
}