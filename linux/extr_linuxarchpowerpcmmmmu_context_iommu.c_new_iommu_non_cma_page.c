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
typedef  int gfp_t ;

/* Variables and functions */
 int GFP_USER ; 
 scalar_t__ PageCompound (struct page*) ; 
 scalar_t__ PageHighMem (struct page*) ; 
 int __GFP_HIGHMEM ; 
 int __GFP_NORETRY ; 
 int __GFP_NOWARN ; 
 struct page* alloc_page (int) ; 

struct page *new_iommu_non_cma_page(struct page *page, unsigned long private)
{
	gfp_t gfp_mask = GFP_USER;
	struct page *new_page;

	if (PageCompound(page))
		return NULL;

	if (PageHighMem(page))
		gfp_mask |= __GFP_HIGHMEM;

	/*
	 * We don't want the allocation to force an OOM if possibe
	 */
	new_page = alloc_page(gfp_mask | __GFP_NORETRY | __GFP_NOWARN);
	return new_page;
}