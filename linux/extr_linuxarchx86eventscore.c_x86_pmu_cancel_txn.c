#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pmu {int dummy; } ;
struct cpu_hw_events {unsigned int txn_flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  n_txn; int /*<<< orphan*/  n_events; int /*<<< orphan*/  n_added; } ;

/* Variables and functions */
 unsigned int PERF_PMU_TXN_ADD ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __this_cpu_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ cpu_hw_events ; 
 int /*<<< orphan*/  perf_pmu_enable (struct pmu*) ; 
 struct cpu_hw_events* this_cpu_ptr (TYPE_1__*) ; 

__attribute__((used)) static void x86_pmu_cancel_txn(struct pmu *pmu)
{
	unsigned int txn_flags;
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);

	WARN_ON_ONCE(!cpuc->txn_flags);	/* no txn in flight */

	txn_flags = cpuc->txn_flags;
	cpuc->txn_flags = 0;
	if (txn_flags & ~PERF_PMU_TXN_ADD)
		return;

	/*
	 * Truncate collected array by the number of events added in this
	 * transaction. See x86_pmu_add() and x86_pmu_*_txn().
	 */
	__this_cpu_sub(cpu_hw_events.n_added, __this_cpu_read(cpu_hw_events.n_txn));
	__this_cpu_sub(cpu_hw_events.n_events, __this_cpu_read(cpu_hw_events.n_txn));
	perf_pmu_enable(pmu);
}