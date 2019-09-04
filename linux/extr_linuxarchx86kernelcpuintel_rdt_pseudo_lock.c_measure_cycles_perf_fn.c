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
struct pseudo_lock_region {unsigned int size; unsigned int line_size; int thread_done; int /*<<< orphan*/  lock_thread_wq; void* kmem; } ;
struct TYPE_2__ {int x86_model; } ;

/* Variables and functions */
#define  INTEL_FAM6_ATOM_GEMINI_LAKE 130 
#define  INTEL_FAM6_ATOM_GOLDMONT 129 
#define  INTEL_FAM6_BROADWELL_X 128 
 scalar_t__ MSR_ARCH_PERFMON_EVENTSEL0 ; 
 scalar_t__ MSR_ARCH_PERFMON_PERFCTR0 ; 
 int /*<<< orphan*/  MSR_MISC_FEATURE_CONTROL ; 
 int /*<<< orphan*/  __wrmsr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ boot_cpu_data ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 unsigned long long native_read_pmc (int) ; 
 int /*<<< orphan*/  prefetch_disable_bits ; 
 int /*<<< orphan*/  pseudo_wrmsrl_notrace (scalar_t__,int) ; 
 int /*<<< orphan*/  trace_pseudo_lock_l2 (unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  trace_pseudo_lock_l3 (unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int measure_cycles_perf_fn(void *_plr)
{
	unsigned long long l3_hits = 0, l3_miss = 0;
	u64 l3_hit_bits = 0, l3_miss_bits = 0;
	struct pseudo_lock_region *plr = _plr;
	unsigned long long l2_hits, l2_miss;
	u64 l2_hit_bits, l2_miss_bits;
	unsigned long i;
#ifdef CONFIG_KASAN
	/*
	 * The registers used for local register variables are also used
	 * when KASAN is active. When KASAN is active we use regular variables
	 * at the cost of including cache access latency to these variables
	 * in the measurements.
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
	 * Non-architectural event for the Goldmont Microarchitecture
	 * from Intel x86 Architecture Software Developer Manual (SDM):
	 * MEM_LOAD_UOPS_RETIRED D1H (event number)
	 * Umask values:
	 *     L1_HIT   01H
	 *     L2_HIT   02H
	 *     L1_MISS  08H
	 *     L2_MISS  10H
	 *
	 * On Broadwell Microarchitecture the MEM_LOAD_UOPS_RETIRED event
	 * has two "no fix" errata associated with it: BDM35 and BDM100. On
	 * this platform we use the following events instead:
	 *  L2_RQSTS 24H (Documented in https://download.01.org/perfmon/BDW/)
	 *       REFERENCES FFH
	 *       MISS       3FH
	 *  LONGEST_LAT_CACHE 2EH (Documented in SDM)
	 *       REFERENCE 4FH
	 *       MISS      41H
	 */

	/*
	 * Start by setting flags for IA32_PERFEVTSELx:
	 *     OS  (Operating system mode)  0x2
	 *     INT (APIC interrupt enable)  0x10
	 *     EN  (Enable counter)         0x40
	 *
	 * Then add the Umask value and event number to select performance
	 * event.
	 */

	switch (boot_cpu_data.x86_model) {
	case INTEL_FAM6_ATOM_GOLDMONT:
	case INTEL_FAM6_ATOM_GEMINI_LAKE:
		l2_hit_bits = (0x52ULL << 16) | (0x2 << 8) | 0xd1;
		l2_miss_bits = (0x52ULL << 16) | (0x10 << 8) | 0xd1;
		break;
	case INTEL_FAM6_BROADWELL_X:
		/* On BDW the l2_hit_bits count references, not hits */
		l2_hit_bits = (0x52ULL << 16) | (0xff << 8) | 0x24;
		l2_miss_bits = (0x52ULL << 16) | (0x3f << 8) | 0x24;
		/* On BDW the l3_hit_bits count references, not hits */
		l3_hit_bits = (0x52ULL << 16) | (0x4f << 8) | 0x2e;
		l3_miss_bits = (0x52ULL << 16) | (0x41 << 8) | 0x2e;
		break;
	default:
		goto out;
	}

	local_irq_disable();
	/*
	 * Call wrmsr direcly to avoid the local register variables from
	 * being overwritten due to reordering of their assignment with
	 * the wrmsr calls.
	 */
	__wrmsr(MSR_MISC_FEATURE_CONTROL, prefetch_disable_bits, 0x0);
	/* Disable events and reset counters */
	pseudo_wrmsrl_notrace(MSR_ARCH_PERFMON_EVENTSEL0, 0x0);
	pseudo_wrmsrl_notrace(MSR_ARCH_PERFMON_EVENTSEL0 + 1, 0x0);
	pseudo_wrmsrl_notrace(MSR_ARCH_PERFMON_PERFCTR0, 0x0);
	pseudo_wrmsrl_notrace(MSR_ARCH_PERFMON_PERFCTR0 + 1, 0x0);
	if (l3_hit_bits > 0) {
		pseudo_wrmsrl_notrace(MSR_ARCH_PERFMON_EVENTSEL0 + 2, 0x0);
		pseudo_wrmsrl_notrace(MSR_ARCH_PERFMON_EVENTSEL0 + 3, 0x0);
		pseudo_wrmsrl_notrace(MSR_ARCH_PERFMON_PERFCTR0 + 2, 0x0);
		pseudo_wrmsrl_notrace(MSR_ARCH_PERFMON_PERFCTR0 + 3, 0x0);
	}
	/* Set and enable the L2 counters */
	pseudo_wrmsrl_notrace(MSR_ARCH_PERFMON_EVENTSEL0, l2_hit_bits);
	pseudo_wrmsrl_notrace(MSR_ARCH_PERFMON_EVENTSEL0 + 1, l2_miss_bits);
	if (l3_hit_bits > 0) {
		pseudo_wrmsrl_notrace(MSR_ARCH_PERFMON_EVENTSEL0 + 2,
				      l3_hit_bits);
		pseudo_wrmsrl_notrace(MSR_ARCH_PERFMON_EVENTSEL0 + 3,
				      l3_miss_bits);
	}
	mem_r = plr->kmem;
	size = plr->size;
	line_size = plr->line_size;
	for (i = 0; i < size; i += line_size) {
		asm volatile("mov (%0,%1,1), %%eax\n\t"
			     :
			     : "r" (mem_r), "r" (i)
			     : "%eax", "memory");
	}
	/*
	 * Call wrmsr directly (no tracing) to not influence
	 * the cache access counters as they are disabled.
	 */
	pseudo_wrmsrl_notrace(MSR_ARCH_PERFMON_EVENTSEL0,
			      l2_hit_bits & ~(0x40ULL << 16));
	pseudo_wrmsrl_notrace(MSR_ARCH_PERFMON_EVENTSEL0 + 1,
			      l2_miss_bits & ~(0x40ULL << 16));
	if (l3_hit_bits > 0) {
		pseudo_wrmsrl_notrace(MSR_ARCH_PERFMON_EVENTSEL0 + 2,
				      l3_hit_bits & ~(0x40ULL << 16));
		pseudo_wrmsrl_notrace(MSR_ARCH_PERFMON_EVENTSEL0 + 3,
				      l3_miss_bits & ~(0x40ULL << 16));
	}
	l2_hits = native_read_pmc(0);
	l2_miss = native_read_pmc(1);
	if (l3_hit_bits > 0) {
		l3_hits = native_read_pmc(2);
		l3_miss = native_read_pmc(3);
	}
	wrmsr(MSR_MISC_FEATURE_CONTROL, 0x0, 0x0);
	local_irq_enable();
	/*
	 * On BDW we count references and misses, need to adjust. Sometimes
	 * the "hits" counter is a bit more than the references, for
	 * example, x references but x + 1 hits. To not report invalid
	 * hit values in this case we treat that as misses eaqual to
	 * references.
	 */
	if (boot_cpu_data.x86_model == INTEL_FAM6_BROADWELL_X)
		l2_hits -= (l2_miss > l2_hits ? l2_hits : l2_miss);
	trace_pseudo_lock_l2(l2_hits, l2_miss);
	if (l3_hit_bits > 0) {
		if (boot_cpu_data.x86_model == INTEL_FAM6_BROADWELL_X)
			l3_hits -= (l3_miss > l3_hits ? l3_hits : l3_miss);
		trace_pseudo_lock_l3(l3_hits, l3_miss);
	}

out:
	plr->thread_done = 1;
	wake_up_interruptible(&plr->lock_thread_wq);
	return 0;
}