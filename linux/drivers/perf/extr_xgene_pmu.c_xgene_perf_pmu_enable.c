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
struct xgene_pmu_dev {int /*<<< orphan*/  max_counters; int /*<<< orphan*/  cntr_assign_mask; struct xgene_pmu* parent; } ;
struct xgene_pmu {TYPE_1__* ops; } ;
struct pmu {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* start_counters ) (struct xgene_pmu_dev*) ;} ;

/* Variables and functions */
 int bitmap_weight (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct xgene_pmu_dev*) ; 
 struct xgene_pmu_dev* to_pmu_dev (struct pmu*) ; 

__attribute__((used)) static void xgene_perf_pmu_enable(struct pmu *pmu)
{
	struct xgene_pmu_dev *pmu_dev = to_pmu_dev(pmu);
	struct xgene_pmu *xgene_pmu = pmu_dev->parent;
	int enabled = bitmap_weight(pmu_dev->cntr_assign_mask,
			pmu_dev->max_counters);

	if (!enabled)
		return;

	xgene_pmu->ops->start_counters(pmu_dev);
}