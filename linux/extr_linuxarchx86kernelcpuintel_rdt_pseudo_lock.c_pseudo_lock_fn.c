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
typedef  int u32 ;
struct rdtgroup {int closid; struct pseudo_lock_region* plr; } ;
struct pseudo_lock_region {unsigned int size; unsigned int line_size; int thread_done; int /*<<< orphan*/  lock_thread_wq; void* kmem; } ;
struct TYPE_2__ {int /*<<< orphan*/  cur_rmid; int /*<<< orphan*/  cur_closid; } ;

/* Variables and functions */
 int /*<<< orphan*/  IA32_PQR_ASSOC ; 
 int /*<<< orphan*/  MSR_MISC_FEATURE_CONTROL ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  __wrmsr (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  native_wbinvd () ; 
 TYPE_1__ pqr_state ; 
 int prefetch_disable_bits ; 
 int /*<<< orphan*/  rmb () ; 
 int this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int pseudo_lock_fn(void *_rdtgrp)
{
	struct rdtgroup *rdtgrp = _rdtgrp;
	struct pseudo_lock_region *plr = rdtgrp->plr;
	u32 rmid_p, closid_p;
	unsigned long i;
#ifdef CONFIG_KASAN
	/*
	 * The registers used for local register variables are also used
	 * when KASAN is active. When KASAN is active we use a regular
	 * variable to ensure we always use a valid pointer, but the cost
	 * is that this variable will enter the cache through evicting the
	 * memory we are trying to lock into the cache. Thus expect lower
	 * pseudo-locking success rate when KASAN is active.
	 */
	unsigned int line_size;
	unsigned int size;
	void *mem_r;
#else
	register unsigned int line_size asm("esi");
	register unsigned int size asm("edi");
#ifdef CONFIG_X86_64
	register void *mem_r asm("rbx");
#else
	register void *mem_r asm("ebx");
#endif /* CONFIG_X86_64 */
#endif /* CONFIG_KASAN */

	/*
	 * Make sure none of the allocated memory is cached. If it is we
	 * will get a cache hit in below loop from outside of pseudo-locked
	 * region.
	 * wbinvd (as opposed to clflush/clflushopt) is required to
	 * increase likelihood that allocated cache portion will be filled
	 * with associated memory.
	 */
	native_wbinvd();

	/*
	 * Always called with interrupts enabled. By disabling interrupts
	 * ensure that we will not be preempted during this critical section.
	 */
	local_irq_disable();

	/*
	 * Call wrmsr and rdmsr as directly as possible to avoid tracing
	 * clobbering local register variables or affecting cache accesses.
	 *
	 * Disable the hardware prefetcher so that when the end of the memory
	 * being pseudo-locked is reached the hardware will not read beyond
	 * the buffer and evict pseudo-locked memory read earlier from the
	 * cache.
	 */
	__wrmsr(MSR_MISC_FEATURE_CONTROL, prefetch_disable_bits, 0x0);
	closid_p = this_cpu_read(pqr_state.cur_closid);
	rmid_p = this_cpu_read(pqr_state.cur_rmid);
	mem_r = plr->kmem;
	size = plr->size;
	line_size = plr->line_size;
	/*
	 * Critical section begin: start by writing the closid associated
	 * with the capacity bitmask of the cache region being
	 * pseudo-locked followed by reading of kernel memory to load it
	 * into the cache.
	 */
	__wrmsr(IA32_PQR_ASSOC, rmid_p, rdtgrp->closid);
	/*
	 * Cache was flushed earlier. Now access kernel memory to read it
	 * into cache region associated with just activated plr->closid.
	 * Loop over data twice:
	 * - In first loop the cache region is shared with the page walker
	 *   as it populates the paging structure caches (including TLB).
	 * - In the second loop the paging structure caches are used and
	 *   cache region is populated with the memory being referenced.
	 */
	for (i = 0; i < size; i += PAGE_SIZE) {
		/*
		 * Add a barrier to prevent speculative execution of this
		 * loop reading beyond the end of the buffer.
		 */
		rmb();
		asm volatile("mov (%0,%1,1), %%eax\n\t"
			:
			: "r" (mem_r), "r" (i)
			: "%eax", "memory");
	}
	for (i = 0; i < size; i += line_size) {
		/*
		 * Add a barrier to prevent speculative execution of this
		 * loop reading beyond the end of the buffer.
		 */
		rmb();
		asm volatile("mov (%0,%1,1), %%eax\n\t"
			:
			: "r" (mem_r), "r" (i)
			: "%eax", "memory");
	}
	/*
	 * Critical section end: restore closid with capacity bitmask that
	 * does not overlap with pseudo-locked region.
	 */
	__wrmsr(IA32_PQR_ASSOC, rmid_p, closid_p);

	/* Re-enable the hardware prefetcher(s) */
	wrmsr(MSR_MISC_FEATURE_CONTROL, 0x0, 0x0);
	local_irq_enable();

	plr->thread_done = 1;
	wake_up_interruptible(&plr->lock_thread_wq);
	return 0;
}