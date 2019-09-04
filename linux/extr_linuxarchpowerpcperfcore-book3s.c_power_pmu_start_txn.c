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
struct pmu {int dummy; } ;
struct cpu_hw_events {unsigned int txn_flags; int /*<<< orphan*/  n_events; int /*<<< orphan*/  n_txn_start; } ;

/* Variables and functions */
 unsigned int PERF_PMU_TXN_ADD ; 
 int /*<<< orphan*/  WARN_ON_ONCE (unsigned int) ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 int /*<<< orphan*/  perf_pmu_disable (struct pmu*) ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void power_pmu_start_txn(struct pmu *pmu, unsigned int txn_flags)
{
	struct cpu_hw_events *cpuhw = this_cpu_ptr(&cpu_hw_events);

	WARN_ON_ONCE(cpuhw->txn_flags);		/* txn already in flight */

	cpuhw->txn_flags = txn_flags;
	if (txn_flags & ~PERF_PMU_TXN_ADD)
		return;

	perf_pmu_disable(pmu);
	cpuhw->n_txn_start = cpuhw->n_events;
}