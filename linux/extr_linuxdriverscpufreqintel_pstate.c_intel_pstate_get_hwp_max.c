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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_4__ {int /*<<< orphan*/  hwp_cap_cached; } ;
struct TYPE_3__ {scalar_t__ no_turbo; } ;

/* Variables and functions */
 int HWP_GUARANTEED_PERF (int /*<<< orphan*/ ) ; 
 int HWP_HIGHEST_PERF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSR_HWP_CAPABILITIES ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__** all_cpu_data ; 
 TYPE_1__ global ; 
 int /*<<< orphan*/  rdmsrl_on_cpu (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void intel_pstate_get_hwp_max(unsigned int cpu, int *phy_max,
				     int *current_max)
{
	u64 cap;

	rdmsrl_on_cpu(cpu, MSR_HWP_CAPABILITIES, &cap);
	WRITE_ONCE(all_cpu_data[cpu]->hwp_cap_cached, cap);
	if (global.no_turbo)
		*current_max = HWP_GUARANTEED_PERF(cap);
	else
		*current_max = HWP_HIGHEST_PERF(cap);

	*phy_max = HWP_HIGHEST_PERF(cap);
}