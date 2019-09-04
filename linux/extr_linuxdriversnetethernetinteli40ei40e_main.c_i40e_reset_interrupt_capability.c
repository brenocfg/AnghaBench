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
struct i40e_pf {int flags; int /*<<< orphan*/  pdev; int /*<<< orphan*/ * irq_pile; int /*<<< orphan*/ * msix_entries; } ;

/* Variables and functions */
 int I40E_FLAG_MSIX_ENABLED ; 
 int I40E_FLAG_MSI_ENABLED ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_msix (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i40e_reset_interrupt_capability(struct i40e_pf *pf)
{
	/* If we're in Legacy mode, the interrupt was cleaned in vsi_close */
	if (pf->flags & I40E_FLAG_MSIX_ENABLED) {
		pci_disable_msix(pf->pdev);
		kfree(pf->msix_entries);
		pf->msix_entries = NULL;
		kfree(pf->irq_pile);
		pf->irq_pile = NULL;
	} else if (pf->flags & I40E_FLAG_MSI_ENABLED) {
		pci_disable_msi(pf->pdev);
	}
	pf->flags &= ~(I40E_FLAG_MSIX_ENABLED | I40E_FLAG_MSI_ENABLED);
}