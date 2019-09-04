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
struct pci_dev {int dummy; } ;

/* Variables and functions */

void remove_dev_pci_data(struct pci_dev *pdev)
{
#ifdef CONFIG_PCI_IOV
	struct pci_dn *parent;
	struct pci_dn *pdn, *tmp;
	int i;

	/*
	 * VF and VF PE are created/released dynamically, so we need to
	 * bind/unbind them.  Otherwise the VF and VF PE would be mismatched
	 * when re-enabling SR-IOV.
	 */
	if (pdev->is_virtfn) {
		pdn = pci_get_pdn(pdev);
		pdn->pe_number = IODA_INVALID_PE;
		return;
	}

	/* Only support IOV PF for now */
	if (!pdev->is_physfn)
		return;

	/* Check if VFs have been populated */
	pdn = pci_get_pdn(pdev);
	if (!pdn || !(pdn->flags & PCI_DN_FLAG_IOV_VF))
		return;

	pdn->flags &= ~PCI_DN_FLAG_IOV_VF;
	parent = pci_bus_to_pdn(pdev->bus);
	if (!parent)
		return;

	/*
	 * We might introduce flag to pci_dn in future
	 * so that we can release VF's firmware data in
	 * a batch mode.
	 */
	for (i = 0; i < pci_sriov_get_totalvfs(pdev); i++) {
		struct eeh_dev *edev __maybe_unused;

		list_for_each_entry_safe(pdn, tmp,
			&parent->child_list, list) {
			if (pdn->busno != pci_iov_virtfn_bus(pdev, i) ||
			    pdn->devfn != pci_iov_virtfn_devfn(pdev, i))
				continue;

#ifdef CONFIG_EEH
			/* Release EEH device for the VF */
			edev = pdn_to_eeh_dev(pdn);
			if (edev) {
				pdn->edev = NULL;
				kfree(edev);
			}
#endif /* CONFIG_EEH */

			if (!list_empty(&pdn->list))
				list_del(&pdn->list);

			kfree(pdn);
		}
	}
#endif /* CONFIG_PCI_IOV */
}