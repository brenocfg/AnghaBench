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
struct powernv_smp_call_data {void* gpstate_id; void* pstate_id; } ;
struct global_pstate_info {int /*<<< orphan*/  timer; } ;
struct cpufreq_policy {int /*<<< orphan*/  cpu; struct global_pstate_info* driver_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  min; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 void* idx_to_pstate (int /*<<< orphan*/ ) ; 
 TYPE_1__ powernv_pstate_info ; 
 int /*<<< orphan*/  set_pstate ; 
 int /*<<< orphan*/  smp_call_function_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct powernv_smp_call_data*,int) ; 

__attribute__((used)) static void powernv_cpufreq_stop_cpu(struct cpufreq_policy *policy)
{
	struct powernv_smp_call_data freq_data;
	struct global_pstate_info *gpstates = policy->driver_data;

	freq_data.pstate_id = idx_to_pstate(powernv_pstate_info.min);
	freq_data.gpstate_id = idx_to_pstate(powernv_pstate_info.min);
	smp_call_function_single(policy->cpu, set_pstate, &freq_data, 1);
	if (gpstates)
		del_timer_sync(&gpstates->timer);
}