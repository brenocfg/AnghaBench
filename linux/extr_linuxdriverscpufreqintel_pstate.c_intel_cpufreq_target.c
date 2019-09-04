#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cpufreq_policy {size_t cpu; int /*<<< orphan*/  cur; } ;
struct cpufreq_freqs {unsigned int new; int /*<<< orphan*/  old; } ;
struct TYPE_3__ {int scaling; int current_pstate; } ;
struct cpudata {TYPE_1__ pstate; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* get_val ) (struct cpudata*,int) ;} ;

/* Variables and functions */
#define  CPUFREQ_RELATION_H 129 
#define  CPUFREQ_RELATION_L 128 
 int DIV_ROUND_CLOSEST (int,int) ; 
 int DIV_ROUND_UP (unsigned int,int) ; 
 int /*<<< orphan*/  INTEL_PSTATE_TRACE_TARGET ; 
 int /*<<< orphan*/  MSR_IA32_PERF_CTL ; 
 struct cpudata** all_cpu_data ; 
 int /*<<< orphan*/  cpufreq_freq_transition_begin (struct cpufreq_policy*,struct cpufreq_freqs*) ; 
 int /*<<< orphan*/  cpufreq_freq_transition_end (struct cpufreq_policy*,struct cpufreq_freqs*,int) ; 
 int /*<<< orphan*/  intel_cpufreq_trace (struct cpudata*,int /*<<< orphan*/ ,int) ; 
 int intel_pstate_prepare_request (struct cpudata*,int) ; 
 TYPE_2__ pstate_funcs ; 
 int /*<<< orphan*/  stub1 (struct cpudata*,int) ; 
 int /*<<< orphan*/  update_turbo_state () ; 
 int /*<<< orphan*/  wrmsrl_on_cpu (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int intel_cpufreq_target(struct cpufreq_policy *policy,
				unsigned int target_freq,
				unsigned int relation)
{
	struct cpudata *cpu = all_cpu_data[policy->cpu];
	struct cpufreq_freqs freqs;
	int target_pstate, old_pstate;

	update_turbo_state();

	freqs.old = policy->cur;
	freqs.new = target_freq;

	cpufreq_freq_transition_begin(policy, &freqs);
	switch (relation) {
	case CPUFREQ_RELATION_L:
		target_pstate = DIV_ROUND_UP(freqs.new, cpu->pstate.scaling);
		break;
	case CPUFREQ_RELATION_H:
		target_pstate = freqs.new / cpu->pstate.scaling;
		break;
	default:
		target_pstate = DIV_ROUND_CLOSEST(freqs.new, cpu->pstate.scaling);
		break;
	}
	target_pstate = intel_pstate_prepare_request(cpu, target_pstate);
	old_pstate = cpu->pstate.current_pstate;
	if (target_pstate != cpu->pstate.current_pstate) {
		cpu->pstate.current_pstate = target_pstate;
		wrmsrl_on_cpu(policy->cpu, MSR_IA32_PERF_CTL,
			      pstate_funcs.get_val(cpu, target_pstate));
	}
	freqs.new = target_pstate * cpu->pstate.scaling;
	intel_cpufreq_trace(cpu, INTEL_PSTATE_TRACE_TARGET, old_pstate);
	cpufreq_freq_transition_end(policy, &freqs, false);

	return 0;
}