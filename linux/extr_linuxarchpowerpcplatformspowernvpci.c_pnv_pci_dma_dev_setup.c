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
struct pnv_phb {int /*<<< orphan*/  (* dma_dev_setup ) (struct pnv_phb*,struct pci_dev*) ;} ;
struct pci_dev {int /*<<< orphan*/  bus; } ;
struct pci_controller {struct pnv_phb* private_data; } ;

/* Variables and functions */
 struct pci_controller* pci_bus_to_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct pnv_phb*,struct pci_dev*) ; 

void pnv_pci_dma_dev_setup(struct pci_dev *pdev)
{
	struct pci_controller *hose = pci_bus_to_host(pdev->bus);
	struct pnv_phb *phb = hose->private_data;
#ifdef CONFIG_PCI_IOV
	struct pnv_ioda_pe *pe;
	struct pci_dn *pdn;

	/* Fix the VF pdn PE number */
	if (pdev->is_virtfn) {
		pdn = pci_get_pdn(pdev);
		WARN_ON(pdn->pe_number != IODA_INVALID_PE);
		list_for_each_entry(pe, &phb->ioda.pe_list, list) {
			if (pe->rid == ((pdev->bus->number << 8) |
			    (pdev->devfn & 0xff))) {
				pdn->pe_number = pe->pe_number;
				pe->pdev = pdev;
				break;
			}
		}
	}
#endif /* CONFIG_PCI_IOV */

	if (phb && phb->dma_dev_setup)
		phb->dma_dev_setup(phb, pdev);
}