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
struct cpufreq_freqs {unsigned long new; } ;

/* Variables and functions */
 int /*<<< orphan*/  X86_FEATURE_CONSTANT_TSC ; 
 int /*<<< orphan*/  __this_cpu_write (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  boot_cpu_has (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_tsc_khz ; 
 unsigned long cpufreq_quick_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_smp_processor_id () ; 
 unsigned long tsc_khz ; 

__attribute__((used)) static void tsc_khz_changed(void *data)
{
	struct cpufreq_freqs *freq = data;
	unsigned long khz = 0;

	if (data)
		khz = freq->new;
	else if (!boot_cpu_has(X86_FEATURE_CONSTANT_TSC))
		khz = cpufreq_quick_get(raw_smp_processor_id());
	if (!khz)
		khz = tsc_khz;
	__this_cpu_write(cpu_tsc_khz, khz);
}