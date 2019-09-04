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
typedef  size_t u32 ;
struct page {int dummy; } ;
struct its_baser {int val; size_t psz; scalar_t__* base; int /*<<< orphan*/  order; } ;
typedef  scalar_t__ __le64 ;

/* Variables and functions */
 int GFP_KERNEL ; 
 size_t GITS_BASER_ENTRY_SIZE (int) ; 
 int GITS_BASER_INDIRECT ; 
 int GITS_BASER_SHAREABILITY_MASK ; 
 int GITS_BASER_VALID ; 
 size_t GITS_LVL1_ENTRY_SIZE ; 
 size_t PAGE_ORDER_TO_SIZE (int /*<<< orphan*/ ) ; 
 int __GFP_ZERO ; 
 struct page* alloc_pages (int,int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_to_le64 (int) ; 
 int /*<<< orphan*/  dsb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (size_t) ; 
 int /*<<< orphan*/  gic_flush_dcache_to_poc (scalar_t__*,size_t) ; 
 size_t ilog2 (size_t) ; 
 scalar_t__* page_address (struct page*) ; 
 int page_to_phys (struct page*) ; 
 int /*<<< orphan*/  sy ; 

__attribute__((used)) static bool its_alloc_table_entry(struct its_baser *baser, u32 id)
{
	struct page *page;
	u32 esz, idx;
	__le64 *table;

	/* Don't allow device id that exceeds single, flat table limit */
	esz = GITS_BASER_ENTRY_SIZE(baser->val);
	if (!(baser->val & GITS_BASER_INDIRECT))
		return (id < (PAGE_ORDER_TO_SIZE(baser->order) / esz));

	/* Compute 1st level table index & check if that exceeds table limit */
	idx = id >> ilog2(baser->psz / esz);
	if (idx >= (PAGE_ORDER_TO_SIZE(baser->order) / GITS_LVL1_ENTRY_SIZE))
		return false;

	table = baser->base;

	/* Allocate memory for 2nd level table */
	if (!table[idx]) {
		page = alloc_pages(GFP_KERNEL | __GFP_ZERO, get_order(baser->psz));
		if (!page)
			return false;

		/* Flush Lvl2 table to PoC if hw doesn't support coherency */
		if (!(baser->val & GITS_BASER_SHAREABILITY_MASK))
			gic_flush_dcache_to_poc(page_address(page), baser->psz);

		table[idx] = cpu_to_le64(page_to_phys(page) | GITS_BASER_VALID);

		/* Flush Lvl1 entry to PoC if hw doesn't support coherency */
		if (!(baser->val & GITS_BASER_SHAREABILITY_MASK))
			gic_flush_dcache_to_poc(table + idx, GITS_LVL1_ENTRY_SIZE);

		/* Ensure updated table contents are visible to ITS hardware */
		dsb(sy);
	}

	return true;
}