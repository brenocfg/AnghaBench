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
struct iommu_table {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pnv_pci_ioda2_tce_invalidate (struct iommu_table*,long,long,int) ; 
 int /*<<< orphan*/  pnv_tce_free (struct iommu_table*,long,long) ; 

__attribute__((used)) static void pnv_ioda2_tce_free(struct iommu_table *tbl, long index,
		long npages)
{
	pnv_tce_free(tbl, index, npages);

	pnv_pci_ioda2_tce_invalidate(tbl, index, npages, false);
}