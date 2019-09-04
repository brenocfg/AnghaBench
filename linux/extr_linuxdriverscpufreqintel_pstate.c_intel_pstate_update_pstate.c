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
struct TYPE_3__ {int current_pstate; } ;
struct cpudata {TYPE_1__ pstate; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* get_val ) (struct cpudata*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_IA32_PERF_CTL ; 
 TYPE_2__ pstate_funcs ; 
 int /*<<< orphan*/  stub1 (struct cpudata*,int) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_pstate_update_pstate(struct cpudata *cpu, int pstate)
{
	if (pstate == cpu->pstate.current_pstate)
		return;

	cpu->pstate.current_pstate = pstate;
	wrmsrl(MSR_IA32_PERF_CTL, pstate_funcs.get_val(cpu, pstate));
}