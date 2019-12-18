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
typedef  int u64 ;
struct perf_event_attr {scalar_t__ type; scalar_t__ freq; scalar_t__ exclude_idle; } ;
struct perf_event {scalar_t__ cpu; TYPE_1__* pmu; struct perf_event_attr attr; } ;
struct arm_spe_pmu {int features; int /*<<< orphan*/  supported_cpus; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EACCES ; 
 int EINVAL ; 
 int ENOENT ; 
 int EOPNOTSUPP ; 
 int SPE_PMU_FEAT_FILT_EVT ; 
 int SPE_PMU_FEAT_FILT_LAT ; 
 int SPE_PMU_FEAT_FILT_TYP ; 
 int /*<<< orphan*/  SYS_PMSCR_EL1_CX_SHIFT ; 
 int /*<<< orphan*/  SYS_PMSCR_EL1_PA_SHIFT ; 
 int /*<<< orphan*/  SYS_PMSCR_EL1_PCT_SHIFT ; 
 int SYS_PMSEVFR_EL1_RES0 ; 
 int /*<<< orphan*/  SYS_PMSFCR_EL1_FE_SHIFT ; 
 int /*<<< orphan*/  SYS_PMSFCR_EL1_FL_SHIFT ; 
 int /*<<< orphan*/  SYS_PMSFCR_EL1_FT_SHIFT ; 
 int arm_spe_event_to_pmscr (struct perf_event*) ; 
 int arm_spe_event_to_pmsevfr (struct perf_event*) ; 
 int arm_spe_event_to_pmsfcr (struct perf_event*) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_test_cpu (scalar_t__,int /*<<< orphan*/ *) ; 
 struct arm_spe_pmu* to_spe_pmu (TYPE_1__*) ; 

__attribute__((used)) static int arm_spe_pmu_event_init(struct perf_event *event)
{
	u64 reg;
	struct perf_event_attr *attr = &event->attr;
	struct arm_spe_pmu *spe_pmu = to_spe_pmu(event->pmu);

	/* This is, of course, deeply driver-specific */
	if (attr->type != event->pmu->type)
		return -ENOENT;

	if (event->cpu >= 0 &&
	    !cpumask_test_cpu(event->cpu, &spe_pmu->supported_cpus))
		return -ENOENT;

	if (arm_spe_event_to_pmsevfr(event) & SYS_PMSEVFR_EL1_RES0)
		return -EOPNOTSUPP;

	if (attr->exclude_idle)
		return -EOPNOTSUPP;

	/*
	 * Feedback-directed frequency throttling doesn't work when we
	 * have a buffer of samples. We'd need to manually count the
	 * samples in the buffer when it fills up and adjust the event
	 * count to reflect that. Instead, just force the user to specify
	 * a sample period.
	 */
	if (attr->freq)
		return -EINVAL;

	reg = arm_spe_event_to_pmsfcr(event);
	if ((reg & BIT(SYS_PMSFCR_EL1_FE_SHIFT)) &&
	    !(spe_pmu->features & SPE_PMU_FEAT_FILT_EVT))
		return -EOPNOTSUPP;

	if ((reg & BIT(SYS_PMSFCR_EL1_FT_SHIFT)) &&
	    !(spe_pmu->features & SPE_PMU_FEAT_FILT_TYP))
		return -EOPNOTSUPP;

	if ((reg & BIT(SYS_PMSFCR_EL1_FL_SHIFT)) &&
	    !(spe_pmu->features & SPE_PMU_FEAT_FILT_LAT))
		return -EOPNOTSUPP;

	reg = arm_spe_event_to_pmscr(event);
	if (!capable(CAP_SYS_ADMIN) &&
	    (reg & (BIT(SYS_PMSCR_EL1_PA_SHIFT) |
		    BIT(SYS_PMSCR_EL1_CX_SHIFT) |
		    BIT(SYS_PMSCR_EL1_PCT_SHIFT))))
		return -EACCES;

	return 0;
}