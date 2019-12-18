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
typedef  int /*<<< orphan*/  u32 ;
struct pmu {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  used_mask; } ;
struct dsu_pmu {int /*<<< orphan*/  pmu_lock; TYPE_1__ hw_events; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLUSTERPMCR_E ; 
 int /*<<< orphan*/  DSU_PMU_MAX_HW_CNTRS ; 
 int /*<<< orphan*/  __dsu_pmu_read_pmcr () ; 
 int /*<<< orphan*/  __dsu_pmu_write_pmcr (int /*<<< orphan*/ ) ; 
 scalar_t__ bitmap_empty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct dsu_pmu* to_dsu_pmu (struct pmu*) ; 

__attribute__((used)) static void dsu_pmu_enable(struct pmu *pmu)
{
	u32 pmcr;
	unsigned long flags;
	struct dsu_pmu *dsu_pmu = to_dsu_pmu(pmu);

	/* If no counters are added, skip enabling the PMU */
	if (bitmap_empty(dsu_pmu->hw_events.used_mask, DSU_PMU_MAX_HW_CNTRS))
		return;

	raw_spin_lock_irqsave(&dsu_pmu->pmu_lock, flags);
	pmcr = __dsu_pmu_read_pmcr();
	pmcr |= CLUSTERPMCR_E;
	__dsu_pmu_write_pmcr(pmcr);
	raw_spin_unlock_irqrestore(&dsu_pmu->pmu_lock, flags);
}