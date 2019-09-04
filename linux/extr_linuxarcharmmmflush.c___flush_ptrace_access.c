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

/* Variables and functions */
 unsigned int FLAG_PA_CORE_IN_MM ; 
 unsigned int FLAG_PA_IS_EXEC ; 
 int /*<<< orphan*/  __cpuc_coherent_kern_range (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  __flush_icache_all () ; 
 scalar_t__ cache_is_vipt_aliasing () ; 
 scalar_t__ cache_is_vivt () ; 
 scalar_t__ cache_ops_need_broadcast () ; 
 int /*<<< orphan*/  flush_icache_alias (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  flush_pfn_alias (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  flush_ptrace_access_other ; 
 scalar_t__ icache_is_vipt_aliasing () ; 
 int /*<<< orphan*/  page_to_pfn (struct page*) ; 
 int /*<<< orphan*/  smp_call_function (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline
void __flush_ptrace_access(struct page *page, unsigned long uaddr, void *kaddr,
			   unsigned long len, unsigned int flags)
{
	if (cache_is_vivt()) {
		if (flags & FLAG_PA_CORE_IN_MM) {
			unsigned long addr = (unsigned long)kaddr;
			__cpuc_coherent_kern_range(addr, addr + len);
		}
		return;
	}

	if (cache_is_vipt_aliasing()) {
		flush_pfn_alias(page_to_pfn(page), uaddr);
		__flush_icache_all();
		return;
	}

	/* VIPT non-aliasing D-cache */
	if (flags & FLAG_PA_IS_EXEC) {
		unsigned long addr = (unsigned long)kaddr;
		if (icache_is_vipt_aliasing())
			flush_icache_alias(page_to_pfn(page), uaddr, len);
		else
			__cpuc_coherent_kern_range(addr, addr + len);
		if (cache_ops_need_broadcast())
			smp_call_function(flush_ptrace_access_other,
					  NULL, 1);
	}
}