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
struct vm_area_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pgprot_t ;
typedef  int /*<<< orphan*/  pfn_t ;
typedef  enum page_cache_mode { ____Placeholder_page_cache_mode } page_cache_mode ;

/* Variables and functions */
 int _PAGE_CACHE_MASK ; 
 int /*<<< orphan*/  __pgprot (int) ; 
 int cachemode2protval (int) ; 
 int lookup_memtype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pat_enabled () ; 
 int /*<<< orphan*/  pfn_t_to_phys (int /*<<< orphan*/ ) ; 
 int pgprot_val (int /*<<< orphan*/ ) ; 

void track_pfn_insert(struct vm_area_struct *vma, pgprot_t *prot, pfn_t pfn)
{
	enum page_cache_mode pcm;

	if (!pat_enabled())
		return;

	/* Set prot based on lookup */
	pcm = lookup_memtype(pfn_t_to_phys(pfn));
	*prot = __pgprot((pgprot_val(*prot) & (~_PAGE_CACHE_MASK)) |
			 cachemode2protval(pcm));
}