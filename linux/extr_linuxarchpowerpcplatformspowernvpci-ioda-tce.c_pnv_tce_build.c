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
typedef  int u64 ;
struct iommu_table {int it_page_shift; long it_offset; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int TCE_PCI_READ ; 
 int TCE_PCI_WRITE ; 
 int __pa (unsigned long) ; 
 int /*<<< orphan*/  cpu_to_be64 (unsigned long) ; 
 int iommu_direction_to_tce_perm (int) ; 
 int /*<<< orphan*/ * pnv_tce (struct iommu_table*,int,unsigned long,int) ; 

int pnv_tce_build(struct iommu_table *tbl, long index, long npages,
		unsigned long uaddr, enum dma_data_direction direction,
		unsigned long attrs)
{
	u64 proto_tce = iommu_direction_to_tce_perm(direction);
	u64 rpn = __pa(uaddr) >> tbl->it_page_shift;
	long i;

	if (proto_tce & TCE_PCI_WRITE)
		proto_tce |= TCE_PCI_READ;

	for (i = 0; i < npages; i++) {
		unsigned long newtce = proto_tce |
			((rpn + i) << tbl->it_page_shift);
		unsigned long idx = index - tbl->it_offset + i;

		*(pnv_tce(tbl, false, idx, true)) = cpu_to_be64(newtce);
	}

	return 0;
}