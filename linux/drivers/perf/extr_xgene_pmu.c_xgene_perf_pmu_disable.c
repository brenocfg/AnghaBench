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
struct xgene_pmu_dev {struct xgene_pmu* parent; } ;
struct xgene_pmu {TYPE_1__* ops; } ;
struct pmu {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* stop_counters ) (struct xgene_pmu_dev*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct xgene_pmu_dev*) ; 
 struct xgene_pmu_dev* to_pmu_dev (struct pmu*) ; 

__attribute__((used)) static void xgene_perf_pmu_disable(struct pmu *pmu)
{
	struct xgene_pmu_dev *pmu_dev = to_pmu_dev(pmu);
	struct xgene_pmu *xgene_pmu = pmu_dev->parent;

	xgene_pmu->ops->stop_counters(pmu_dev);
}