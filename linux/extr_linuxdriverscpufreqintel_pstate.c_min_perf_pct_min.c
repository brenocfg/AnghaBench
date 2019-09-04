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
struct TYPE_2__ {int turbo_pstate; int min_pstate; } ;
struct cpudata {TYPE_1__ pstate; } ;

/* Variables and functions */
 struct cpudata** all_cpu_data ; 

__attribute__((used)) static int min_perf_pct_min(void)
{
	struct cpudata *cpu = all_cpu_data[0];
	int turbo_pstate = cpu->pstate.turbo_pstate;

	return turbo_pstate ?
		(cpu->pstate.min_pstate * 100 / turbo_pstate) : 0;
}