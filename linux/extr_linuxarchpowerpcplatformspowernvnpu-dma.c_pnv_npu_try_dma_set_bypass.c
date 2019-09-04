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
struct TYPE_3__ {struct pnv_ioda_pe* pe_array; } ;
struct pnv_phb {TYPE_1__ ioda; } ;
struct pnv_ioda_pe {int dummy; } ;
struct pci_dn {size_t pe_number; } ;
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  bus; } ;
struct TYPE_4__ {struct pnv_phb* private_data; } ;

/* Variables and functions */
 size_t IODA_INVALID_PE ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 TYPE_2__* pci_bus_to_host (int /*<<< orphan*/ ) ; 
 struct pci_dn* pci_get_pdn (struct pci_dev*) ; 
 int /*<<< orphan*/  pnv_npu_dma_set_32 (struct pnv_ioda_pe*) ; 
 int /*<<< orphan*/  pnv_npu_dma_set_bypass (struct pnv_ioda_pe*) ; 
 struct pci_dev* pnv_pci_get_npu_dev (struct pci_dev*,int) ; 

void pnv_npu_try_dma_set_bypass(struct pci_dev *gpdev, bool bypass)
{
	int i;
	struct pnv_phb *phb;
	struct pci_dn *pdn;
	struct pnv_ioda_pe *npe;
	struct pci_dev *npdev;

	for (i = 0; ; ++i) {
		npdev = pnv_pci_get_npu_dev(gpdev, i);

		if (!npdev)
			break;

		pdn = pci_get_pdn(npdev);
		if (WARN_ON(!pdn || pdn->pe_number == IODA_INVALID_PE))
			return;

		phb = pci_bus_to_host(npdev->bus)->private_data;

		/* We only do bypass if it's enabled on the linked device */
		npe = &phb->ioda.pe_array[pdn->pe_number];

		if (bypass) {
			dev_info(&npdev->dev,
					"Using 64-bit DMA iommu bypass\n");
			pnv_npu_dma_set_bypass(npe);
		} else {
			dev_info(&npdev->dev, "Using 32-bit DMA via iommu\n");
			pnv_npu_dma_set_32(npe);
		}
	}
}