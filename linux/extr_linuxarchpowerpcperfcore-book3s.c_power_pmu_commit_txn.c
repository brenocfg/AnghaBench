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
struct pmu {int dummy; } ;
struct cpu_hw_events {int txn_flags; long n_events; long n_txn_start; int /*<<< orphan*/ * events; TYPE_2__** event; int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  config; } ;
struct TYPE_4__ {TYPE_1__ hw; } ;

/* Variables and functions */
 int EAGAIN ; 
 int PERF_PMU_TXN_ADD ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ check_excludes (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 int /*<<< orphan*/  perf_pmu_enable (struct pmu*) ; 
 long power_check_constraints (struct cpu_hw_events*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  ppmu ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int power_pmu_commit_txn(struct pmu *pmu)
{
	struct cpu_hw_events *cpuhw;
	long i, n;

	if (!ppmu)
		return -EAGAIN;

	cpuhw = this_cpu_ptr(&cpu_hw_events);
	WARN_ON_ONCE(!cpuhw->txn_flags);	/* no txn in flight */

	if (cpuhw->txn_flags & ~PERF_PMU_TXN_ADD) {
		cpuhw->txn_flags = 0;
		return 0;
	}

	n = cpuhw->n_events;
	if (check_excludes(cpuhw->event, cpuhw->flags, 0, n))
		return -EAGAIN;
	i = power_check_constraints(cpuhw, cpuhw->events, cpuhw->flags, n);
	if (i < 0)
		return -EAGAIN;

	for (i = cpuhw->n_txn_start; i < n; ++i)
		cpuhw->event[i]->hw.config = cpuhw->events[i];

	cpuhw->txn_flags = 0;
	perf_pmu_enable(pmu);
	return 0;
}