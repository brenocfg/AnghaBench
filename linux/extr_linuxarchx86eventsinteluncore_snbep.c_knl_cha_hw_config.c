#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int config1; } ;
struct hw_perf_event_extra {int config; int idx; scalar_t__ reg; } ;
struct TYPE_4__ {int config; struct hw_perf_event_extra extra_reg; } ;
struct perf_event {TYPE_3__ attr; TYPE_1__ hw; } ;
struct intel_uncore_box {TYPE_2__* pmu; } ;
struct extra_reg {int event; int config_mask; int idx; scalar_t__ msr; } ;
struct TYPE_5__ {int pmu_idx; } ;

/* Variables and functions */
 scalar_t__ HSWEP_C0_MSR_PMON_BOX_FILTER0 ; 
 int KNL_CHA_MSR_OFFSET ; 
 int KNL_CHA_MSR_PMON_BOX_FILTER_LOCAL_NODE ; 
 int KNL_CHA_MSR_PMON_BOX_FILTER_NNC ; 
 int KNL_CHA_MSR_PMON_BOX_FILTER_REMOTE_NODE ; 
 int knl_cha_filter_mask (int) ; 
 struct extra_reg* knl_uncore_cha_extra_regs ; 

__attribute__((used)) static int knl_cha_hw_config(struct intel_uncore_box *box,
			     struct perf_event *event)
{
	struct hw_perf_event_extra *reg1 = &event->hw.extra_reg;
	struct extra_reg *er;
	int idx = 0;

	for (er = knl_uncore_cha_extra_regs; er->msr; er++) {
		if (er->event != (event->hw.config & er->config_mask))
			continue;
		idx |= er->idx;
	}

	if (idx) {
		reg1->reg = HSWEP_C0_MSR_PMON_BOX_FILTER0 +
			    KNL_CHA_MSR_OFFSET * box->pmu->pmu_idx;
		reg1->config = event->attr.config1 & knl_cha_filter_mask(idx);

		reg1->config |= KNL_CHA_MSR_PMON_BOX_FILTER_REMOTE_NODE;
		reg1->config |= KNL_CHA_MSR_PMON_BOX_FILTER_LOCAL_NODE;
		reg1->config |= KNL_CHA_MSR_PMON_BOX_FILTER_NNC;
		reg1->idx = idx;
	}
	return 0;
}