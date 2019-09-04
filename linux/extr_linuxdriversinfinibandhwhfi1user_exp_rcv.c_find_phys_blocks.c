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
typedef  unsigned int u32 ;
struct tid_user_buf {struct tid_pageset* psets; struct page** pages; } ;
struct tid_pageset {unsigned int idx; int count; } ;
struct page {int dummy; } ;

/* Variables and functions */
 unsigned int MAX_EXPECTED_BUFFER ; 
 unsigned int PAGE_SHIFT ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  is_power_of_2 (unsigned int) ; 
 unsigned long page_to_pfn (struct page*) ; 
 unsigned int rounddown_pow_of_two (unsigned int) ; 

__attribute__((used)) static u32 find_phys_blocks(struct tid_user_buf *tidbuf, unsigned int npages)
{
	unsigned pagecount, pageidx, setcount = 0, i;
	unsigned long pfn, this_pfn;
	struct page **pages = tidbuf->pages;
	struct tid_pageset *list = tidbuf->psets;

	if (!npages)
		return 0;

	/*
	 * Look for sets of physically contiguous pages in the user buffer.
	 * This will allow us to optimize Expected RcvArray entry usage by
	 * using the bigger supported sizes.
	 */
	pfn = page_to_pfn(pages[0]);
	for (pageidx = 0, pagecount = 1, i = 1; i <= npages; i++) {
		this_pfn = i < npages ? page_to_pfn(pages[i]) : 0;

		/*
		 * If the pfn's are not sequential, pages are not physically
		 * contiguous.
		 */
		if (this_pfn != ++pfn) {
			/*
			 * At this point we have to loop over the set of
			 * physically contiguous pages and break them down it
			 * sizes supported by the HW.
			 * There are two main constraints:
			 *     1. The max buffer size is MAX_EXPECTED_BUFFER.
			 *        If the total set size is bigger than that
			 *        program only a MAX_EXPECTED_BUFFER chunk.
			 *     2. The buffer size has to be a power of two. If
			 *        it is not, round down to the closes power of
			 *        2 and program that size.
			 */
			while (pagecount) {
				int maxpages = pagecount;
				u32 bufsize = pagecount * PAGE_SIZE;

				if (bufsize > MAX_EXPECTED_BUFFER)
					maxpages =
						MAX_EXPECTED_BUFFER >>
						PAGE_SHIFT;
				else if (!is_power_of_2(bufsize))
					maxpages =
						rounddown_pow_of_two(bufsize) >>
						PAGE_SHIFT;

				list[setcount].idx = pageidx;
				list[setcount].count = maxpages;
				pagecount -= maxpages;
				pageidx += maxpages;
				setcount++;
			}
			pageidx = i;
			pagecount = 1;
			pfn = this_pfn;
		} else {
			pagecount++;
		}
	}
	return setcount;
}