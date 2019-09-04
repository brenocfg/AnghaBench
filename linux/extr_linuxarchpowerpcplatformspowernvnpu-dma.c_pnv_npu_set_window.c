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
struct pnv_phb {TYPE_1__* hose; int /*<<< orphan*/  opal_id; } ;
struct pnv_ioda_pe {int /*<<< orphan*/  table_group; int /*<<< orphan*/  pe_number; struct pnv_phb* phb; } ;
struct iommu_table {unsigned long it_level_size; unsigned long it_size; int it_offset; int it_page_shift; int /*<<< orphan*/  it_base; scalar_t__ it_indirect_levels; } ;
typedef  long int64_t ;
typedef  int __u64 ;
struct TYPE_2__ {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOMMU_PAGE_SIZE (struct iommu_table*) ; 
 int /*<<< orphan*/  __pa (int /*<<< orphan*/ ) ; 
 long opal_pci_map_pe_dma_window (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,unsigned long const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pe_err (struct pnv_ioda_pe*,char*,long) ; 
 int /*<<< orphan*/  pe_info (struct pnv_ioda_pe*,char*,int const,int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnv_pci_ioda2_tce_invalidate_entire (struct pnv_phb*,int) ; 
 int /*<<< orphan*/  pnv_pci_link_table_and_group (int /*<<< orphan*/ ,int,struct iommu_table*,int /*<<< orphan*/ *) ; 

long pnv_npu_set_window(struct pnv_ioda_pe *npe, int num,
		struct iommu_table *tbl)
{
	struct pnv_phb *phb = npe->phb;
	int64_t rc;
	const unsigned long size = tbl->it_indirect_levels ?
		tbl->it_level_size : tbl->it_size;
	const __u64 start_addr = tbl->it_offset << tbl->it_page_shift;
	const __u64 win_size = tbl->it_size << tbl->it_page_shift;

	pe_info(npe, "Setting up window %llx..%llx pg=%lx\n",
			start_addr, start_addr + win_size - 1,
			IOMMU_PAGE_SIZE(tbl));

	rc = opal_pci_map_pe_dma_window(phb->opal_id,
			npe->pe_number,
			npe->pe_number,
			tbl->it_indirect_levels + 1,
			__pa(tbl->it_base),
			size << 3,
			IOMMU_PAGE_SIZE(tbl));
	if (rc) {
		pe_err(npe, "Failed to configure TCE table, err %lld\n", rc);
		return rc;
	}
	pnv_pci_ioda2_tce_invalidate_entire(phb, false);

	/* Add the table to the list so its TCE cache will get invalidated */
	pnv_pci_link_table_and_group(phb->hose->node, num,
			tbl, &npe->table_group);

	return 0;
}