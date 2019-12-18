#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct qib_devdata {int /*<<< orphan*/  pcidev; TYPE_2__* cspec; } ;
struct TYPE_4__ {unsigned long long main_int_mask; int num_msix_entries; TYPE_1__* msix_entries; } ;
struct TYPE_3__ {struct qib_devdata* arg; int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_affinity_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kr_intgranted ; 
 int /*<<< orphan*/  pci_free_irq (int /*<<< orphan*/ ,int,struct qib_devdata*) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_irq_vector (int /*<<< orphan*/ ,int) ; 
 scalar_t__ qib_read_kreg64 (struct qib_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_write_kreg (struct qib_devdata*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  reset_dca_notifier (struct qib_devdata*,int) ; 

__attribute__((used)) static void qib_7322_free_irq(struct qib_devdata *dd)
{
	u64 intgranted;
	int i;

	dd->cspec->main_int_mask = ~0ULL;

	for (i = 0; i < dd->cspec->num_msix_entries; i++) {
		/* only free IRQs that were allocated */
		if (dd->cspec->msix_entries[i].arg) {
#ifdef CONFIG_INFINIBAND_QIB_DCA
			reset_dca_notifier(dd, i);
#endif
			irq_set_affinity_hint(pci_irq_vector(dd->pcidev, i),
					      NULL);
			free_cpumask_var(dd->cspec->msix_entries[i].mask);
			pci_free_irq(dd->pcidev, i,
				     dd->cspec->msix_entries[i].arg);
		}
	}

	/* If num_msix_entries was 0, disable the INTx IRQ */
	if (!dd->cspec->num_msix_entries)
		pci_free_irq(dd->pcidev, 0, dd);
	else
		dd->cspec->num_msix_entries = 0;

	pci_free_irq_vectors(dd->pcidev);

	/* make sure no MSIx interrupts are left pending */
	intgranted = qib_read_kreg64(dd, kr_intgranted);
	if (intgranted)
		qib_write_kreg(dd, kr_intgranted, intgranted);
}