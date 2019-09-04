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

/* Variables and functions */
 unsigned long FIXADDR_START ; 
 unsigned long PAGE_MASK ; 
 int kmap_atomic_idx () ; 
 int /*<<< orphan*/  kmap_atomic_idx_pop () ; 
 int /*<<< orphan*/  pagefault_enable () ; 
 int /*<<< orphan*/  preempt_enable () ; 

void __kunmap_atomic(void *kvaddr)
{
	unsigned long vaddr = (unsigned long) kvaddr & PAGE_MASK;
	int type;

	if (vaddr < FIXADDR_START) { // FIXME
		pagefault_enable();
		preempt_enable();
		return;
	}

	type = kmap_atomic_idx();

#ifdef CONFIG_DEBUG_HIGHMEM
	{
		unsigned long idx;

		idx = type + KM_TYPE_NR * smp_processor_id();
		BUG_ON(vaddr != __fix_to_virt(FIX_KMAP_BEGIN+idx));

		/* XXX Fix - Anton */
#if 0
		__flush_cache_one(vaddr);
#else
		flush_cache_all();
#endif

		/*
		 * force other mappings to Oops if they'll try to access
		 * this pte without first remap it
		 */
		pte_clear(&init_mm, vaddr, kmap_pte-idx);
		/* XXX Fix - Anton */
#if 0
		__flush_tlb_one(vaddr);
#else
		flush_tlb_all();
#endif
	}
#endif

	kmap_atomic_idx_pop();
	pagefault_enable();
	preempt_enable();
}