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
typedef  scalar_t__ u64 ;
struct dma_ops_domain {int /*<<< orphan*/  iovad; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  IOVA_PFN (scalar_t__) ; 
 unsigned long PAGE_SHIFT ; 
 unsigned int __roundup_pow_of_two (unsigned int) ; 
 unsigned long alloc_iova_fast (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned long dma_ops_alloc_iova(struct device *dev,
					struct dma_ops_domain *dma_dom,
					unsigned int pages, u64 dma_mask)
{
	unsigned long pfn = 0;

	pages = __roundup_pow_of_two(pages);

	if (dma_mask > DMA_BIT_MASK(32))
		pfn = alloc_iova_fast(&dma_dom->iovad, pages,
				      IOVA_PFN(DMA_BIT_MASK(32)), false);

	if (!pfn)
		pfn = alloc_iova_fast(&dma_dom->iovad, pages,
				      IOVA_PFN(dma_mask), true);

	return (pfn << PAGE_SHIFT);
}