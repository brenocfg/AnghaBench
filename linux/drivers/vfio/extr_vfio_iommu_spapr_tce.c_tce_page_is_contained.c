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
struct page {int dummy; } ;
struct mm_struct {int dummy; } ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  compound_head (struct page*) ; 
 scalar_t__ mm_iommu_is_devmem (struct mm_struct*,unsigned long,unsigned int,unsigned long*) ; 
 unsigned int page_shift (int /*<<< orphan*/ ) ; 
 struct page* pfn_to_page (unsigned long) ; 

__attribute__((used)) static bool tce_page_is_contained(struct mm_struct *mm, unsigned long hpa,
		unsigned int it_page_shift)
{
	struct page *page;
	unsigned long size = 0;

	if (mm_iommu_is_devmem(mm, hpa, it_page_shift, &size))
		return size == (1UL << it_page_shift);

	page = pfn_to_page(hpa >> PAGE_SHIFT);
	/*
	 * Check that the TCE table granularity is not bigger than the size of
	 * a page we just found. Otherwise the hardware can get access to
	 * a bigger memory chunk that it should.
	 */
	return page_shift(compound_head(page)) >= it_page_shift;
}