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
struct TYPE_4__ {int /*<<< orphan*/  id; int /*<<< orphan*/  pmu; scalar_t__ base; int /*<<< orphan*/  node; } ;
struct arm_ccn {int num_xps; TYPE_2__ dt; TYPE_1__* xp; scalar_t__ irq; } ;
struct TYPE_3__ {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ CCN_DT_PMCR ; 
 scalar_t__ CCN_XP_DT_CONTROL ; 
 int /*<<< orphan*/  CPUHP_AP_PERF_ARM_CCN_ONLINE ; 
 int /*<<< orphan*/  arm_ccn_pmu_ida ; 
 int /*<<< orphan*/  cpuhp_state_remove_instance_nocalls (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_affinity_hint (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_pmu_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void arm_ccn_pmu_cleanup(struct arm_ccn *ccn)
{
	int i;

	cpuhp_state_remove_instance_nocalls(CPUHP_AP_PERF_ARM_CCN_ONLINE,
					    &ccn->dt.node);
	if (ccn->irq)
		irq_set_affinity_hint(ccn->irq, NULL);
	for (i = 0; i < ccn->num_xps; i++)
		writel(0, ccn->xp[i].base + CCN_XP_DT_CONTROL);
	writel(0, ccn->dt.base + CCN_DT_PMCR);
	perf_pmu_unregister(&ccn->dt.pmu);
	ida_simple_remove(&arm_ccn_pmu_ida, ccn->dt.id);
}