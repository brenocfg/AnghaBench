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
struct iommu_table {TYPE_1__* it_ops; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* flush ) (struct iommu_table*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  __iommu_free (struct iommu_table*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  stub1 (struct iommu_table*) ; 

__attribute__((used)) static void iommu_free(struct iommu_table *tbl, dma_addr_t dma_addr,
		unsigned int npages)
{
	__iommu_free(tbl, dma_addr, npages);

	/* Make sure TLB cache is flushed if the HW needs it. We do
	 * not do an mb() here on purpose, it is not needed on any of
	 * the current platforms.
	 */
	if (tbl->it_ops->flush)
		tbl->it_ops->flush(tbl);
}