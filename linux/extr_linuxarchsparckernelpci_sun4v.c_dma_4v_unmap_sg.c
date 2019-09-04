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
struct scatterlist {scalar_t__ dma_address; unsigned int dma_length; } ;
struct pci_pbm_info {int /*<<< orphan*/  devhandle; } ;
struct iommu_map_table {scalar_t__ table_map_base; } ;
struct iommu {struct iommu_map_table tbl; struct atu* atu; } ;
struct TYPE_3__ {struct pci_pbm_info* host_controller; struct iommu* iommu; } ;
struct device {TYPE_1__ archdata; } ;
struct atu {struct iommu_map_table tbl; TYPE_2__* iotsb; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_4__ {unsigned long iotsb_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ DMA_BIT_MASK (int) ; 
 int DMA_NONE ; 
 int /*<<< orphan*/  IOMMU_ERROR_CODE ; 
 unsigned long IO_PAGE_SHIFT ; 
 int /*<<< orphan*/  IO_PAGE_SIZE ; 
 int /*<<< orphan*/  dma_4v_iommu_demap (struct device*,int /*<<< orphan*/ ,scalar_t__,unsigned long,unsigned long,unsigned long) ; 
 unsigned long iommu_num_pages (scalar_t__,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_tbl_range_free (struct iommu_map_table*,scalar_t__,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 

__attribute__((used)) static void dma_4v_unmap_sg(struct device *dev, struct scatterlist *sglist,
			    int nelems, enum dma_data_direction direction,
			    unsigned long attrs)
{
	struct pci_pbm_info *pbm;
	struct scatterlist *sg;
	struct iommu *iommu;
	struct atu *atu;
	unsigned long flags, entry;
	unsigned long iotsb_num;
	u32 devhandle;

	BUG_ON(direction == DMA_NONE);

	iommu = dev->archdata.iommu;
	pbm = dev->archdata.host_controller;
	atu = iommu->atu;
	devhandle = pbm->devhandle;
	
	local_irq_save(flags);

	sg = sglist;
	while (nelems--) {
		dma_addr_t dma_handle = sg->dma_address;
		unsigned int len = sg->dma_length;
		unsigned long npages;
		struct iommu_map_table *tbl;
		unsigned long shift = IO_PAGE_SHIFT;

		if (!len)
			break;
		npages = iommu_num_pages(dma_handle, len, IO_PAGE_SIZE);

		if (dma_handle <= DMA_BIT_MASK(32)) {
			iotsb_num = 0; /* we don't care for legacy iommu */
			tbl = &iommu->tbl;
		} else {
			iotsb_num = atu->iotsb->iotsb_num;
			tbl = &atu->tbl;
		}
		entry = ((dma_handle - tbl->table_map_base) >> shift);
		dma_4v_iommu_demap(dev, devhandle, dma_handle, iotsb_num,
				   entry, npages);
		iommu_tbl_range_free(tbl, dma_handle, npages,
				     IOMMU_ERROR_CODE);
		sg = sg_next(sg);
	}

	local_irq_restore(flags);
}