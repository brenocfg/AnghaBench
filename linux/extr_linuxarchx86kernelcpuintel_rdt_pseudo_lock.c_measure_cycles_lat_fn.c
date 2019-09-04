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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct pseudo_lock_region {unsigned long size; int thread_done; int /*<<< orphan*/  lock_thread_wq; void* kmem; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_MISC_FEATURE_CONTROL ; 
 int /*<<< orphan*/  __wrmsr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  prefetch_disable_bits ; 
 scalar_t__ rdtsc_ordered () ; 
 int /*<<< orphan*/  trace_pseudo_lock_mem_latency (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int measure_cycles_lat_fn(void *_plr)
{
	struct pseudo_lock_region *plr = _plr;
	unsigned long i;
	u64 start, end;
#ifdef CONFIG_KASAN
	/*
	 * The registers used for local register variables are also used
	 * when KASAN is active. When KASAN is active we use a regular
	 * variable to ensure we always use a valid pointer to access memory.
	 * The cost is that accessing this pointer, which could be in
	 * cache, will be included in the measurement of memory read latency.
	 */
	void *mem_r;
#else
#ifdef CONFIG_X86_64
	register void *mem_r asm("rbx");
#else
	register void *mem_r asm("ebx");
#endif /* CONFIG_X86_64 */
#endif /* CONFIG_KASAN */

	local_irq_disable();
	/*
	 * The wrmsr call may be reordered with the assignment below it.
	 * Call wrmsr as directly as possible to avoid tracing clobbering
	 * local register variable used for memory pointer.
	 */
	__wrmsr(MSR_MISC_FEATURE_CONTROL, prefetch_disable_bits, 0x0);
	mem_r = plr->kmem;
	/*
	 * Dummy execute of the time measurement to load the needed
	 * instructions into the L1 instruction cache.
	 */
	start = rdtsc_ordered();
	for (i = 0; i < plr->size; i += 32) {
		start = rdtsc_ordered();
		asm volatile("mov (%0,%1,1), %%eax\n\t"
			     :
			     : "r" (mem_r), "r" (i)
			     : "%eax", "memory");
		end = rdtsc_ordered();
		trace_pseudo_lock_mem_latency((u32)(end - start));
	}
	wrmsr(MSR_MISC_FEATURE_CONTROL, 0x0, 0x0);
	local_irq_enable();
	plr->thread_done = 1;
	wake_up_interruptible(&plr->lock_thread_wq);
	return 0;
}