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
struct l3cache_pmu {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ L3_M_BC_CR ; 
 struct l3cache_pmu* to_l3cache_pmu (struct pmu*) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void qcom_l3_cache__pmu_disable(struct pmu *pmu)
{
	struct l3cache_pmu *l3pmu = to_l3cache_pmu(pmu);

	writel_relaxed(0, l3pmu->regs + L3_M_BC_CR);

	/* Ensure the basic counter unit is stopped before proceeding */
	wmb();
}