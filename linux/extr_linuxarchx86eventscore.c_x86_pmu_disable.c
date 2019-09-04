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
struct pmu {int dummy; } ;
struct cpu_hw_events {scalar_t__ enabled; scalar_t__ n_added; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* disable_all ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 int /*<<< orphan*/  stub1 () ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 TYPE_1__ x86_pmu ; 
 int /*<<< orphan*/  x86_pmu_initialized () ; 

__attribute__((used)) static void x86_pmu_disable(struct pmu *pmu)
{
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);

	if (!x86_pmu_initialized())
		return;

	if (!cpuc->enabled)
		return;

	cpuc->n_added = 0;
	cpuc->enabled = 0;
	barrier();

	x86_pmu.disable_all();
}