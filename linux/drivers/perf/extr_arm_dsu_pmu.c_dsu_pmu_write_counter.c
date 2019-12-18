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
struct TYPE_3__ {int idx; } ;
struct perf_event {TYPE_2__* pmu; TYPE_1__ hw; } ;
struct dsu_pmu {int /*<<< orphan*/  pmu_lock; int /*<<< orphan*/  associated_cpus; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DSU_PMU_IDX_CYCLE_COUNTER ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  __dsu_pmu_write_counter (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __dsu_pmu_write_pmccntr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_test_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dsu_pmu_counter_valid (struct dsu_pmu*,int) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 struct dsu_pmu* to_dsu_pmu (TYPE_2__*) ; 

__attribute__((used)) static void dsu_pmu_write_counter(struct perf_event *event, u64 val)
{
	unsigned long flags;
	struct dsu_pmu *dsu_pmu = to_dsu_pmu(event->pmu);
	int idx = event->hw.idx;

	if (WARN_ON(!cpumask_test_cpu(smp_processor_id(),
			 &dsu_pmu->associated_cpus)))
		return;

	if (!dsu_pmu_counter_valid(dsu_pmu, idx)) {
		dev_err(event->pmu->dev,
			"writing to invalid counter %d\n", idx);
		return;
	}

	raw_spin_lock_irqsave(&dsu_pmu->pmu_lock, flags);
	if (idx == DSU_PMU_IDX_CYCLE_COUNTER)
		__dsu_pmu_write_pmccntr(val);
	else
		__dsu_pmu_write_counter(idx, val);
	raw_spin_unlock_irqrestore(&dsu_pmu->pmu_lock, flags);
}