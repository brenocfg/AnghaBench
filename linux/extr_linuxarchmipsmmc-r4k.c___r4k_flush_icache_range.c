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
struct flush_icache_range_args {unsigned long start; unsigned long end; int type; int user; } ;

/* Variables and functions */
 int R4K_HIT ; 
 int R4K_INDEX ; 
 int /*<<< orphan*/  cpu_has_ic_fills_f_dc ; 
 scalar_t__ dcache_size ; 
 unsigned long icache_size ; 
 int /*<<< orphan*/  instruction_hazard () ; 
 int /*<<< orphan*/  local_r4k_flush_icache_range_ipi ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  r4k_on_each_cpu (int,int /*<<< orphan*/ ,struct flush_icache_range_args*) ; 
 scalar_t__ r4k_op_needs_ipi (int) ; 

__attribute__((used)) static void __r4k_flush_icache_range(unsigned long start, unsigned long end,
				     bool user)
{
	struct flush_icache_range_args args;
	unsigned long size, cache_size;

	args.start = start;
	args.end = end;
	args.type = R4K_HIT | R4K_INDEX;
	args.user = user;

	/*
	 * Indexed cache ops require an SMP call.
	 * Consider if that can or should be avoided.
	 */
	preempt_disable();
	if (r4k_op_needs_ipi(R4K_INDEX) && !r4k_op_needs_ipi(R4K_HIT)) {
		/*
		 * If address-based cache ops don't require an SMP call, then
		 * use them exclusively for small flushes.
		 */
		size = end - start;
		cache_size = icache_size;
		if (!cpu_has_ic_fills_f_dc) {
			size *= 2;
			cache_size += dcache_size;
		}
		if (size <= cache_size)
			args.type &= ~R4K_INDEX;
	}
	r4k_on_each_cpu(args.type, local_r4k_flush_icache_range_ipi, &args);
	preempt_enable();
	instruction_hazard();
}