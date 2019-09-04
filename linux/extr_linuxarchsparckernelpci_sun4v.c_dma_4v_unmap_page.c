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
typedef  int /*<<< orphan*/  u32 ;
struct pci_pbm_info {int /*<<< orphan*/  devhandle; } ;
struct iommu_map_table {size_t table_map_base; } ;
struct iommu {struct iommu_map_table tbl; struct atu* atu; } ;
struct TYPE_3__ {struct pci_pbm_info* host_controller; struct iommu* iommu; } ;
struct device {TYPE_1__ archdata; } ;
struct atu {struct iommu_map_table tbl; TYPE_2__* iotsb; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  size_t dma_addr_t ;
struct TYPE_4__ {unsigned long iotsb_num; } ;

/* Variables and functions */
 size_t DMA_BIT_MASK (int) ; 
 int DMA_NONE ; 
 int /*<<< orphan*/  IOMMU_ERROR_CODE ; 
 size_t IO_PAGE_ALIGN (size_t) ; 
 size_t IO_PAGE_MASK ; 
 unsigned long IO_PAGE_SHIFT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dma_4v_iommu_demap (struct device*,int /*<<< orphan*/ ,size_t,unsigned long,long,unsigned long) ; 
 int /*<<< orphan*/  iommu_tbl_range_free (struct iommu_map_table*,size_t,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ printk_ratelimit () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void dma_4v_unmap_page(struct device *dev, dma_addr_t bus_addr,
			      size_t sz, enum dma_data_direction direction,
			      unsigned long attrs)
{
	struct pci_pbm_info *pbm;
	struct iommu *iommu;
	struct atu *atu;
	struct iommu_map_table *tbl;
	unsigned long npages;
	unsigned long iotsb_num;
	long entry;
	u32 devhandle;

	if (unlikely(direction == DMA_NONE)) {
		if (printk_ratelimit())
			WARN_ON(1);
		return;
	}

	iommu = dev->archdata.iommu;
	pbm = dev->archdata.host_controller;
	atu = iommu->atu;
	devhandle = pbm->devhandle;

	npages = IO_PAGE_ALIGN(bus_addr + sz) - (bus_addr & IO_PAGE_MASK);
	npages >>= IO_PAGE_SHIFT;
	bus_addr &= IO_PAGE_MASK;

	if (bus_addr <= DMA_BIT_MASK(32)) {
		iotsb_num = 0; /* we don't care for legacy iommu */
		tbl = &iommu->tbl;
	} else {
		iotsb_num = atu->iotsb->iotsb_num;
		tbl = &atu->tbl;
	}
	entry = (bus_addr - tbl->table_map_base) >> IO_PAGE_SHIFT;
	dma_4v_iommu_demap(dev, devhandle, bus_addr, iotsb_num, entry, npages);
	iommu_tbl_range_free(tbl, bus_addr, npages, IOMMU_ERROR_CODE);
}