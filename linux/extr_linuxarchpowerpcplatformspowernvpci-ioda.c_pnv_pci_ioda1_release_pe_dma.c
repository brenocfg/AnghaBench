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
struct TYPE_2__ {scalar_t__ group; struct iommu_table** tables; } ;
struct pnv_ioda_pe {TYPE_1__ table_group; } ;
struct iommu_table {int it_size; int /*<<< orphan*/  it_base; int /*<<< orphan*/  it_offset; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 scalar_t__ OPAL_SUCCESS ; 
 int /*<<< orphan*/  WARN_ON (scalar_t__) ; 
 int /*<<< orphan*/  free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (int) ; 
 int /*<<< orphan*/  iommu_group_put (scalar_t__) ; 
 int /*<<< orphan*/  iommu_tce_table_put (struct iommu_table*) ; 
 scalar_t__ pnv_pci_ioda1_unset_window (TYPE_1__*,int /*<<< orphan*/ ) ; 
 unsigned int pnv_pci_ioda_pe_dma_weight (struct pnv_ioda_pe*) ; 
 int /*<<< orphan*/  pnv_pci_p7ioc_tce_invalidate (struct iommu_table*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void pnv_pci_ioda1_release_pe_dma(struct pnv_ioda_pe *pe)
{
	unsigned int weight = pnv_pci_ioda_pe_dma_weight(pe);
	struct iommu_table *tbl = pe->table_group.tables[0];
	int64_t rc;

	if (!weight)
		return;

	rc = pnv_pci_ioda1_unset_window(&pe->table_group, 0);
	if (rc != OPAL_SUCCESS)
		return;

	pnv_pci_p7ioc_tce_invalidate(tbl, tbl->it_offset, tbl->it_size, false);
	if (pe->table_group.group) {
		iommu_group_put(pe->table_group.group);
		WARN_ON(pe->table_group.group);
	}

	free_pages(tbl->it_base, get_order(tbl->it_size << 3));
	iommu_tce_table_put(tbl);
}