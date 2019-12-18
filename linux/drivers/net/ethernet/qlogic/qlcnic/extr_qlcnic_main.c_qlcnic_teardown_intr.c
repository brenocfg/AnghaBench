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
struct qlcnic_adapter {int flags; TYPE_1__* ahw; int /*<<< orphan*/ * msix_entries; int /*<<< orphan*/  pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * intr_tbl; } ;

/* Variables and functions */
 int QLCNIC_MSIX_ENABLED ; 
 int QLCNIC_MSI_ENABLED ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_msix (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

void qlcnic_teardown_intr(struct qlcnic_adapter *adapter)
{
	if (adapter->flags & QLCNIC_MSIX_ENABLED)
		pci_disable_msix(adapter->pdev);
	if (adapter->flags & QLCNIC_MSI_ENABLED)
		pci_disable_msi(adapter->pdev);

	kfree(adapter->msix_entries);
	adapter->msix_entries = NULL;

	if (adapter->ahw->intr_tbl) {
		vfree(adapter->ahw->intr_tbl);
		adapter->ahw->intr_tbl = NULL;
	}
}