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
typedef  scalar_t__ u64 ;
struct page {int dummy; } ;
struct iommu_map_table {scalar_t__ table_map_base; } ;
struct iommu {struct iommu_map_table tbl; struct atu* atu; } ;
struct TYPE_2__ {int numa_node; struct iommu* iommu; } ;
struct device {scalar_t__ coherent_dma_mask; TYPE_1__ archdata; } ;
struct atu {struct iommu_map_table tbl; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 unsigned long DMA_ATTR_WEAK_ORDERING ; 
 scalar_t__ DMA_BIT_MASK (int) ; 
 unsigned long HV_PCI_MAP_ATTR_READ ; 
 unsigned long HV_PCI_MAP_ATTR_RELAXED_ORDER ; 
 unsigned long HV_PCI_MAP_ATTR_WRITE ; 
 long IOMMU_ERROR_CODE ; 
 size_t IO_PAGE_ALIGN (size_t) ; 
 size_t IO_PAGE_SHIFT ; 
 unsigned long MAX_ORDER ; 
 unsigned long PAGE_SIZE ; 
 unsigned long __pa (unsigned long) ; 
 struct page* alloc_pages_node (int,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  free_pages (unsigned long,unsigned long) ; 
 unsigned long get_order (size_t) ; 
 long iommu_batch_add (unsigned long,scalar_t__) ; 
 long iommu_batch_end (scalar_t__) ; 
 int /*<<< orphan*/  iommu_batch_start (struct device*,unsigned long,long) ; 
 long iommu_tbl_range_alloc (struct device*,struct iommu_map_table*,unsigned long,int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_tbl_range_free (struct iommu_map_table*,scalar_t__,unsigned long,long) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ page_address (struct page*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void *dma_4v_alloc_coherent(struct device *dev, size_t size,
				   dma_addr_t *dma_addrp, gfp_t gfp,
				   unsigned long attrs)
{
	u64 mask;
	unsigned long flags, order, first_page, npages, n;
	unsigned long prot = 0;
	struct iommu *iommu;
	struct atu *atu;
	struct iommu_map_table *tbl;
	struct page *page;
	void *ret;
	long entry;
	int nid;

	size = IO_PAGE_ALIGN(size);
	order = get_order(size);
	if (unlikely(order >= MAX_ORDER))
		return NULL;

	npages = size >> IO_PAGE_SHIFT;

	if (attrs & DMA_ATTR_WEAK_ORDERING)
		prot = HV_PCI_MAP_ATTR_RELAXED_ORDER;

	nid = dev->archdata.numa_node;
	page = alloc_pages_node(nid, gfp, order);
	if (unlikely(!page))
		return NULL;

	first_page = (unsigned long) page_address(page);
	memset((char *)first_page, 0, PAGE_SIZE << order);

	iommu = dev->archdata.iommu;
	atu = iommu->atu;

	mask = dev->coherent_dma_mask;
	if (mask <= DMA_BIT_MASK(32))
		tbl = &iommu->tbl;
	else
		tbl = &atu->tbl;

	entry = iommu_tbl_range_alloc(dev, tbl, npages, NULL,
				      (unsigned long)(-1), 0);

	if (unlikely(entry == IOMMU_ERROR_CODE))
		goto range_alloc_fail;

	*dma_addrp = (tbl->table_map_base + (entry << IO_PAGE_SHIFT));
	ret = (void *) first_page;
	first_page = __pa(first_page);

	local_irq_save(flags);

	iommu_batch_start(dev,
			  (HV_PCI_MAP_ATTR_READ | prot |
			   HV_PCI_MAP_ATTR_WRITE),
			  entry);

	for (n = 0; n < npages; n++) {
		long err = iommu_batch_add(first_page + (n * PAGE_SIZE), mask);
		if (unlikely(err < 0L))
			goto iommu_map_fail;
	}

	if (unlikely(iommu_batch_end(mask) < 0L))
		goto iommu_map_fail;

	local_irq_restore(flags);

	return ret;

iommu_map_fail:
	local_irq_restore(flags);
	iommu_tbl_range_free(tbl, *dma_addrp, npages, IOMMU_ERROR_CODE);

range_alloc_fail:
	free_pages(first_page, order);
	return NULL;
}