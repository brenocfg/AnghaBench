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
struct TYPE_5__ {int config1; } ;
struct hw_perf_event_extra {int config; int idx; scalar_t__ reg; } ;
struct TYPE_6__ {int config; struct hw_perf_event_extra extra_reg; } ;
struct perf_event {TYPE_2__ attr; TYPE_3__ hw; } ;
struct intel_uncore_box {TYPE_1__* pmu; } ;
struct extra_reg {int event; int config_mask; int idx; scalar_t__ msr; } ;
struct TYPE_4__ {int pmu_idx; } ;

/* Variables and functions */
 scalar_t__ SNBEP_C0_MSR_PMON_BOX_FILTER ; 
 int SNBEP_CBO_MSR_OFFSET ; 
 int snbep_cbox_filter_mask (int) ; 
 struct extra_reg* snbep_uncore_cbox_extra_regs ; 

__attribute__((used)) static int snbep_cbox_hw_config(struct intel_uncore_box *box, struct perf_event *event)
{
	struct hw_perf_event_extra *reg1 = &event->hw.extra_reg;
	struct extra_reg *er;
	int idx = 0;

	for (er = snbep_uncore_cbox_extra_regs; er->msr; er++) {
		if (er->event != (event->hw.config & er->config_mask))
			continue;
		idx |= er->idx;
	}

	if (idx) {
		reg1->reg = SNBEP_C0_MSR_PMON_BOX_FILTER +
			SNBEP_CBO_MSR_OFFSET * box->pmu->pmu_idx;
		reg1->config = event->attr.config1 & snbep_cbox_filter_mask(idx);
		reg1->idx = idx;
	}
	return 0;
}