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
struct qib_devdata {int /*<<< orphan*/  pcidev; scalar_t__ msi_lo; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_IRQ_LEGACY ; 
 scalar_t__ pci_alloc_irq_vectors (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_dev_err (struct qib_devdata*,char*) ; 
 int /*<<< orphan*/  qib_devinfo (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  qib_free_irq (struct qib_devdata*) ; 
 int /*<<< orphan*/  qib_setup_7220_interrupt (struct qib_devdata*) ; 

__attribute__((used)) static int qib_7220_intr_fallback(struct qib_devdata *dd)
{
	if (!dd->msi_lo)
		return 0;

	qib_devinfo(dd->pcidev,
		    "MSI interrupt not detected, trying INTx interrupts\n");

	qib_free_irq(dd);
	dd->msi_lo = 0;
	if (pci_alloc_irq_vectors(dd->pcidev, 1, 1, PCI_IRQ_LEGACY) < 0)
		qib_dev_err(dd, "Failed to enable INTx\n");
	qib_setup_7220_interrupt(dd);
	return 1;
}