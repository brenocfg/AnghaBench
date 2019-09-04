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
struct resource {int start; int end; int /*<<< orphan*/  parent; } ;
struct TYPE_2__ {int m64_base; int m64_segsize; } ;
struct pnv_phb {TYPE_1__ ioda; } ;
struct pci_dev {struct resource* resource; int /*<<< orphan*/  bus; } ;
struct pci_controller {struct pnv_phb* private_data; } ;
typedef  int resource_size_t ;

/* Variables and functions */
 int PCI_ROM_RESOURCE ; 
 int _ALIGN_DOWN (int,int) ; 
 int _ALIGN_UP (int,int) ; 
 struct pci_controller* pci_bus_to_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnv_ioda_reserve_pe (struct pnv_phb*,int) ; 
 int /*<<< orphan*/  pnv_pci_is_m64 (struct pnv_phb*,struct resource*) ; 
 int /*<<< orphan*/  set_bit (int,unsigned long*) ; 

__attribute__((used)) static void pnv_ioda_reserve_dev_m64_pe(struct pci_dev *pdev,
					 unsigned long *pe_bitmap)
{
	struct pci_controller *hose = pci_bus_to_host(pdev->bus);
	struct pnv_phb *phb = hose->private_data;
	struct resource *r;
	resource_size_t base, sgsz, start, end;
	int segno, i;

	base = phb->ioda.m64_base;
	sgsz = phb->ioda.m64_segsize;
	for (i = 0; i <= PCI_ROM_RESOURCE; i++) {
		r = &pdev->resource[i];
		if (!r->parent || !pnv_pci_is_m64(phb, r))
			continue;

		start = _ALIGN_DOWN(r->start - base, sgsz);
		end = _ALIGN_UP(r->end - base, sgsz);
		for (segno = start / sgsz; segno < end / sgsz; segno++) {
			if (pe_bitmap)
				set_bit(segno, pe_bitmap);
			else
				pnv_ioda_reserve_pe(phb, segno);
		}
	}
}