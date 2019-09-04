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
struct pci_dn {struct pci_dn* parent; } ;
struct eeh_pe {int dummy; } ;
struct eeh_dev {struct eeh_pe* pe; scalar_t__ physfn; } ;

/* Variables and functions */
 struct pci_dn* eeh_dev_to_pdn (struct eeh_dev*) ; 
 struct pci_dn* pci_get_pdn (scalar_t__) ; 
 struct eeh_dev* pdn_to_eeh_dev (struct pci_dn*) ; 

__attribute__((used)) static struct eeh_pe *eeh_pe_get_parent(struct eeh_dev *edev)
{
	struct eeh_dev *parent;
	struct pci_dn *pdn = eeh_dev_to_pdn(edev);

	/*
	 * It might have the case for the indirect parent
	 * EEH device already having associated PE, but
	 * the direct parent EEH device doesn't have yet.
	 */
	if (edev->physfn)
		pdn = pci_get_pdn(edev->physfn);
	else
		pdn = pdn ? pdn->parent : NULL;
	while (pdn) {
		/* We're poking out of PCI territory */
		parent = pdn_to_eeh_dev(pdn);
		if (!parent)
			return NULL;

		if (parent->pe)
			return parent->pe;

		pdn = pdn->parent;
	}

	return NULL;
}