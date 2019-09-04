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
struct cpu_hw_events {int txn_flags; int n_events; int /*<<< orphan*/  events; int /*<<< orphan*/  event; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int PERF_PMU_TXN_ADD ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ check_excludes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 int /*<<< orphan*/  perf_pmu_enable (struct pmu*) ; 
 scalar_t__ sparc_check_constraints (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sparc_pmu ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sparc_pmu_commit_txn(struct pmu *pmu)
{
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	int n;

	if (!sparc_pmu)
		return -EINVAL;

	WARN_ON_ONCE(!cpuc->txn_flags);	/* no txn in flight */

	if (cpuc->txn_flags & ~PERF_PMU_TXN_ADD) {
		cpuc->txn_flags = 0;
		return 0;
	}

	n = cpuc->n_events;
	if (check_excludes(cpuc->event, 0, n))
		return -EINVAL;
	if (sparc_check_constraints(cpuc->event, cpuc->events, n))
		return -EAGAIN;

	cpuc->txn_flags = 0;
	perf_pmu_enable(pmu);
	return 0;
}