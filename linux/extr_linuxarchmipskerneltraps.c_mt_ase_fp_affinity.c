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

__attribute__((used)) static void mt_ase_fp_affinity(void)
{
#ifdef CONFIG_MIPS_MT_FPAFF
	if (mt_fpemul_threshold > 0 &&
	     ((current->thread.emulated_fp++ > mt_fpemul_threshold))) {
		/*
		 * If there's no FPU present, or if the application has already
		 * restricted the allowed set to exclude any CPUs with FPUs,
		 * we'll skip the procedure.
		 */
		if (cpumask_intersects(&current->cpus_allowed, &mt_fpu_cpumask)) {
			cpumask_t tmask;

			current->thread.user_cpus_allowed
				= current->cpus_allowed;
			cpumask_and(&tmask, &current->cpus_allowed,
				    &mt_fpu_cpumask);
			set_cpus_allowed_ptr(current, &tmask);
			set_thread_flag(TIF_FPUBOUND);
		}
	}
#endif /* CONFIG_MIPS_MT_FPAFF */
}