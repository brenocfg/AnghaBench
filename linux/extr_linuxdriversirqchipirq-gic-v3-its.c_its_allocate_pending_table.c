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
 int /*<<< orphan*/  LPI_PENDBASE_SZ ; 
 int /*<<< orphan*/  SZ_64K ; 
 int __GFP_ZERO ; 
 struct page* alloc_pages (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gic_flush_dcache_to_poc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 
 int /*<<< orphan*/  u32 ; 

__attribute__((used)) static struct page *its_allocate_pending_table(gfp_t gfp_flags)
{
	struct page *pend_page;
	/*
	 * The pending pages have to be at least 64kB aligned,
	 * hence the 'max(LPI_PENDBASE_SZ, SZ_64K)' below.
	 */
	pend_page = alloc_pages(gfp_flags | __GFP_ZERO,
				get_order(max_t(u32, LPI_PENDBASE_SZ, SZ_64K)));
	if (!pend_page)
		return NULL;

	/* Make sure the GIC will observe the zero-ed page */
	gic_flush_dcache_to_poc(page_address(pend_page), LPI_PENDBASE_SZ);

	return pend_page;
}