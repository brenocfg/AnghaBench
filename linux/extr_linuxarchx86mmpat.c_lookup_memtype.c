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
typedef  int u64 ;
struct page {int dummy; } ;
struct memtype {int type; } ;
typedef  enum page_cache_mode { ____Placeholder_page_cache_mode } page_cache_mode ;
struct TYPE_2__ {scalar_t__ (* is_untracked_pat_range ) (int,scalar_t__) ;} ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 
 int _PAGE_CACHE_MODE_UC_MINUS ; 
 int _PAGE_CACHE_MODE_WB ; 
 int get_page_memtype (struct page*) ; 
 int /*<<< orphan*/  memtype_lock ; 
 scalar_t__ pat_pagerange_is_ram (int,scalar_t__) ; 
 struct page* pfn_to_page (int) ; 
 struct memtype* rbt_memtype_lookup (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (int,scalar_t__) ; 
 TYPE_1__ x86_platform ; 

__attribute__((used)) static enum page_cache_mode lookup_memtype(u64 paddr)
{
	enum page_cache_mode rettype = _PAGE_CACHE_MODE_WB;
	struct memtype *entry;

	if (x86_platform.is_untracked_pat_range(paddr, paddr + PAGE_SIZE))
		return rettype;

	if (pat_pagerange_is_ram(paddr, paddr + PAGE_SIZE)) {
		struct page *page;

		page = pfn_to_page(paddr >> PAGE_SHIFT);
		return get_page_memtype(page);
	}

	spin_lock(&memtype_lock);

	entry = rbt_memtype_lookup(paddr);
	if (entry != NULL)
		rettype = entry->type;
	else
		rettype = _PAGE_CACHE_MODE_UC_MINUS;

	spin_unlock(&memtype_lock);
	return rettype;
}