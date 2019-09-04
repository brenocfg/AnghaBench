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
struct pnv_phb {int /*<<< orphan*/  opal_id; } ;
struct TYPE_2__ {int /*<<< orphan*/ * tables; } ;
struct pnv_ioda_pe {TYPE_1__ table_group; int /*<<< orphan*/  pe_number; struct pnv_phb* phb; } ;
typedef  long int64_t ;

/* Variables and functions */
 long opal_pci_map_pe_dma_window (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pe_err (struct pnv_ioda_pe*,char*,long) ; 
 int /*<<< orphan*/  pe_info (struct pnv_ioda_pe*,char*) ; 
 int /*<<< orphan*/  pnv_pci_ioda2_tce_invalidate_entire (struct pnv_phb*,int) ; 
 int /*<<< orphan*/  pnv_pci_unlink_table_and_group (int /*<<< orphan*/ ,TYPE_1__*) ; 

long pnv_npu_unset_window(struct pnv_ioda_pe *npe, int num)
{
	struct pnv_phb *phb = npe->phb;
	int64_t rc;

	pe_info(npe, "Removing DMA window\n");

	rc = opal_pci_map_pe_dma_window(phb->opal_id, npe->pe_number,
			npe->pe_number,
			0/* levels */, 0/* table address */,
			0/* table size */, 0/* page size */);
	if (rc) {
		pe_err(npe, "Unmapping failed, ret = %lld\n", rc);
		return rc;
	}
	pnv_pci_ioda2_tce_invalidate_entire(phb, false);

	pnv_pci_unlink_table_and_group(npe->table_group.tables[num],
			&npe->table_group);

	return 0;
}