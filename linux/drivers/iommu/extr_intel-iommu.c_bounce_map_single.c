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
typedef  int /*<<< orphan*/  u64 ;
struct intel_iommu {int /*<<< orphan*/  cap; } ;
struct dmar_domain {int /*<<< orphan*/  iovad; } ;
struct device {int dummy; } ;
typedef  size_t phys_addr_t ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  size_t dma_addr_t ;

/* Variables and functions */
 size_t ALIGN (size_t,int /*<<< orphan*/ ) ; 
 unsigned long DMA_ATTR_SKIP_CPU_SYNC ; 
 int DMA_BIDIRECTIONAL ; 
 int DMA_FROM_DEVICE ; 
 size_t DMA_MAPPING_ERROR ; 
 int DMA_NONE ; 
 int DMA_PTE_READ ; 
 int DMA_PTE_WRITE ; 
 int DMA_TO_DEVICE ; 
 int /*<<< orphan*/  IS_ALIGNED (size_t,int /*<<< orphan*/ ) ; 
 unsigned long PAGE_SHIFT ; 
 size_t VTD_PAGE_SHIFT ; 
 int /*<<< orphan*/  VTD_PAGE_SIZE ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  __phys_to_dma (struct device*,int /*<<< orphan*/ ) ; 
 unsigned long aligned_nrpages (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  cap_zlr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,size_t,unsigned long long,int) ; 
 int /*<<< orphan*/  dma_to_mm_pfn (unsigned long) ; 
 struct intel_iommu* domain_get_iommu (struct dmar_domain*) ; 
 int domain_pfn_mapping (struct dmar_domain*,int /*<<< orphan*/ ,size_t,unsigned long,int) ; 
 struct dmar_domain* find_domain (struct device*) ; 
 int /*<<< orphan*/  free_iova_fast (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long intel_alloc_iova (struct device*,struct dmar_domain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_tlb_start ; 
 scalar_t__ is_swiotlb_buffer (size_t) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  mm_to_dma_pfn (unsigned long) ; 
 void* phys_to_virt (size_t) ; 
 size_t swiotlb_tbl_map_single (struct device*,int /*<<< orphan*/ ,size_t,size_t,size_t,int,unsigned long) ; 
 int /*<<< orphan*/  swiotlb_tbl_unmap_single (struct device*,size_t,size_t,size_t,int,unsigned long) ; 
 int /*<<< orphan*/  trace_bounce_map_single (struct device*,unsigned long,size_t,size_t) ; 

__attribute__((used)) static dma_addr_t
bounce_map_single(struct device *dev, phys_addr_t paddr, size_t size,
		  enum dma_data_direction dir, unsigned long attrs,
		  u64 dma_mask)
{
	size_t aligned_size = ALIGN(size, VTD_PAGE_SIZE);
	struct dmar_domain *domain;
	struct intel_iommu *iommu;
	unsigned long iova_pfn;
	unsigned long nrpages;
	phys_addr_t tlb_addr;
	int prot = 0;
	int ret;

	domain = find_domain(dev);
	if (WARN_ON(dir == DMA_NONE || !domain))
		return DMA_MAPPING_ERROR;

	iommu = domain_get_iommu(domain);
	if (WARN_ON(!iommu))
		return DMA_MAPPING_ERROR;

	nrpages = aligned_nrpages(0, size);
	iova_pfn = intel_alloc_iova(dev, domain,
				    dma_to_mm_pfn(nrpages), dma_mask);
	if (!iova_pfn)
		return DMA_MAPPING_ERROR;

	/*
	 * Check if DMAR supports zero-length reads on write only
	 * mappings..
	 */
	if (dir == DMA_TO_DEVICE || dir == DMA_BIDIRECTIONAL ||
			!cap_zlr(iommu->cap))
		prot |= DMA_PTE_READ;
	if (dir == DMA_FROM_DEVICE || dir == DMA_BIDIRECTIONAL)
		prot |= DMA_PTE_WRITE;

	/*
	 * If both the physical buffer start address and size are
	 * page aligned, we don't need to use a bounce page.
	 */
	if (!IS_ALIGNED(paddr | size, VTD_PAGE_SIZE)) {
		tlb_addr = swiotlb_tbl_map_single(dev,
				__phys_to_dma(dev, io_tlb_start),
				paddr, size, aligned_size, dir, attrs);
		if (tlb_addr == DMA_MAPPING_ERROR) {
			goto swiotlb_error;
		} else {
			/* Cleanup the padding area. */
			void *padding_start = phys_to_virt(tlb_addr);
			size_t padding_size = aligned_size;

			if (!(attrs & DMA_ATTR_SKIP_CPU_SYNC) &&
			    (dir == DMA_TO_DEVICE ||
			     dir == DMA_BIDIRECTIONAL)) {
				padding_start += size;
				padding_size -= size;
			}

			memset(padding_start, 0, padding_size);
		}
	} else {
		tlb_addr = paddr;
	}

	ret = domain_pfn_mapping(domain, mm_to_dma_pfn(iova_pfn),
				 tlb_addr >> VTD_PAGE_SHIFT, nrpages, prot);
	if (ret)
		goto mapping_error;

	trace_bounce_map_single(dev, iova_pfn << PAGE_SHIFT, paddr, size);

	return (phys_addr_t)iova_pfn << PAGE_SHIFT;

mapping_error:
	if (is_swiotlb_buffer(tlb_addr))
		swiotlb_tbl_unmap_single(dev, tlb_addr, size,
					 aligned_size, dir, attrs);
swiotlb_error:
	free_iova_fast(&domain->iovad, iova_pfn, dma_to_mm_pfn(nrpages));
	dev_err(dev, "Device bounce map: %zx@%llx dir %d --- failed\n",
		size, (unsigned long long)paddr, dir);

	return DMA_MAPPING_ERROR;
}