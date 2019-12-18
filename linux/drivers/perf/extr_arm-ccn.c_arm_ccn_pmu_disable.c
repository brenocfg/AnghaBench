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
struct TYPE_2__ {scalar_t__ base; } ;
struct arm_ccn {TYPE_1__ dt; } ;

/* Variables and functions */
 scalar_t__ CCN_DT_PMCR ; 
 int /*<<< orphan*/  CCN_DT_PMCR__PMU_EN ; 
 struct arm_ccn* pmu_to_arm_ccn (struct pmu*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void arm_ccn_pmu_disable(struct pmu *pmu)
{
	struct arm_ccn *ccn = pmu_to_arm_ccn(pmu);

	u32 val = readl(ccn->dt.base + CCN_DT_PMCR);
	val &= ~CCN_DT_PMCR__PMU_EN;
	writel(val, ccn->dt.base + CCN_DT_PMCR);
}