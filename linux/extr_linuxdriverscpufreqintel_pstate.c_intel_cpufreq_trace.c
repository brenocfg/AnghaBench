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
struct sample {int /*<<< orphan*/  tsc; int /*<<< orphan*/  aperf; int /*<<< orphan*/  mperf; } ;
struct TYPE_2__ {int /*<<< orphan*/  current_pstate; } ;
struct cpudata {int iowait_boost; TYPE_1__ pstate; struct sample sample; } ;

/* Variables and functions */
 int /*<<< orphan*/  fp_toint (int) ; 
 int /*<<< orphan*/  get_avg_frequency (struct cpudata*) ; 
 int /*<<< orphan*/  intel_pstate_sample (struct cpudata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  trace_pstate_sample (unsigned int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_pstate_sample_enabled () ; 

__attribute__((used)) static void intel_cpufreq_trace(struct cpudata *cpu, unsigned int trace_type, int old_pstate)
{
	struct sample *sample;

	if (!trace_pstate_sample_enabled())
		return;

	if (!intel_pstate_sample(cpu, ktime_get()))
		return;

	sample = &cpu->sample;
	trace_pstate_sample(trace_type,
		0,
		old_pstate,
		cpu->pstate.current_pstate,
		sample->mperf,
		sample->aperf,
		sample->tsc,
		get_avg_frequency(cpu),
		fp_toint(cpu->iowait_boost * 100));
}