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
struct igc_adapter {int num_q_vectors; int flags; int /*<<< orphan*/  pdev; int /*<<< orphan*/ * msix_entries; } ;

/* Variables and functions */
 int IGC_FLAG_HAS_MSI ; 
 int /*<<< orphan*/  igc_reset_q_vector (struct igc_adapter*,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_msix (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void igc_reset_interrupt_capability(struct igc_adapter *adapter)
{
	int v_idx = adapter->num_q_vectors;

	if (adapter->msix_entries) {
		pci_disable_msix(adapter->pdev);
		kfree(adapter->msix_entries);
		adapter->msix_entries = NULL;
	} else if (adapter->flags & IGC_FLAG_HAS_MSI) {
		pci_disable_msi(adapter->pdev);
	}

	while (v_idx--)
		igc_reset_q_vector(adapter, v_idx);
}