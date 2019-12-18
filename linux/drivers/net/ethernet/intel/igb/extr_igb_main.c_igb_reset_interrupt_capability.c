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
struct igb_adapter {int num_q_vectors; int flags; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int IGB_FLAG_HAS_MSI ; 
 int IGB_FLAG_HAS_MSIX ; 
 int /*<<< orphan*/  igb_reset_q_vector (struct igb_adapter*,int) ; 
 int /*<<< orphan*/  pci_disable_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_msix (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void igb_reset_interrupt_capability(struct igb_adapter *adapter)
{
	int v_idx = adapter->num_q_vectors;

	if (adapter->flags & IGB_FLAG_HAS_MSIX)
		pci_disable_msix(adapter->pdev);
	else if (adapter->flags & IGB_FLAG_HAS_MSI)
		pci_disable_msi(adapter->pdev);

	while (v_idx--)
		igb_reset_q_vector(adapter, v_idx);
}