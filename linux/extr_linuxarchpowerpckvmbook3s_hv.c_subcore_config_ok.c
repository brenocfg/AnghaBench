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
 int /*<<< orphan*/  CPU_FTR_ARCH_300 ; 
 int MAX_SMT_THREADS ; 
 int MAX_SUBCORES ; 
 scalar_t__ cpu_has_feature (int /*<<< orphan*/ ) ; 
 int dynamic_mt_modes ; 
 int roundup_pow_of_two (int) ; 
 int threads_per_subcore ; 

__attribute__((used)) static bool subcore_config_ok(int n_subcores, int n_threads)
{
	/*
	 * POWER9 "SMT4" cores are permanently in what is effectively a 4-way
	 * split-core mode, with one thread per subcore.
	 */
	if (cpu_has_feature(CPU_FTR_ARCH_300))
		return n_subcores <= 4 && n_threads == 1;

	/* On POWER8, can only dynamically split if unsplit to begin with */
	if (n_subcores > 1 && threads_per_subcore < MAX_SMT_THREADS)
		return false;
	if (n_subcores > MAX_SUBCORES)
		return false;
	if (n_subcores > 1) {
		if (!(dynamic_mt_modes & 2))
			n_subcores = 4;
		if (n_subcores > 2 && !(dynamic_mt_modes & 4))
			return false;
	}

	return n_subcores * roundup_pow_of_two(n_threads) <= MAX_SMT_THREADS;
}