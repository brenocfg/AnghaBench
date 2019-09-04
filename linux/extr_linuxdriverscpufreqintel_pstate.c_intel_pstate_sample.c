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
typedef  scalar_t__ u64 ;
struct TYPE_2__ {scalar_t__ mperf; scalar_t__ tsc; scalar_t__ aperf; scalar_t__ time; } ;
struct cpudata {scalar_t__ prev_mperf; scalar_t__ prev_tsc; scalar_t__ last_sample_time; scalar_t__ prev_aperf; TYPE_1__ sample; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_IA32_APERF ; 
 int /*<<< orphan*/  MSR_IA32_MPERF ; 
 int /*<<< orphan*/  intel_pstate_calc_avg_perf (struct cpudata*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ rdtsc () ; 

__attribute__((used)) static inline bool intel_pstate_sample(struct cpudata *cpu, u64 time)
{
	u64 aperf, mperf;
	unsigned long flags;
	u64 tsc;

	local_irq_save(flags);
	rdmsrl(MSR_IA32_APERF, aperf);
	rdmsrl(MSR_IA32_MPERF, mperf);
	tsc = rdtsc();
	if (cpu->prev_mperf == mperf || cpu->prev_tsc == tsc) {
		local_irq_restore(flags);
		return false;
	}
	local_irq_restore(flags);

	cpu->last_sample_time = cpu->sample.time;
	cpu->sample.time = time;
	cpu->sample.aperf = aperf;
	cpu->sample.mperf = mperf;
	cpu->sample.tsc =  tsc;
	cpu->sample.aperf -= cpu->prev_aperf;
	cpu->sample.mperf -= cpu->prev_mperf;
	cpu->sample.tsc -= cpu->prev_tsc;

	cpu->prev_aperf = aperf;
	cpu->prev_mperf = mperf;
	cpu->prev_tsc = tsc;
	/*
	 * First time this function is invoked in a given cycle, all of the
	 * previous sample data fields are equal to zero or stale and they must
	 * be populated with meaningful numbers for things to work, so assume
	 * that sample.time will always be reset before setting the utilization
	 * update hook and make the caller skip the sample then.
	 */
	if (cpu->last_sample_time) {
		intel_pstate_calc_avg_perf(cpu);
		return true;
	}
	return false;
}