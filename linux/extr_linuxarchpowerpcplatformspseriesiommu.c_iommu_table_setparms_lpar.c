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
struct pci_controller {TYPE_1__* bus; } ;
struct iommu_table_group {unsigned long tce32_start; unsigned long tce32_size; } ;
struct iommu_table {unsigned long it_page_shift; int it_blocksize; unsigned long it_offset; unsigned long it_size; int /*<<< orphan*/  it_type; scalar_t__ it_base; int /*<<< orphan*/  it_busno; int /*<<< orphan*/  it_index; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 unsigned long IOMMU_PAGE_SHIFT_4K ; 
 int /*<<< orphan*/  TCE_PCI ; 
 int /*<<< orphan*/  of_parse_dma_window (struct device_node*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,unsigned long*,unsigned long*) ; 

__attribute__((used)) static void iommu_table_setparms_lpar(struct pci_controller *phb,
				      struct device_node *dn,
				      struct iommu_table *tbl,
				      struct iommu_table_group *table_group,
				      const __be32 *dma_window)
{
	unsigned long offset, size;

	of_parse_dma_window(dn, dma_window, &tbl->it_index, &offset, &size);

	tbl->it_busno = phb->bus->number;
	tbl->it_page_shift = IOMMU_PAGE_SHIFT_4K;
	tbl->it_base   = 0;
	tbl->it_blocksize  = 16;
	tbl->it_type = TCE_PCI;
	tbl->it_offset = offset >> tbl->it_page_shift;
	tbl->it_size = size >> tbl->it_page_shift;

	table_group->tce32_start = offset;
	table_group->tce32_size = size;
}