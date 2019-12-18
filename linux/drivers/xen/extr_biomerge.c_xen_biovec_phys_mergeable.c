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
struct bio_vec {scalar_t__ bv_len; scalar_t__ bv_offset; struct page const* bv_page; } ;

/* Variables and functions */
 unsigned long PFN_DOWN (scalar_t__) ; 
 int /*<<< orphan*/  page_to_pfn (struct page const*) ; 
 unsigned long pfn_to_bfn (int /*<<< orphan*/ ) ; 

bool xen_biovec_phys_mergeable(const struct bio_vec *vec1,
			       const struct page *page)
{
#if XEN_PAGE_SIZE == PAGE_SIZE
	unsigned long bfn1 = pfn_to_bfn(page_to_pfn(vec1->bv_page));
	unsigned long bfn2 = pfn_to_bfn(page_to_pfn(page));

	return bfn1 + PFN_DOWN(vec1->bv_offset + vec1->bv_len) == bfn2;
#else
	/*
	 * XXX: Add support for merging bio_vec when using different page
	 * size in Xen and Linux.
	 */
	return false;
#endif
}