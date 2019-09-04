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
struct pci_dn {int dummy; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 struct pci_dn* pci_get_pdn (struct pci_dev*) ; 

struct pci_dn *add_dev_pci_data(struct pci_dev *pdev)
{
#ifdef CONFIG_PCI_IOV
	struct pci_dn *parent, *pdn;
	int i;

	/* Only support IOV for now */
	if (!pdev->is_physfn)
		return pci_get_pdn(pdev);

	/* Check if VFs have been populated */
	pdn = pci_get_pdn(pdev);
	if (!pdn || (pdn->flags & PCI_DN_FLAG_IOV_VF))
		return NULL;

	pdn->flags |= PCI_DN_FLAG_IOV_VF;
	parent = pci_bus_to_pdn(pdev->bus);
	if (!parent)
		return NULL;

	for (i = 0; i < pci_sriov_get_totalvfs(pdev); i++) {
		struct eeh_dev *edev __maybe_unused;

		pdn = add_one_dev_pci_data(parent, i,
					   pci_iov_virtfn_bus(pdev, i),
					   pci_iov_virtfn_devfn(pdev, i));
		if (!pdn) {
			dev_warn(&pdev->dev, "%s: Cannot create firmware data for VF#%d\n",
				 __func__, i);
			return NULL;
		}

#ifdef CONFIG_EEH
		/* Create the EEH device for the VF */
		edev = eeh_dev_init(pdn);
		BUG_ON(!edev);
		edev->physfn = pdev;
#endif /* CONFIG_EEH */
	}
#endif /* CONFIG_PCI_IOV */

	return pci_get_pdn(pdev);
}